#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_lport_scn_s {struct bfa_fcxp_s* fcxp; int /*<<< orphan*/  fcxp_wqe; struct bfa_fcs_lport_s* port; } ;
struct TYPE_7__ {int /*<<< orphan*/  pwwn; } ;
struct bfa_fcs_lport_s {int /*<<< orphan*/  lp_tag; TYPE_3__* fabric; int /*<<< orphan*/  pid; TYPE_4__* fcs; int /*<<< orphan*/  vport; TYPE_1__ port_cfg; } ;
struct TYPE_11__ {int /*<<< orphan*/  ioc; } ;
struct TYPE_10__ {TYPE_5__* bfa; } ;
struct TYPE_9__ {int /*<<< orphan*/  vf_id; TYPE_2__* lps; } ;
struct TYPE_8__ {int /*<<< orphan*/  brcd_switch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_ELS_TOV ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int /*<<< orphan*/  SCNSM_EVENT_SCR_SENT ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_fcxp_alloc_wait (TYPE_5__*,int /*<<< orphan*/ *,void (*) (void*,struct bfa_fcxp_s*),struct bfa_fcs_lport_scn_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcs_lport_scn_scr_response ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct fchs_s*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfa_ioc_get_fcmode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_lport_scn_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int fc_scr_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_lport_scn_send_scr(void *scn_cbarg, struct bfa_fcxp_s *fcxp_alloced)
{
	struct bfa_fcs_lport_scn_s *scn = scn_cbarg;
	struct bfa_fcs_lport_s *port = scn->port;
	struct fchs_s fchs;
	int             len;
	struct bfa_fcxp_s *fcxp;

	bfa_trc(port->fcs, port->pid);
	bfa_trc(port->fcs, port->port_cfg.pwwn);

	fcxp = fcxp_alloced ? fcxp_alloced :
	       bfa_fcs_fcxp_alloc(port->fcs, BFA_TRUE);
	if (!fcxp) {
		bfa_fcs_fcxp_alloc_wait(port->fcs->bfa, &scn->fcxp_wqe,
				bfa_fcs_lport_scn_send_scr, scn, BFA_TRUE);
		return;
	}
	scn->fcxp = fcxp;

	/* Handle VU registrations for Base port only */
	if ((!port->vport) && bfa_ioc_get_fcmode(&port->fcs->bfa->ioc)) {
		len = fc_scr_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				port->fabric->lps->brcd_switch,
				port->pid, 0);
	} else {
	    len = fc_scr_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				    BFA_FALSE,
				    port->pid, 0);
	}

	bfa_fcxp_send(fcxp, NULL, port->fabric->vf_id, port->lp_tag, BFA_FALSE,
			  FC_CLASS_3, len, &fchs,
			  bfa_fcs_lport_scn_scr_response,
			  (void *)scn, FC_MAX_PDUSZ, FC_ELS_TOV);

	bfa_sm_send_event(scn, SCNSM_EVENT_SCR_SENT);
}