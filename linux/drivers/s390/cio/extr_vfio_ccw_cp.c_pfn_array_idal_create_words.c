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
struct pfn_array {int pa_nr; unsigned long* pa_pfn; int pa_iova; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 

__attribute__((used)) static inline void pfn_array_idal_create_words(
	struct pfn_array *pa,
	unsigned long *idaws)
{
	int i;

	/*
	 * Idal words (execept the first one) rely on the memory being 4k
	 * aligned. If a user virtual address is 4K aligned, then it's
	 * corresponding kernel physical address will also be 4K aligned. Thus
	 * there will be no problem here to simply use the phys to create an
	 * idaw.
	 */

	for (i = 0; i < pa->pa_nr; i++)
		idaws[i] = pa->pa_pfn[i] << PAGE_SHIFT;

	/* Adjust the first IDAW, since it may not start on a page boundary */
	idaws[0] += pa->pa_iova & (PAGE_SIZE - 1);
}