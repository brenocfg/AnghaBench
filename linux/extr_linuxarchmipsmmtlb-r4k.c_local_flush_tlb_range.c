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
struct vm_area_struct {struct mm_struct* vm_mm; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {int tlbsize; scalar_t__ tlbsizeftlbsets; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int UNIQUE_ENTRYHI (int) ; 
 int cpu_asid (int,struct mm_struct*) ; 
 scalar_t__ cpu_context (int,struct mm_struct*) ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  drop_mmu_context (struct mm_struct*,int) ; 
 int /*<<< orphan*/  flush_micro_tlb () ; 
 int /*<<< orphan*/  htw_start () ; 
 int /*<<< orphan*/  htw_stop () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int read_c0_entryhi () ; 
 int read_c0_index () ; 
 unsigned long round_down (unsigned long,int) ; 
 unsigned long round_up (unsigned long,int) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_probe_hazard () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int /*<<< orphan*/ ) ; 

void local_flush_tlb_range(struct vm_area_struct *vma, unsigned long start,
	unsigned long end)
{
	struct mm_struct *mm = vma->vm_mm;
	int cpu = smp_processor_id();

	if (cpu_context(cpu, mm) != 0) {
		unsigned long size, flags;

		local_irq_save(flags);
		start = round_down(start, PAGE_SIZE << 1);
		end = round_up(end, PAGE_SIZE << 1);
		size = (end - start) >> (PAGE_SHIFT + 1);
		if (size <= (current_cpu_data.tlbsizeftlbsets ?
			     current_cpu_data.tlbsize / 8 :
			     current_cpu_data.tlbsize / 2)) {
			int oldpid = read_c0_entryhi();
			int newpid = cpu_asid(cpu, mm);

			htw_stop();
			while (start < end) {
				int idx;

				write_c0_entryhi(start | newpid);
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
			write_c0_entryhi(oldpid);
			htw_start();
		} else {
			drop_mmu_context(mm, cpu);
		}
		flush_micro_tlb();
		local_irq_restore(flags);
	}
}