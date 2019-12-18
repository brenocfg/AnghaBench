#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct fc_seq_els_data {void* explan; void* reason; } ;
struct TYPE_4__ {scalar_t__ port_name; } ;
struct fc_rport_priv {int rp_state; int /*<<< orphan*/  kref; int /*<<< orphan*/  rp_mutex; TYPE_2__ ids; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;} ;
struct fc_lport {scalar_t__ wwpn; TYPE_1__ tt; int /*<<< orphan*/  point_to_multipoint; } ;
struct fc_frame {int dummy; } ;
struct fc_els_flogi {int /*<<< orphan*/  fl_cmd; } ;

/* Variables and functions */
 void* ELS_EXPL_INV_LEN ; 
 void* ELS_EXPL_NONE ; 
 void* ELS_EXPL_NOT_NEIGHBOR ; 
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int /*<<< orphan*/  ELS_LS_RJT ; 
 void* ELS_RJT_BUSY ; 
 void* ELS_RJT_FIP ; 
 void* ELS_RJT_LOGIC ; 
 void* ELS_RJT_UNSUP ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REP ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_RPORT_ID_DBG (struct fc_lport*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  RPORT_EV_LOGO ; 
#define  RPORT_ST_ADISC 136 
#define  RPORT_ST_DELETE 135 
#define  RPORT_ST_FLOGI 134 
#define  RPORT_ST_INIT 133 
#define  RPORT_ST_PLOGI 132 
#define  RPORT_ST_PLOGI_WAIT 131 
#define  RPORT_ST_PRLI 130 
#define  RPORT_ST_READY 129 
#define  RPORT_ST_RTV 128 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_flogi_fill (struct fc_lport*,struct fc_frame*) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_flogi* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_frame_sid (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 int /*<<< orphan*/  fc_rport_enter_delete (struct fc_rport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_enter_plogi (struct fc_rport_priv*) ; 
 scalar_t__ fc_rport_login_complete (struct fc_rport_priv*,struct fc_frame*) ; 
 struct fc_rport_priv* fc_rport_lookup (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_state_enter (struct fc_rport_priv*,int const) ; 
 int /*<<< orphan*/  fc_seq_els_rsp_send (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void fc_rport_recv_flogi_req(struct fc_lport *lport,
				    struct fc_frame *rx_fp)
{
	struct fc_els_flogi *flp;
	struct fc_rport_priv *rdata;
	struct fc_frame *fp = rx_fp;
	struct fc_seq_els_data rjt_data;
	u32 sid;

	sid = fc_frame_sid(fp);

	FC_RPORT_ID_DBG(lport, sid, "Received FLOGI request\n");

	if (!lport->point_to_multipoint) {
		rjt_data.reason = ELS_RJT_UNSUP;
		rjt_data.explan = ELS_EXPL_NONE;
		goto reject;
	}

	flp = fc_frame_payload_get(fp, sizeof(*flp));
	if (!flp) {
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_INV_LEN;
		goto reject;
	}

	rdata = fc_rport_lookup(lport, sid);
	if (!rdata) {
		rjt_data.reason = ELS_RJT_FIP;
		rjt_data.explan = ELS_EXPL_NOT_NEIGHBOR;
		goto reject;
	}
	mutex_lock(&rdata->rp_mutex);

	FC_RPORT_DBG(rdata, "Received FLOGI in %s state\n",
		     fc_rport_state(rdata));

	switch (rdata->rp_state) {
	case RPORT_ST_INIT:
		/*
		 * If received the FLOGI request on RPORT which is INIT state
		 * (means not transition to FLOGI either fc_rport timeout
		 * function didn;t trigger or this end hasn;t received
		 * beacon yet from other end. In that case only, allow RPORT
		 * state machine to continue, otherwise fall through which
		 * causes the code to send reject response.
		 * NOTE; Not checking for FIP->state such as VNMP_UP or
		 * VNMP_CLAIM because if FIP state is not one of those,
		 * RPORT wouldn;t have created and 'rport_lookup' would have
		 * failed anyway in that case.
		 */
		break;
	case RPORT_ST_DELETE:
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_FIP;
		rjt_data.explan = ELS_EXPL_NOT_NEIGHBOR;
		goto reject_put;
	case RPORT_ST_FLOGI:
	case RPORT_ST_PLOGI_WAIT:
	case RPORT_ST_PLOGI:
		break;
	case RPORT_ST_PRLI:
	case RPORT_ST_RTV:
	case RPORT_ST_READY:
	case RPORT_ST_ADISC:
		/*
		 * Set the remote port to be deleted and to then restart.
		 * This queues work to be sure exchanges are reset.
		 */
		fc_rport_enter_delete(rdata, RPORT_EV_LOGO);
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_BUSY;
		rjt_data.explan = ELS_EXPL_NONE;
		goto reject_put;
	}
	if (fc_rport_login_complete(rdata, fp)) {
		mutex_unlock(&rdata->rp_mutex);
		rjt_data.reason = ELS_RJT_LOGIC;
		rjt_data.explan = ELS_EXPL_NONE;
		goto reject_put;
	}

	fp = fc_frame_alloc(lport, sizeof(*flp));
	if (!fp)
		goto out;

	fc_flogi_fill(lport, fp);
	flp = fc_frame_payload_get(fp, sizeof(*flp));
	flp->fl_cmd = ELS_LS_ACC;

	fc_fill_reply_hdr(fp, rx_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);

	/*
	 * Do not proceed with the state machine if our
	 * FLOGI has crossed with an FLOGI from the
	 * remote port; wait for the FLOGI response instead.
	 */
	if (rdata->rp_state != RPORT_ST_FLOGI) {
		if (rdata->ids.port_name < lport->wwpn)
			fc_rport_enter_plogi(rdata);
		else
			fc_rport_state_enter(rdata, RPORT_ST_PLOGI_WAIT);
	}
out:
	mutex_unlock(&rdata->rp_mutex);
	kref_put(&rdata->kref, fc_rport_destroy);
	fc_frame_free(rx_fp);
	return;

reject_put:
	kref_put(&rdata->kref, fc_rport_destroy);
reject:
	fc_seq_els_rsp_send(rx_fp, ELS_LS_RJT, &rjt_data);
	fc_frame_free(rx_fp);
}