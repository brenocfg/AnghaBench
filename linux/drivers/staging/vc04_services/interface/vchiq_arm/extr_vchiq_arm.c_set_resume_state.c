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
struct vchiq_arm_state {int vc_resume_state; int /*<<< orphan*/  vc_resume_complete; } ;
typedef  enum vc_resume_status { ____Placeholder_vc_resume_status } vc_resume_status ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  VC_RESUME_FAILED 132 
#define  VC_RESUME_IDLE 131 
#define  VC_RESUME_IN_PROGRESS 130 
#define  VC_RESUME_REQUESTED 129 
#define  VC_RESUME_RESUMED 128 
 int /*<<< orphan*/  VC_SUSPEND_IDLE ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_suspend_state (struct vchiq_arm_state*,int /*<<< orphan*/ ) ; 

void
set_resume_state(struct vchiq_arm_state *arm_state,
		 enum vc_resume_status new_state)
{
	/* set the state in all cases */
	arm_state->vc_resume_state = new_state;

	/* state specific additional actions */
	switch (new_state) {
	case VC_RESUME_FAILED:
		break;
	case VC_RESUME_IDLE:
		reinit_completion(&arm_state->vc_resume_complete);
		break;
	case VC_RESUME_REQUESTED:
		break;
	case VC_RESUME_IN_PROGRESS:
		break;
	case VC_RESUME_RESUMED:
		complete_all(&arm_state->vc_resume_complete);
		set_suspend_state(arm_state, VC_SUSPEND_IDLE);
		break;
	default:
		BUG();
		break;
	}
}