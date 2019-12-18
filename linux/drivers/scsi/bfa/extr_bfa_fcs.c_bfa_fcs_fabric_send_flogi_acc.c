#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int dummy; } ;
struct bfa_s {int dummy; } ;
struct bfa_lport_cfg_s {int /*<<< orphan*/  nwwn; int /*<<< orphan*/  pwwn; } ;
struct bfa_fcxp_s {int dummy; } ;
struct bfa_fcs_lport_n2n_s {int /*<<< orphan*/  reply_oxid; } ;
struct TYPE_5__ {struct bfa_fcs_lport_n2n_s pn2n; } ;
struct TYPE_6__ {TYPE_1__ port_topo; struct bfa_lport_cfg_s port_cfg; } ;
struct bfa_fcs_fabric_s {TYPE_3__* lps; int /*<<< orphan*/  vf_id; TYPE_4__* fcs; TYPE_2__ bport; } ;
struct TYPE_8__ {struct bfa_s* bfa; } ;
struct TYPE_7__ {int /*<<< orphan*/  bfa_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  FC_CLASS_3 ; 
 int /*<<< orphan*/  FC_FABRIC_PORT ; 
 int /*<<< orphan*/  FC_MAX_PDUSZ ; 
 int /*<<< orphan*/  bfa_fcport_get_maxfrsize (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcport_get_rx_bbcredit (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_fcs_fabric_flogiacc_comp ; 
 struct bfa_fcxp_s* bfa_fcs_fcxp_alloc (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcxp_get_reqbuf (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  bfa_fcxp_send (struct bfa_fcxp_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fchs_s*,int /*<<< orphan*/ ,struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_hton3b (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_flogi_acc_build (struct fchs_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcs_fabric_send_flogi_acc(struct bfa_fcs_fabric_s *fabric)
{
	struct bfa_lport_cfg_s *pcfg = &fabric->bport.port_cfg;
	struct bfa_fcs_lport_n2n_s *n2n_port = &fabric->bport.port_topo.pn2n;
	struct bfa_s	  *bfa = fabric->fcs->bfa;
	struct bfa_fcxp_s *fcxp;
	u16	reqlen;
	struct fchs_s	fchs;

	fcxp = bfa_fcs_fcxp_alloc(fabric->fcs, BFA_FALSE);
	/*
	 * Do not expect this failure -- expect remote node to retry
	 */
	if (!fcxp)
		return;

	reqlen = fc_flogi_acc_build(&fchs, bfa_fcxp_get_reqbuf(fcxp),
				    bfa_hton3b(FC_FABRIC_PORT),
				    n2n_port->reply_oxid, pcfg->pwwn,
				    pcfg->nwwn,
				    bfa_fcport_get_maxfrsize(bfa),
				    bfa_fcport_get_rx_bbcredit(bfa), 0);

	bfa_fcxp_send(fcxp, NULL, fabric->vf_id, fabric->lps->bfa_tag,
		      BFA_FALSE, FC_CLASS_3,
		      reqlen, &fchs, bfa_fcs_fabric_flogiacc_comp, fabric,
		      FC_MAX_PDUSZ, 0);
}