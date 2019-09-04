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
 int PAGE_SIZE ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  tlb_entry_erase (unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  utlb_invalidate () ; 

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long flags;

	/* exactly same as above, except for TLB entry not taking ASID */

	if (unlikely((end - start) >= PAGE_SIZE * 32)) {
		local_flush_tlb_all();
		return;
	}

	start &= PAGE_MASK;

	local_irq_save(flags);
	while (start < end) {
		tlb_entry_erase(start);
		start += PAGE_SIZE;
	}

	utlb_invalidate();

	local_irq_restore(flags);
}