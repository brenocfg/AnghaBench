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
 int /*<<< orphan*/  htw_start () ; 
 int /*<<< orphan*/  htw_stop () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 unsigned long num_wired_entries () ; 
 unsigned long read_c0_entryhi () ; 
 unsigned long read_c0_pagemask () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (unsigned long) ; 
 int /*<<< orphan*/  write_c0_index (unsigned long) ; 
 int /*<<< orphan*/  write_c0_pagemask (unsigned long) ; 
 int /*<<< orphan*/  write_c0_wired (unsigned long) ; 

void add_wired_entry(unsigned long entrylo0, unsigned long entrylo1,
		     unsigned long entryhi, unsigned long pagemask)
{
#ifdef CONFIG_XPA
	panic("Broken for XPA kernels");
#else
	unsigned long flags;
	unsigned long wired;
	unsigned long old_pagemask;
	unsigned long old_ctx;

	local_irq_save(flags);
	/* Save old context and create impossible VPN2 value */
	old_ctx = read_c0_entryhi();
	htw_stop();
	old_pagemask = read_c0_pagemask();
	wired = num_wired_entries();
	write_c0_wired(wired + 1);
	write_c0_index(wired);
	tlbw_use_hazard();	/* What is the hazard here? */
	write_c0_pagemask(pagemask);
	write_c0_entryhi(entryhi);
	write_c0_entrylo0(entrylo0);
	write_c0_entrylo1(entrylo1);
	mtc0_tlbw_hazard();
	tlb_write_indexed();
	tlbw_use_hazard();

	write_c0_entryhi(old_ctx);
	tlbw_use_hazard();	/* What is the hazard here? */
	htw_start();
	write_c0_pagemask(old_pagemask);
	local_flush_tlb_all();
	local_irq_restore(flags);
#endif
}