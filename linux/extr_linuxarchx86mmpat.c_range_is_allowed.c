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
typedef  scalar_t__ u64 ;

/* Variables and functions */
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  devmem_is_allowed (unsigned long) ; 
 int /*<<< orphan*/  pat_enabled () ; 

__attribute__((used)) static inline int range_is_allowed(unsigned long pfn, unsigned long size)
{
	u64 from = ((u64)pfn) << PAGE_SHIFT;
	u64 to = from + size;
	u64 cursor = from;

	if (!pat_enabled())
		return 1;

	while (cursor < to) {
		if (!devmem_is_allowed(pfn))
			return 0;
		cursor += PAGE_SIZE;
		pfn++;
	}
	return 1;
}