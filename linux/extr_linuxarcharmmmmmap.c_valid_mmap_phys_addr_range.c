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
 size_t PAGE_SHIFT ; 
 size_t PHYS_MASK ; 

int valid_mmap_phys_addr_range(unsigned long pfn, size_t size)
{
	return (pfn + (size >> PAGE_SHIFT)) <= (1 + (PHYS_MASK >> PAGE_SHIFT));
}