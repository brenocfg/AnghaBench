#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfa_fcs_rport_s {TYPE_1__* fcs; } ;
struct bfa_fcs_rpf_s {int /*<<< orphan*/  rpsc_retries; int /*<<< orphan*/  fcxp_wqe; struct bfa_fcs_rport_s* rport; } ;
typedef  enum rpf_event { ____Placeholder_rpf_event } rpf_event ;
struct TYPE_3__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
#define  RPFSM_EVENT_FCXP_SENT 129 
#define  RPFSM_EVENT_RPORT_OFFLINE 128 
 int /*<<< orphan*/  bfa_fcs_rpf_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_rpf_sm_rpsc ; 
 int /*<<< orphan*/  bfa_fcxp_walloc_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_fcs_rpf_sm_rpsc_sending(struct bfa_fcs_rpf_s *rpf, enum rpf_event event)
{
	struct bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPFSM_EVENT_FCXP_SENT:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc);
		break;

	case RPFSM_EVENT_RPORT_OFFLINE:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_offline);
		bfa_fcxp_walloc_cancel(rport->fcs->bfa, &rpf->fcxp_wqe);
		rpf->rpsc_retries = 0;
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}