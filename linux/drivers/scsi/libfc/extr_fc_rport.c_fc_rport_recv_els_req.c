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
struct fc_seq_els_data {int /*<<< orphan*/  explan; int /*<<< orphan*/  reason; } ;
struct fc_rport_priv {int rp_state; int /*<<< orphan*/  kref; int /*<<< orphan*/  rp_mutex; } ;
struct fc_lport {int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
#define  ELS_ADISC 139 
 int /*<<< orphan*/  ELS_EXPL_NONE ; 
 int /*<<< orphan*/  ELS_EXPL_PLOGI_REQD ; 
 int const ELS_LS_RJT ; 
#define  ELS_PRLI 138 
#define  ELS_PRLO 137 
#define  ELS_REC 136 
 int /*<<< orphan*/  ELS_RJT_BUSY ; 
 int /*<<< orphan*/  ELS_RJT_UNAB ; 
#define  ELS_RLS 135 
#define  ELS_RRQ 134 
#define  ELS_RTV 133 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,int,...) ; 
 int /*<<< orphan*/  FC_RPORT_ID_DBG (struct fc_lport*,int /*<<< orphan*/ ,char*,int) ; 
#define  RPORT_ST_ADISC 132 
#define  RPORT_ST_PLOGI 131 
#define  RPORT_ST_PRLI 130 
#define  RPORT_ST_READY 129 
#define  RPORT_ST_RTV 128 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 int fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_sid (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 struct fc_rport_priv* fc_rport_lookup (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_recv_adisc_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_prli_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_prlo_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_rls_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_recv_rtv_req (struct fc_rport_priv*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_seq_els_rsp_send (struct fc_frame*,int const,struct fc_seq_els_data*) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_rport_recv_els_req(struct fc_lport *lport, struct fc_frame *fp)
{
	struct fc_rport_priv *rdata;
	struct fc_seq_els_data els_data;

	lockdep_assert_held(&lport->lp_mutex);

	rdata = fc_rport_lookup(lport, fc_frame_sid(fp));
	if (!rdata) {
		FC_RPORT_ID_DBG(lport, fc_frame_sid(fp),
				"Received ELS 0x%02x from non-logged-in port\n",
				fc_frame_payload_op(fp));
		goto reject;
	}

	mutex_lock(&rdata->rp_mutex);

	switch (rdata->rp_state) {
	case RPORT_ST_PRLI:
	case RPORT_ST_RTV:
	case RPORT_ST_READY:
	case RPORT_ST_ADISC:
		break;
	case RPORT_ST_PLOGI:
		if (fc_frame_payload_op(fp) == ELS_PRLI) {
			FC_RPORT_DBG(rdata, "Reject ELS PRLI "
				     "while in state %s\n",
				     fc_rport_state(rdata));
			mutex_unlock(&rdata->rp_mutex);
			kref_put(&rdata->kref, fc_rport_destroy);
			goto busy;
		}
		/* fall through */
	default:
		FC_RPORT_DBG(rdata,
			     "Reject ELS 0x%02x while in state %s\n",
			     fc_frame_payload_op(fp), fc_rport_state(rdata));
		mutex_unlock(&rdata->rp_mutex);
		kref_put(&rdata->kref, fc_rport_destroy);
		goto reject;
	}

	switch (fc_frame_payload_op(fp)) {
	case ELS_PRLI:
		fc_rport_recv_prli_req(rdata, fp);
		break;
	case ELS_PRLO:
		fc_rport_recv_prlo_req(rdata, fp);
		break;
	case ELS_ADISC:
		fc_rport_recv_adisc_req(rdata, fp);
		break;
	case ELS_RRQ:
		fc_seq_els_rsp_send(fp, ELS_RRQ, NULL);
		fc_frame_free(fp);
		break;
	case ELS_REC:
		fc_seq_els_rsp_send(fp, ELS_REC, NULL);
		fc_frame_free(fp);
		break;
	case ELS_RLS:
		fc_rport_recv_rls_req(rdata, fp);
		break;
	case ELS_RTV:
		fc_rport_recv_rtv_req(rdata, fp);
		break;
	default:
		fc_frame_free(fp);	/* can't happen */
		break;
	}

	mutex_unlock(&rdata->rp_mutex);
	kref_put(&rdata->kref, fc_rport_destroy);
	return;

reject:
	els_data.reason = ELS_RJT_UNAB;
	els_data.explan = ELS_EXPL_PLOGI_REQD;
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
	fc_frame_free(fp);
	return;

busy:
	els_data.reason = ELS_RJT_BUSY;
	els_data.explan = ELS_EXPL_NONE;
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &els_data);
	fc_frame_free(fp);
	return;
}