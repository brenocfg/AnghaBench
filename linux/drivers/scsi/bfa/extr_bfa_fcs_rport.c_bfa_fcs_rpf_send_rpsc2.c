#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  rpsc_sent; } ;
struct bfa_fcs_rport_s {TYPE_2__ stats; int /*<<< orphan*/  pid; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  fcs; struct bfa_fcs_lport_s* port; } ;
struct bfa_fcs_rpf_s {struct bfa_fcxp_s* fcxp; int /*<<< orphan*/  fcxp_wqe; struct bfa_fcs_rport_s* rport; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_1__* fabric; TYPE_3__* fcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  bfa; } ;
struct TYPE_4__ {int /*<<< orphan*/  vf_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_ELS_TOV ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int /*<<< orphan*/  RPFSM_EVENT_FCXP_SENT ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fcxp_alloc_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void (*) (void*,struct bfa_fcxp_s*),struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_get_fcid (struct bfa_fcs_lport_s*) ; 
 int /*<<< orphan*/  bfa_fcs_rpf_rpsc2_response ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ ,struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_rpf_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fc_rpsc2_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
bfa_fcs_rpf_send_rpsc2(void *rpf_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_rpf_s *rpf = (struct bfa_fcs_rpf_s *)rpf_cbarg;
	struct bfa_fcs_rport_s *rport = rpf->rport;
	struct bfa_fcs_lport_s *port = rport->port;
	struct fchs_s	fchs;
	int		len;
	struct bfa_fcxp_s *fcxp;

	bfa_trc(rport->fcs, rport->pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &rpf->fcxp_wqe,
				bfa_fcs_rpf_send_rpsc2, rpf, BFA_TRUE);
		return;
	}
	rpf->fcxp = fcxp;

	len = fc_rpsc2_build(&fchs, bfa_fcxp_get_reqbuf(fcxp), rport->pid,
			    bfa_fcs_lport_get_fcid(port), &rport->pid, 1);

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs, bfa_fcs_rpf_rpsc2_response,
			  rpf, FC_MAX_PDUSZ, FC_ELS_TOV);
	rport->stats.rpsc_sent++;
	bfa_sm_send_event(rpf, RPFSM_EVENT_FCXP_SENT);

}