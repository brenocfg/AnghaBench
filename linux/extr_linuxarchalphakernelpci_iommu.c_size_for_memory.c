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
 unsigned long max_low_pfn ; 
 unsigned long roundup_pow_of_two (unsigned long) ; 

unsigned long
size_for_memory(unsigned long max)
{
	unsigned long mem = max_low_pfn << PAGE_SHIFT;
	if (mem < max)
		max = roundup_pow_of_two(mem);
	return max;
}