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
struct thread_struct {int dummy; } ;
struct task_struct {struct thread_struct thread; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned long DEBUGCTLMSR_BTF ; 
 unsigned long DEBUGCTLMSR_BTF_SHIFT ; 
 int /*<<< orphan*/  MSR_IA32_DEBUGCTLMSR ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long TIF_BLOCKSTEP ; 
 int /*<<< orphan*/  X86_CR4_TSD ; 
 unsigned long _TIF_BLOCKSTEP ; 
 unsigned long _TIF_NOCPUID ; 
 unsigned long _TIF_NOTSC ; 
 unsigned long _TIF_SPEC_FORCE_UPDATE ; 
 int /*<<< orphan*/  __speculation_ctrl_update (unsigned long,unsigned long) ; 
 scalar_t__ arch_has_block_step () ; 
 int /*<<< orphan*/  cr4_toggle_bits_irqsoff (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  propagate_user_return_notify (struct task_struct*,struct task_struct*) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_cpuid_faulting (int) ; 
 unsigned long speculation_ctrl_update_tif (struct task_struct*) ; 
 int /*<<< orphan*/  switch_to_bitmap (struct thread_struct*,struct thread_struct*,unsigned long,unsigned long) ; 
 TYPE_1__* task_thread_info (struct task_struct*) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,unsigned long) ; 

void __switch_to_xtra(struct task_struct *prev_p, struct task_struct *next_p)
{
	struct thread_struct *prev, *next;
	unsigned long tifp, tifn;

	prev = &prev_p->thread;
	next = &next_p->thread;

	tifn = READ_ONCE(task_thread_info(next_p)->flags);
	tifp = READ_ONCE(task_thread_info(prev_p)->flags);
	switch_to_bitmap(prev, next, tifp, tifn);

	propagate_user_return_notify(prev_p, next_p);

	if ((tifp & _TIF_BLOCKSTEP || tifn & _TIF_BLOCKSTEP) &&
	    arch_has_block_step()) {
		unsigned long debugctl, msk;

		rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
		debugctl &= ~DEBUGCTLMSR_BTF;
		msk = tifn & _TIF_BLOCKSTEP;
		debugctl |= (msk >> TIF_BLOCKSTEP) << DEBUGCTLMSR_BTF_SHIFT;
		wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
	}

	if ((tifp ^ tifn) & _TIF_NOTSC)
		cr4_toggle_bits_irqsoff(X86_CR4_TSD);

	if ((tifp ^ tifn) & _TIF_NOCPUID)
		set_cpuid_faulting(!!(tifn & _TIF_NOCPUID));

	if (likely(!((tifp | tifn) & _TIF_SPEC_FORCE_UPDATE))) {
		__speculation_ctrl_update(tifp, tifn);
	} else {
		speculation_ctrl_update_tif(prev_p);
		tifn = speculation_ctrl_update_tif(next_p);

		/* Enforce MSR update to ensure consistent state */
		__speculation_ctrl_update(~tifn, tifn);
	}
}