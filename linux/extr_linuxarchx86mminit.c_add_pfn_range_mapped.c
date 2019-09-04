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
 int /*<<< orphan*/  E820_MAX_ENTRIES ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  add_range_with_merge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  clean_sort_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  max_low_pfn_mapped ; 
 int /*<<< orphan*/  max_pfn_mapped ; 
 unsigned long min (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  nr_pfn_mapped ; 
 int /*<<< orphan*/  pfn_mapped ; 

__attribute__((used)) static void add_pfn_range_mapped(unsigned long start_pfn, unsigned long end_pfn)
{
	nr_pfn_mapped = add_range_with_merge(pfn_mapped, E820_MAX_ENTRIES,
					     nr_pfn_mapped, start_pfn, end_pfn);
	nr_pfn_mapped = clean_sort_range(pfn_mapped, E820_MAX_ENTRIES);

	max_pfn_mapped = max(max_pfn_mapped, end_pfn);

	if (start_pfn < (1UL<<(32-PAGE_SHIFT)))
		max_low_pfn_mapped = max(max_low_pfn_mapped,
					 min(end_pfn, 1UL<<(32-PAGE_SHIFT)));
}