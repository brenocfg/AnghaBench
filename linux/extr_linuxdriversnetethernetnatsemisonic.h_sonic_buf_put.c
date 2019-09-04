#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */

__attribute__((used)) static inline void sonic_buf_put(void* base, int bitmode,
				 int offset, __u16 val)
{
	if (bitmode)
#ifdef __BIG_ENDIAN
		((__u16 *) base + (offset*2))[1] = val;
#else
		((__u16 *) base + (offset*2))[0] = val;
#endif
	else
	 	((__u16 *) base)[offset] = val;
}