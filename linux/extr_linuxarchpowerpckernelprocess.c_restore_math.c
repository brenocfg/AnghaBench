#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {unsigned long msr; } ;
struct TYPE_7__ {unsigned long fpexc_mode; int /*<<< orphan*/  load_fp; } ;
struct TYPE_6__ {TYPE_4__ thread; } ;

/* Variables and functions */
 unsigned long MSR_FP ; 
 unsigned long MSR_VEC ; 
 unsigned long MSR_VSX ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  loadvec (TYPE_4__) ; 
 int /*<<< orphan*/  msr_all_available ; 
 int /*<<< orphan*/  msr_check_and_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msr_check_and_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msr_tm_active (unsigned long) ; 
 scalar_t__ restore_altivec (TYPE_1__*) ; 
 scalar_t__ restore_fp (TYPE_1__*) ; 
 scalar_t__ restore_vsx (TYPE_1__*) ; 

void restore_math(struct pt_regs *regs)
{
	unsigned long msr;

	if (!msr_tm_active(regs->msr) &&
		!current->thread.load_fp && !loadvec(current->thread))
		return;

	msr = regs->msr;
	msr_check_and_set(msr_all_available);

	/*
	 * Only reload if the bit is not set in the user MSR, the bit BEING set
	 * indicates that the registers are hot
	 */
	if ((!(msr & MSR_FP)) && restore_fp(current))
		msr |= MSR_FP | current->thread.fpexc_mode;

	if ((!(msr & MSR_VEC)) && restore_altivec(current))
		msr |= MSR_VEC;

	if ((msr & (MSR_FP | MSR_VEC)) == (MSR_FP | MSR_VEC) &&
			restore_vsx(current)) {
		msr |= MSR_VSX;
	}

	msr_check_and_clear(msr_all_available);

	regs->msr = msr;
}