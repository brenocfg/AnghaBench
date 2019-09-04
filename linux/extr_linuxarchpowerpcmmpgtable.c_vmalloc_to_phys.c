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
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long __pa (int /*<<< orphan*/ ) ; 
 unsigned long offset_in_page (void*) ; 
 int /*<<< orphan*/  pfn_to_kaddr (unsigned long) ; 
 unsigned long vmalloc_to_pfn (void*) ; 

unsigned long vmalloc_to_phys(void *va)
{
	unsigned long pfn = vmalloc_to_pfn(va);

	BUG_ON(!pfn);
	return __pa(pfn_to_kaddr(pfn)) + offset_in_page(va);
}