#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tlbsizevtlb; int tlbsizeftlbsets; int tlbsize; } ;

/* Variables and functions */
 unsigned long UNIQUE_ENTRYHI (int) ; 
 scalar_t__ cpu_has_tlbinv ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  flush_micro_tlb () ; 
 int /*<<< orphan*/  htw_start () ; 
 int /*<<< orphan*/  htw_stop () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int num_wired_entries () ; 
 unsigned long read_c0_entryhi () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbinvf () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_index (int) ; 

void local_flush_tlb_all(void)
{
	unsigned long flags;
	unsigned long old_ctx;
	int entry, ftlbhighset;

	local_irq_save(flags);
	/* Save old context and create impossible VPN2 value */
	old_ctx = read_c0_entryhi();
	htw_stop();
	write_c0_entrylo0(0);
	write_c0_entrylo1(0);

	entry = num_wired_entries();

	/*
	 * Blast 'em all away.
	 * If there are any wired entries, fall back to iterating
	 */
	if (cpu_has_tlbinv && !entry) {
		if (current_cpu_data.tlbsizevtlb) {
			write_c0_index(0);
			mtc0_tlbw_hazard();
			tlbinvf();  /* invalidate VTLB */
		}
		ftlbhighset = current_cpu_data.tlbsizevtlb +
			current_cpu_data.tlbsizeftlbsets;
		for (entry = current_cpu_data.tlbsizevtlb;
		     entry < ftlbhighset;
		     entry++) {
			write_c0_index(entry);
			mtc0_tlbw_hazard();
			tlbinvf();  /* invalidate one FTLB set */
		}
	} else {
		while (entry < current_cpu_data.tlbsize) {
			/* Make sure all entries differ. */
			write_c0_entryhi(UNIQUE_ENTRYHI(entry));
			write_c0_index(entry);
			mtc0_tlbw_hazard();
			tlb_write_indexed();
			entry++;
		}
	}
	tlbw_use_hazard();
	write_c0_entryhi(old_ctx);
	htw_start();
	flush_micro_tlb();
	local_irq_restore(flags);
}