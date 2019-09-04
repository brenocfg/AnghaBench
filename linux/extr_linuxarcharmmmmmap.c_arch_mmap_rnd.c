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
 unsigned long get_random_long () ; 
 unsigned long mmap_rnd_bits ; 

unsigned long arch_mmap_rnd(void)
{
	unsigned long rnd;

	rnd = get_random_long() & ((1UL << mmap_rnd_bits) - 1);

	return rnd << PAGE_SHIFT;
}