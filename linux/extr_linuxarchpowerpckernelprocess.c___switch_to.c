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
struct thread_struct {int /*<<< orphan*/  hw_brk; } ;
struct task_struct {struct thread_struct thread; } ;
struct TYPE_2__ {struct thread_struct thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __set_breakpoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __switch_to_tm (struct task_struct*,struct task_struct*) ; 
 struct task_struct* _switch (struct thread_struct*,struct thread_struct*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  current_brk ; 
 int /*<<< orphan*/  giveup_all (struct task_struct*) ; 
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  hw_brk_match (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  radix_enabled () ; 
 int /*<<< orphan*/  restore_sprs (struct thread_struct*,struct thread_struct*) ; 
 int /*<<< orphan*/  save_sprs (struct thread_struct*) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

struct task_struct *__switch_to(struct task_struct *prev,
	struct task_struct *new)
{
	struct thread_struct *new_thread, *old_thread;
	struct task_struct *last;
#ifdef CONFIG_PPC_BOOK3S_64
	struct ppc64_tlb_batch *batch;
#endif

	new_thread = &new->thread;
	old_thread = &current->thread;

	WARN_ON(!irqs_disabled());

#ifdef CONFIG_PPC_BOOK3S_64
	batch = this_cpu_ptr(&ppc64_tlb_batch);
	if (batch->active) {
		current_thread_info()->local_flags |= _TLF_LAZY_MMU;
		if (batch->index)
			__flush_tlb_pending(batch);
		batch->active = 0;
	}
#endif /* CONFIG_PPC_BOOK3S_64 */

#ifdef CONFIG_PPC_ADV_DEBUG_REGS
	switch_booke_debug_regs(&new->thread.debug);
#else
/*
 * For PPC_BOOK3S_64, we use the hw-breakpoint interfaces that would
 * schedule DABR
 */
#ifndef CONFIG_HAVE_HW_BREAKPOINT
	if (unlikely(!hw_brk_match(this_cpu_ptr(&current_brk), &new->thread.hw_brk)))
		__set_breakpoint(&new->thread.hw_brk);
#endif /* CONFIG_HAVE_HW_BREAKPOINT */
#endif

	/*
	 * We need to save SPRs before treclaim/trecheckpoint as these will
	 * change a number of them.
	 */
	save_sprs(&prev->thread);

	/* Save FPU, Altivec, VSX and SPE state */
	giveup_all(prev);

	__switch_to_tm(prev, new);

	if (!radix_enabled()) {
		/*
		 * We can't take a PMU exception inside _switch() since there
		 * is a window where the kernel stack SLB and the kernel stack
		 * are out of sync. Hard disable here.
		 */
		hard_irq_disable();
	}

	/*
	 * Call restore_sprs() before calling _switch(). If we move it after
	 * _switch() then we miss out on calling it for new tasks. The reason
	 * for this is we manually create a stack frame for new tasks that
	 * directly returns through ret_from_fork() or
	 * ret_from_kernel_thread(). See copy_thread() for details.
	 */
	restore_sprs(old_thread, new_thread);

	last = _switch(old_thread, new_thread);

#ifdef CONFIG_PPC_BOOK3S_64
	if (current_thread_info()->local_flags & _TLF_LAZY_MMU) {
		current_thread_info()->local_flags &= ~_TLF_LAZY_MMU;
		batch = this_cpu_ptr(&ppc64_tlb_batch);
		batch->active = 1;
	}

	if (current_thread_info()->task->thread.regs) {
		restore_math(current_thread_info()->task->thread.regs);

		/*
		 * The copy-paste buffer can only store into foreign real
		 * addresses, so unprivileged processes can not see the
		 * data or use it in any way unless they have foreign real
		 * mappings. If the new process has the foreign real address
		 * mappings, we must issue a cp_abort to clear any state and
		 * prevent snooping, corruption or a covert channel.
		 */
		if (current_thread_info()->task->thread.used_vas)
			asm volatile(PPC_CP_ABORT);
	}
#endif /* CONFIG_PPC_BOOK3S_64 */

	return last;
}