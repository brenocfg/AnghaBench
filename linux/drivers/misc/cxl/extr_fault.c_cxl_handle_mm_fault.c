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
typedef  int /*<<< orphan*/  vm_fault_t ;
typedef  int u64 ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int CXL_PSL_DSISR_An_S ; 
 int DSISR_NOHPTE ; 
 unsigned long HPTE_NOHPTE_UPDATE ; 
 scalar_t__ USER_REGION_ID ; 
 unsigned long _PAGE_PRESENT ; 
 unsigned long _PAGE_PRIVILEGED ; 
 unsigned long _PAGE_READ ; 
 unsigned long _PAGE_WRITE ; 
 int copro_handle_mm_fault (struct mm_struct*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_region_id (int) ; 
 int /*<<< orphan*/  hash_page_mm (struct mm_struct*,int,unsigned long,int,unsigned long) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  pr_devel (char*,int) ; 
 int /*<<< orphan*/  radix_enabled () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

int cxl_handle_mm_fault(struct mm_struct *mm, u64 dsisr, u64 dar)
{
	vm_fault_t flt = 0;
	int result;
	unsigned long access, flags, inv_flags = 0;

	/*
	 * Add the fault handling cpu to task mm cpumask so that we
	 * can do a safe lockless page table walk when inserting the
	 * hash page table entry. This function get called with a
	 * valid mm for user space addresses. Hence using the if (mm)
	 * check is sufficient here.
	 */
	if (mm && !cpumask_test_cpu(smp_processor_id(), mm_cpumask(mm))) {
		cpumask_set_cpu(smp_processor_id(), mm_cpumask(mm));
		/*
		 * We need to make sure we walk the table only after
		 * we update the cpumask. The other side of the barrier
		 * is explained in serialize_against_pte_lookup()
		 */
		smp_mb();
	}
	if ((result = copro_handle_mm_fault(mm, dar, dsisr, &flt))) {
		pr_devel("copro_handle_mm_fault failed: %#x\n", result);
		return result;
	}

	if (!radix_enabled()) {
		/*
		 * update_mmu_cache() will not have loaded the hash since current->trap
		 * is not a 0x400 or 0x300, so just call hash_page_mm() here.
		 */
		access = _PAGE_PRESENT | _PAGE_READ;
		if (dsisr & CXL_PSL_DSISR_An_S)
			access |= _PAGE_WRITE;

		if (!mm && (get_region_id(dar) != USER_REGION_ID))
			access |= _PAGE_PRIVILEGED;

		if (dsisr & DSISR_NOHPTE)
			inv_flags |= HPTE_NOHPTE_UPDATE;

		local_irq_save(flags);
		hash_page_mm(mm, dar, access, 0x300, inv_flags);
		local_irq_restore(flags);
	}
	return 0;
}