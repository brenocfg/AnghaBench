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
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned long TASK_SIZE ; 
 unsigned long _TLB_ENTRIES ; 
 int /*<<< orphan*/  invalidate_dtlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  invalidate_itlb_mapping (unsigned long) ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	if (end > start && start >= TASK_SIZE && end <= PAGE_OFFSET &&
	    end - start < _TLB_ENTRIES << PAGE_SHIFT) {
		start &= PAGE_MASK;
		while (start < end) {
			invalidate_itlb_mapping(start);
			invalidate_dtlb_mapping(start);
			start += PAGE_SIZE;
		}
	} else {
		local_flush_tlb_all();
	}
}