#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  rem_port_wwn; } ;
struct TYPE_10__ {TYPE_3__ pn2n; } ;
struct TYPE_7__ {int /*<<< orphan*/  pwwn; } ;
struct TYPE_12__ {int /*<<< orphan*/  pid; TYPE_4__ port_topo; TYPE_1__ port_cfg; } ;
struct TYPE_8__ {int /*<<< orphan*/  flogi_rsp_err; int /*<<< orphan*/  flogi_rejects; int /*<<< orphan*/  flogi_unknown_rsp; int /*<<< orphan*/  flogi_acc_err; int /*<<< orphan*/  flogi_accepts; } ;
struct bfa_fcs_fabric_s {int /*<<< orphan*/  is_auth; int /*<<< orphan*/  fcs; int /*<<< orphan*/  is_npiv; TYPE_6__ bport; int /*<<< orphan*/  fab_type; TYPE_5__* lps; int /*<<< orphan*/  fabric_name; int /*<<< orphan*/  bb_credit; TYPE_2__ stats; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;
struct TYPE_11__ {int /*<<< orphan*/  pr_pwwn; int /*<<< orphan*/  auth_req; int /*<<< orphan*/  npiv_en; int /*<<< orphan*/  lp_pid; scalar_t__ fport; int /*<<< orphan*/  pr_nwwn; int /*<<< orphan*/  brcd_switch; int /*<<< orphan*/  pr_bbcred; int /*<<< orphan*/  ext_status; } ;

/* Variables and functions */
#define  BFA_EPROTO_BAD_ACCEPT 133 
#define  BFA_EPROTO_UNKNOWN_RSP 132 
 int /*<<< orphan*/  BFA_FCS_FABRIC_N2N ; 
 int /*<<< orphan*/  BFA_FCS_FABRIC_SM_CONT_OP ; 
 int /*<<< orphan*/  BFA_FCS_FABRIC_SM_NO_FABRIC ; 
 int /*<<< orphan*/  BFA_FCS_FABRIC_SM_RETRY_OP ; 
#define  BFA_STATUS_EPROTOCOL 131 
#define  BFA_STATUS_FABRIC_RJT 130 
#define  BFA_STATUS_INVALID_MAC 129 
#define  BFA_STATUS_OK 128 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_fabric_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_cb_lps_flogi_comp(void *bfad, void *uarg, bfa_status_t status)
{
	struct bfa_fcs_fabric_s *fabric = uarg;

	bfa_trc(fabric->fcs, fabric->bport.port_cfg.pwwn);
	bfa_trc(fabric->fcs, status);

	switch (status) {
	case BFA_STATUS_OK:
		fabric->stats.flogi_accepts++;
		break;

	case BFA_STATUS_INVALID_MAC:
		/* Only for CNA */
		fabric->stats.flogi_acc_err++;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);

		return;

	case BFA_STATUS_EPROTOCOL:
		switch (fabric->lps->ext_status) {
		case BFA_EPROTO_BAD_ACCEPT:
			fabric->stats.flogi_acc_err++;
			break;

		case BFA_EPROTO_UNKNOWN_RSP:
			fabric->stats.flogi_unknown_rsp++;
			break;

		default:
			break;
		}
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);

		return;

	case BFA_STATUS_FABRIC_RJT:
		fabric->stats.flogi_rejects++;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);
		return;

	default:
		fabric->stats.flogi_rsp_err++;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_RETRY_OP);
		return;
	}

	fabric->bb_credit = fabric->lps->pr_bbcred;
	bfa_trc(fabric->fcs, fabric->bb_credit);

	if (!(fabric->lps->brcd_switch))
		fabric->fabric_name =  fabric->lps->pr_nwwn;

	/*
	 * Check port type. It should be 1 = F-port.
	 */
	if (fabric->lps->fport) {
		fabric->bport.pid = fabric->lps->lp_pid;
		fabric->is_npiv = fabric->lps->npiv_en;
		fabric->is_auth = fabric->lps->auth_req;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_CONT_OP);
	} else {
		/*
		 * Nport-2-Nport direct attached
		 */
		fabric->bport.port_topo.pn2n.rem_port_wwn =
			fabric->lps->pr_pwwn;
		fabric->fab_type = BFA_FCS_FABRIC_N2N;
		bfa_sm_send_event(fabric, BFA_FCS_FABRIC_SM_NO_FABRIC);
	}

	bfa_trc(fabric->fcs, fabric->bport.pid);
	bfa_trc(fabric->fcs, fabric->is_npiv);
	bfa_trc(fabric->fcs, fabric->is_auth);
}