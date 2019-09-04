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
struct vfp_hard_struct {int fpscr; int /*<<< orphan*/  fpinst2; int /*<<< orphan*/  fpinst; int /*<<< orphan*/  fpexc; int /*<<< orphan*/  fpregs; } ;
struct user_vfp_exc {int /*<<< orphan*/  fpinst2; int /*<<< orphan*/  fpinst; int /*<<< orphan*/  fpexc; } ;
struct user_vfp {int fpscr; int /*<<< orphan*/  fpregs; } ;
struct TYPE_2__ {struct vfp_hard_struct hard; } ;
struct thread_info {TYPE_1__ vfpstate; } ;

/* Variables and functions */
 int FPSCR_LENGTH_MASK ; 
 int FPSCR_STRIDE_MASK ; 
 struct thread_info* current_thread_info () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vfp_flush_hwstate (struct thread_info*) ; 
 int /*<<< orphan*/  vfp_sync_hwstate (struct thread_info*) ; 

int vfp_preserve_user_clear_hwstate(struct user_vfp *ufp,
				    struct user_vfp_exc *ufp_exc)
{
	struct thread_info *thread = current_thread_info();
	struct vfp_hard_struct *hwstate = &thread->vfpstate.hard;

	/* Ensure that the saved hwstate is up-to-date. */
	vfp_sync_hwstate(thread);

	/*
	 * Copy the floating point registers. There can be unused
	 * registers see asm/hwcap.h for details.
	 */
	memcpy(&ufp->fpregs, &hwstate->fpregs, sizeof(hwstate->fpregs));

	/*
	 * Copy the status and control register.
	 */
	ufp->fpscr = hwstate->fpscr;

	/*
	 * Copy the exception registers.
	 */
	ufp_exc->fpexc = hwstate->fpexc;
	ufp_exc->fpinst = hwstate->fpinst;
	ufp_exc->fpinst2 = hwstate->fpinst2;

	/* Ensure that VFP is disabled. */
	vfp_flush_hwstate(thread);

	/*
	 * As per the PCS, clear the length and stride bits for function
	 * entry.
	 */
	hwstate->fpscr &= ~(FPSCR_LENGTH_MASK | FPSCR_STRIDE_MASK);
	return 0;
}