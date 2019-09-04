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
struct task_struct {int dummy; } ;
struct mm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ALTIVEC ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inc_mm_active_cpus (struct mm_struct*) ; 
 int /*<<< orphan*/  membarrier_arch_switch_mm (struct mm_struct*,struct mm_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  mm_cpumask (struct mm_struct*) ; 
 int /*<<< orphan*/  radix_kvm_prefetch_workaround (struct mm_struct*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  switch_mm_pgdir (struct task_struct*,struct mm_struct*) ; 
 int /*<<< orphan*/  switch_mmu_context (struct mm_struct*,struct mm_struct*,struct task_struct*) ; 

void switch_mm_irqs_off(struct mm_struct *prev, struct mm_struct *next,
			struct task_struct *tsk)
{
	bool new_on_cpu = false;

	/* Mark this context has been used on the new CPU */
	if (!cpumask_test_cpu(smp_processor_id(), mm_cpumask(next))) {
		cpumask_set_cpu(smp_processor_id(), mm_cpumask(next));
		inc_mm_active_cpus(next);

		/*
		 * This full barrier orders the store to the cpumask above vs
		 * a subsequent operation which allows this CPU to begin loading
		 * translations for next.
		 *
		 * When using the radix MMU that operation is the load of the
		 * MMU context id, which is then moved to SPRN_PID.
		 *
		 * For the hash MMU it is either the first load from slb_cache
		 * in switch_slb(), and/or the store of paca->mm_ctx_id in
		 * copy_mm_to_paca().
		 *
		 * On the other side, the barrier is in mm/tlb-radix.c for
		 * radix which orders earlier stores to clear the PTEs vs
		 * the load of mm_cpumask. And pte_xchg which does the same
		 * thing for hash.
		 *
		 * This full barrier is needed by membarrier when switching
		 * between processes after store to rq->curr, before user-space
		 * memory accesses.
		 */
		smp_mb();

		new_on_cpu = true;
	}

	/* Some subarchs need to track the PGD elsewhere */
	switch_mm_pgdir(tsk, next);

	/* Nothing else to do if we aren't actually switching */
	if (prev == next)
		return;

	/*
	 * We must stop all altivec streams before changing the HW
	 * context
	 */
	if (cpu_has_feature(CPU_FTR_ALTIVEC))
		asm volatile ("dssall");

	if (new_on_cpu)
		radix_kvm_prefetch_workaround(next);
	else
		membarrier_arch_switch_mm(prev, next, tsk);

	/*
	 * The actual HW switching method differs between the various
	 * sub architectures. Out of line for now
	 */
	switch_mmu_context(prev, next, tsk);
}