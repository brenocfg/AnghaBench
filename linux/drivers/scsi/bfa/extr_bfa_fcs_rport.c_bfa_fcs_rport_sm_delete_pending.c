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
struct bfa_fcs_rport_s {int pwwn; int pid; int /*<<< orphan*/  fcs; } ;
typedef  enum rport_event { ____Placeholder_rport_event } rport_event ;

/* Variables and functions */
#define  RPSM_EVENT_DELETE 131 
#define  RPSM_EVENT_HCB_OFFLINE 130 
#define  RPSM_EVENT_LOGO_IMP 129 
#define  RPSM_EVENT_PLOGI_RCVD 128 
 int /*<<< orphan*/  bfa_fcs_rport_free (struct bfa_fcs_rport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rport_sm_uninit ; 
 int /*<<< orphan*/  bfa_sm_fault (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rport_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_fcs_rport_sm_delete_pending(struct bfa_fcs_rport_s *rport,
				enum rport_event event)
{
	bfa_trc(rport->fcs, rport->pwwn);
	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPSM_EVENT_HCB_OFFLINE:
		bfa_sm_set_state(rport, bfa_fcs_rport_sm_uninit);
		bfa_fcs_rport_free(rport);
		break;

	case RPSM_EVENT_DELETE:
	case RPSM_EVENT_LOGO_IMP:
	case RPSM_EVENT_PLOGI_RCVD:
		/* Ignore these events */
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}