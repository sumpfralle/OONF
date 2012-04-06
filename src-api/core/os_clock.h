
/*
 * The olsr.org Optimized Link-State Routing daemon(olsrd)
 * Copyright (c) 2004-2012, the olsr.org team - see HISTORY file
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of olsr.org, olsrd nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Visit http://www.olsr.org for more information.
 *
 * If you find this software useful feel free to make a donation
 * to the project. For more information see the website or contact
 * the copyright holders.
 *
 */

#ifndef OS_CLOCK_H_
#define OS_CLOCK_H_

#include <stdio.h>
#include <sys/time.h>

#include "common/common_types.h"
#include "olsr_logging.h"
#include "olsr_interface.h"

#define MSEC_PER_SEC 1000
#define USEC_PER_MSEC 1000

/*
 * Set one of the following defines in the os specific os_net includes
 * to OS_SPECIFIC to define that the os code is implementing the function
 * itself and does not use the generic function
 * Set it to OS_GENERIC to define that the code use the default implementation.
 *
 * Example from os_system_linux.h:
 *
 * #define OS_SYSTEM_INIT         OS_SPECIFIC
 * #define OS_SYSTEM_INIT_IF      OS_SPECIFIC
 * #define OS_SYSTEM_SET_IFSTATE  OS_SPECIFIC
 * #define OS_SYSTEM_GETTIMEOFDAY OS_GENERIC
 * #define OS_SYSTEM_LOG          OS_GENERIC
 */

/* set the guard macro so we can include the os specific settings */
#define OS_NET_SPECIFIC_INCLUDE
#include "os_helper.h"

#if defined(__linux__)
#include "os_linux/os_clock_linux.h"
#elif defined (BSD)
#include "os_bsd/os_clock_bsd.h"
#elif defined (_WIN32)
#include "os_win32/os_clock_win32.h"
#else
#error "Unknown operation system"
#endif

#undef OS_NET_SPECIFIC_INCLUDE

/* prototypes for all os_system functions */
EXPORT int os_clock_init(void);
EXPORT void os_clock_cleanup(void);

EXPORT int os_clock_gettime64(uint64_t *t64);

/*
 * INLINE implementations for generic os_net functions
 */

#if OS_CLOCK_INIT == OS_GENERIC
/**
 * Dummy init function
 * @return always returns 0
 */
static INLINE int
os_clock_init(void) {
  return 0;
}

/**
 * Dummy cleanup function
 */
static INLINE void
os_clock_init(void) {
}

#endif

#if OS_CLOCK_GETTIMEOFDAY == OS_GENERIC
/**
 * Inline wrapper around gettimeofday
 * @param tv pointer to target timeval object
 * @return -1 if an error happened, 0 otherwise
 */
static INLINE int
os_clock_gettimeofday(struct timeval *tv) {
  return gettimeofday(tv, NULL);
}
#endif


#endif /* OS_CLOCK_H_ */