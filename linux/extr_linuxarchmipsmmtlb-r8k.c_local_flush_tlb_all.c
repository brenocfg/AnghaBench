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
 unsigned long CKSEG0 ; 
 int PAGE_SHIFT ; 
 int TFP_TLB_SET_SHIFT ; 
 int TFP_TLB_SIZE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 unsigned long read_c0_entryhi () ; 
 int /*<<< orphan*/  tlb_write () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_tlbset (int) ; 
 int /*<<< orphan*/  write_c0_vaddr (int) ; 

void local_flush_tlb_all(void)
{
	unsigned long flags;
	unsigned long old_ctx;
	int entry;

	local_irq_save(flags);
	/* Save old context and create impossible VPN2 value */
	old_ctx = read_c0_entryhi();
	write_c0_entrylo(0);

	for (entry = 0; entry < TFP_TLB_SIZE; entry++) {
		write_c0_tlbset(entry >> TFP_TLB_SET_SHIFT);
		write_c0_vaddr(entry << PAGE_SHIFT);
		write_c0_entryhi(CKSEG0 + (entry << (PAGE_SHIFT + 1)));
		mtc0_tlbw_hazard();
		tlb_write();
	}
	tlbw_use_hazard();
	write_c0_entryhi(old_ctx);
	local_irq_restore(flags);
}