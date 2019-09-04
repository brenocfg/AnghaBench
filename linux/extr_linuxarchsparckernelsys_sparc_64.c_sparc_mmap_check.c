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

/* Variables and functions */
 int EINVAL ; 
 unsigned long STACK_TOP32 ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 unsigned long VA_EXCLUDE_START ; 
 scalar_t__ invalid_64bit_range (unsigned long,unsigned long) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

int sparc_mmap_check(unsigned long addr, unsigned long len)
{
	if (test_thread_flag(TIF_32BIT)) {
		if (len >= STACK_TOP32)
			return -EINVAL;

		if (addr > STACK_TOP32 - len)
			return -EINVAL;
	} else {
		if (len >= VA_EXCLUDE_START)
			return -EINVAL;

		if (invalid_64bit_range(addr, len))
			return -EINVAL;
	}

	return 0;
}