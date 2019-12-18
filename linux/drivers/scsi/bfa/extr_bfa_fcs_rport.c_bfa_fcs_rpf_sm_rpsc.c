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
struct bfa_fcs_rport_s {int pid; TYPE_1__* fcs; int /*<<< orphan*/  bfa_rport; } ;
struct bfa_fcs_rpf_s {int /*<<< orphan*/  rpsc_retries; int /*<<< orphan*/  fcxp; int /*<<< orphan*/  timer; int /*<<< orphan*/  assigned_speed; int /*<<< orphan*/  rpsc_speed; struct bfa_fcs_rport_s* rport; } ;
typedef  enum rpf_event { ____Placeholder_rpf_event } rpf_event ;
struct TYPE_3__ {int /*<<< orphan*/  bfa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_RPF_RETRIES ; 
 int /*<<< orphan*/  BFA_FCS_RPF_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  BFA_PORT_SPEED_UNKNOWN ; 
#define  RPFSM_EVENT_RPORT_OFFLINE 131 
#define  RPFSM_EVENT_RPSC_COMP 130 
#define  RPFSM_EVENT_RPSC_ERROR 129 
#define  RPFSM_EVENT_RPSC_FAIL 128 
 int /*<<< orphan*/  bfa_fcs_rpf_sm_offline ; 
 int /*<<< orphan*/  bfa_fcs_rpf_sm_online ; 
 int /*<<< orphan*/  bfa_fcs_rpf_sm_rpsc_retry ; 
 int /*<<< orphan*/  bfa_fcs_rpf_timeout ; 
 int /*<<< orphan*/  bfa_fcxp_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_rport_speed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_fault (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_1__*,int) ; 

__attribute__((used)) static void
bfa_fcs_rpf_sm_rpsc(struct bfa_fcs_rpf_s *rpf, enum rpf_event event)
{
	struct bfa_fcs_rport_s *rport = rpf->rport;

	bfa_trc(rport->fcs, rport->pid);
	bfa_trc(rport->fcs, event);

	switch (event) {
	case RPFSM_EVENT_RPSC_COMP:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_online);
		/* Update speed info in f/w via BFA */
		if (rpf->rpsc_speed != BFA_PORT_SPEED_UNKNOWN)
			bfa_rport_speed(rport->bfa_rport, rpf->rpsc_speed);
		else if (rpf->assigned_speed != BFA_PORT_SPEED_UNKNOWN)
			bfa_rport_speed(rport->bfa_rport, rpf->assigned_speed);
		break;

	case RPFSM_EVENT_RPSC_FAIL:
		/* RPSC not supported by rport */
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_online);
		break;

	case RPFSM_EVENT_RPSC_ERROR:
		/* need to retry...delayed a bit. */
		if (rpf->rpsc_retries++ < BFA_FCS_RPF_RETRIES) {
			bfa_timer_start(rport->fcs->bfa, &rpf->timer,
				    bfa_fcs_rpf_timeout, rpf,
				    BFA_FCS_RPF_RETRY_TIMEOUT);
			bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_rpsc_retry);
		} else {
			bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_online);
		}
		break;

	case RPFSM_EVENT_RPORT_OFFLINE:
		bfa_sm_set_state(rpf, bfa_fcs_rpf_sm_offline);
		bfa_fcxp_discard(rpf->fcxp);
		rpf->rpsc_retries = 0;
		break;

	default:
		bfa_sm_fault(rport->fcs, event);
	}
}