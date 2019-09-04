#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* regs; } ;
struct task_struct {TYPE_2__ thread; } ;
struct TYPE_3__ {unsigned long msr; } ;

/* Variables and functions */
 unsigned long MSR_FP ; 
 unsigned long MSR_SPE ; 
 unsigned long MSR_VEC ; 
 unsigned long MSR_VSX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __giveup_spe (struct task_struct*) ; 
 unsigned long msr_all_available ; 
 int /*<<< orphan*/  msr_check_and_clear (unsigned long) ; 
 int /*<<< orphan*/  msr_check_and_set (unsigned long) ; 
 int /*<<< orphan*/  save_altivec (struct task_struct*) ; 
 int /*<<< orphan*/  save_fpu (struct task_struct*) ; 
 int /*<<< orphan*/  thread_pkey_regs_save (TYPE_2__*) ; 

__attribute__((used)) static void save_all(struct task_struct *tsk)
{
	unsigned long usermsr;

	if (!tsk->thread.regs)
		return;

	usermsr = tsk->thread.regs->msr;

	if ((usermsr & msr_all_available) == 0)
		return;

	msr_check_and_set(msr_all_available);

	WARN_ON((usermsr & MSR_VSX) && !((usermsr & MSR_FP) && (usermsr & MSR_VEC)));

	if (usermsr & MSR_FP)
		save_fpu(tsk);

	if (usermsr & MSR_VEC)
		save_altivec(tsk);

	if (usermsr & MSR_SPE)
		__giveup_spe(tsk);

	msr_check_and_clear(msr_all_available);
	thread_pkey_regs_save(&tsk->thread);
}