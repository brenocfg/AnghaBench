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
 unsigned long PAGE_SHIFT ; 
 scalar_t__ TASK_IS_32BIT_ADDR ; 
 unsigned long get_random_long () ; 

__attribute__((used)) static inline unsigned long brk_rnd(void)
{
	unsigned long rnd = get_random_long();

	rnd = rnd << PAGE_SHIFT;
	/* 8MB for 32bit, 256MB for 64bit */
	if (TASK_IS_32BIT_ADDR)
		rnd = rnd & 0x7ffffful;
	else
		rnd = rnd & 0xffffffful;

	return rnd;
}