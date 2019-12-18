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
struct pfn_array {int pa_nr; unsigned long* pa_iova_pfn; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 

__attribute__((used)) static bool pfn_array_iova_pinned(struct pfn_array *pa, unsigned long iova)
{
	unsigned long iova_pfn = iova >> PAGE_SHIFT;
	int i;

	for (i = 0; i < pa->pa_nr; i++)
		if (pa->pa_iova_pfn[i] == iova_pfn)
			return true;

	return false;
}