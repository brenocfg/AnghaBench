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
 unsigned long long PAGE_SIZE ; 
 unsigned long cpu_asid (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long get_asid () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  switch_and_save_asid (unsigned long) ; 

__attribute__((used)) static void sh64_icache_inv_user_page(struct vm_area_struct *vma, unsigned long eaddr)
{
	/* If we get called, we know that vma->vm_flags contains VM_EXEC.
	   Also, eaddr is page-aligned. */
	unsigned int cpu = smp_processor_id();
	unsigned long long addr, end_addr;
	unsigned long flags = 0;
	unsigned long running_asid, vma_asid;
	addr = eaddr;
	end_addr = addr + PAGE_SIZE;

	/* Check whether we can use the current ASID for the I-cache
	   invalidation.  For example, if we're called via
	   access_process_vm->flush_cache_page->here, (e.g. when reading from
	   /proc), 'running_asid' will be that of the reader, not of the
	   victim.

	   Also, note the risk that we might get pre-empted between the ASID
	   compare and blocking IRQs, and before we regain control, the
	   pid->ASID mapping changes.  However, the whole cache will get
	   invalidated when the mapping is renewed, so the worst that can
	   happen is that the loop below ends up invalidating somebody else's
	   cache entries.
	*/

	running_asid = get_asid();
	vma_asid = cpu_asid(cpu, vma->vm_mm);
	if (running_asid != vma_asid) {
		local_irq_save(flags);
		switch_and_save_asid(vma_asid);
	}
	while (addr < end_addr) {
		/* Worth unrolling a little */
		__asm__ __volatile__("icbi %0,  0" : : "r" (addr));
		__asm__ __volatile__("icbi %0, 32" : : "r" (addr));
		__asm__ __volatile__("icbi %0, 64" : : "r" (addr));
		__asm__ __volatile__("icbi %0, 96" : : "r" (addr));
		addr += 128;
	}
	if (running_asid != vma_asid) {
		switch_and_save_asid(running_asid);
		local_irq_restore(flags);
	}
}