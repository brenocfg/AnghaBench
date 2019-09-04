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
struct TYPE_2__ {int tlbsize; scalar_t__ tlbsizeftlbsets; } ;

/* Variables and functions */
 int PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int UNIQUE_ENTRYHI (int) ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  flush_micro_tlb () ; 
 int /*<<< orphan*/  htw_start () ; 
 int /*<<< orphan*/  htw_stop () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int read_c0_entryhi () ; 
 int read_c0_index () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_probe_hazard () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int /*<<< orphan*/ ) ; 

void local_flush_tlb_kernel_range(unsigned long start, unsigned long end)
{
	unsigned long size, flags;

	local_irq_save(flags);
	size = (end - start + (PAGE_SIZE - 1)) >> PAGE_SHIFT;
	size = (size + 1) >> 1;
	if (size <= (current_cpu_data.tlbsizeftlbsets ?
		     current_cpu_data.tlbsize / 8 :
		     current_cpu_data.tlbsize / 2)) {
		int pid = read_c0_entryhi();

		start &= (PAGE_MASK << 1);
		end += ((PAGE_SIZE << 1) - 1);
		end &= (PAGE_MASK << 1);
		htw_stop();

		while (start < end) {
			int idx;

			write_c0_entryhi(start);
			start += (PAGE_SIZE << 1);
			mtc0_tlbw_hazard();
			tlb_probe();
			tlb_probe_hazard();
			idx = read_c0_index();
			write_c0_entrylo0(0);
			write_c0_entrylo1(0);
			if (idx < 0)
				continue;
			/* Make sure all entries differ. */
			write_c0_entryhi(UNIQUE_ENTRYHI(idx));
			mtc0_tlbw_hazard();
			tlb_write_indexed();
		}
		tlbw_use_hazard();
		write_c0_entryhi(pid);
		htw_start();
	} else {
		local_flush_tlb_all();
	}
	flush_micro_tlb();
	local_irq_restore(flags);
}