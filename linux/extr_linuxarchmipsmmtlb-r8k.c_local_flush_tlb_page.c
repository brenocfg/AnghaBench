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
struct vm_area_struct {int /*<<< orphan*/  vm_mm; } ;

/* Variables and functions */
 int CKSEG0 ; 
 unsigned long PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int cpu_asid (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_context (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int read_c0_entryhi () ; 
 long read_c0_tlbset () ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  tlb_probe () ; 
 int /*<<< orphan*/  tlb_write () ; 
 int /*<<< orphan*/  write_c0_entryhi (int) ; 
 int /*<<< orphan*/  write_c0_entrylo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_vaddr (unsigned long) ; 

void local_flush_tlb_page(struct vm_area_struct *vma, unsigned long page)
{
	int cpu = smp_processor_id();
	unsigned long flags;
	int oldpid, newpid;
	signed long idx;

	if (!cpu_context(cpu, vma->vm_mm))
		return;

	newpid = cpu_asid(cpu, vma->vm_mm);
	page &= PAGE_MASK;
	local_irq_save(flags);
	oldpid = read_c0_entryhi();
	write_c0_vaddr(page);
	write_c0_entryhi(newpid);
	tlb_probe();
	idx = read_c0_tlbset();
	if (idx < 0)
		goto finish;

	write_c0_entrylo(0);
	write_c0_entryhi(CKSEG0 + (idx << (PAGE_SHIFT + 1)));
	tlb_write();

finish:
	write_c0_entryhi(oldpid);
	local_irq_restore(flags);
}