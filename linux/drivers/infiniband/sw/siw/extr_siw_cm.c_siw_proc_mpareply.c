#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct siw_qp_attrs {int irq_size; int orq_size; int /*<<< orphan*/  state; int /*<<< orphan*/  sk; int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {scalar_t__ state; } ;
struct TYPE_8__ {scalar_t__ gso_seg_limit; } ;
struct siw_qp {int /*<<< orphan*/  state_lock; TYPE_7__ attrs; TYPE_1__ tx_ctx; } ;
struct TYPE_11__ {int ird; int ord; } ;
struct TYPE_13__ {int bits; } ;
struct mpa_rr {TYPE_6__ params; int /*<<< orphan*/  key; } ;
struct TYPE_12__ {TYPE_4__ v2_ctrl_req; scalar_t__ pdata; struct mpa_rr hdr; } ;
struct siw_cep {int ird; int ord; int /*<<< orphan*/  state; int /*<<< orphan*/  sock; TYPE_5__ mpa; TYPE_3__* sdev; scalar_t__ enhanced_rdma_conn_est; struct siw_qp* qp; } ;
struct mpa_v2_data {int ird; int ord; } ;
typedef  int /*<<< orphan*/  qp_attrs ;
typedef  enum siw_qp_attr_mask { ____Placeholder_siw_qp_attr_mask } siw_qp_attr_mask ;
typedef  enum mpa_v2_ctrl { ____Placeholder_mpa_v2_ctrl } mpa_v2_ctrl ;
struct TYPE_9__ {int max_ird; int /*<<< orphan*/  max_ord; } ;
struct TYPE_10__ {TYPE_2__ attrs; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ECONNREFUSED ; 
 int ECONNRESET ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROTO ; 
 int /*<<< orphan*/  IW_CM_EVENT_CONNECT_REPLY ; 
 int /*<<< orphan*/  LLP_ECODE_INSUFFICIENT_IRD ; 
 int /*<<< orphan*/  LLP_ECODE_INVALID_REQ_RESP ; 
 int /*<<< orphan*/  LLP_ECODE_NO_MATCHING_RTR ; 
 int /*<<< orphan*/  LLP_ETYPE_MPA ; 
 int MPA_IRD_ORD_MASK ; 
 int /*<<< orphan*/  MPA_KEY_REP ; 
 int MPA_REVISION_2 ; 
 int MPA_RR_FLAG_CRC ; 
 int MPA_RR_FLAG_ENHANCED ; 
 int MPA_RR_FLAG_GSO_EXP ; 
 int MPA_RR_FLAG_MARKERS ; 
 int MPA_RR_FLAG_REJECT ; 
 int MPA_V2_PEER_TO_PEER ; 
 int MPA_V2_RDMA_NO_RTR ; 
 int MPA_V2_RDMA_READ_RTR ; 
 int MPA_V2_RDMA_WRITE_RTR ; 
 int /*<<< orphan*/  SIW_EPSTATE_RDMA_MODE ; 
 int /*<<< orphan*/  SIW_MPA_CRC ; 
 int SIW_QP_ATTR_IRD ; 
 int SIW_QP_ATTR_LLP_HANDLE ; 
 int SIW_QP_ATTR_MPA ; 
 int SIW_QP_ATTR_ORD ; 
 int SIW_QP_ATTR_STATE ; 
 scalar_t__ SIW_QP_STATE_RTR ; 
 int /*<<< orphan*/  SIW_QP_STATE_RTS ; 
 int /*<<< orphan*/  TERM_ERROR_LAYER_LLP ; 
 int __mpa_rr_revision (int) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct siw_qp_attrs*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mpa_crc_required ; 
 scalar_t__ mpa_crc_strict ; 
 int ntohs (int) ; 
 int relaxed_ird_negotiation ; 
 int /*<<< orphan*/  siw_cancel_mpatimer (struct siw_cep*) ; 
 int siw_cm_upcall (struct siw_cep*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  siw_dbg_cep (struct siw_cep*,char*,...) ; 
 int /*<<< orphan*/  siw_init_terminate (struct siw_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int siw_qp_modify (struct siw_qp*,struct siw_qp_attrs*,int) ; 
 int siw_qp_mpa_rts (struct siw_qp*,int) ; 
 int /*<<< orphan*/  siw_qp_socket_assoc (struct siw_cep*,struct siw_qp*) ; 
 int siw_recv_mpa_rr (struct siw_cep*) ; 
 int /*<<< orphan*/  siw_send_terminate (struct siw_qp*) ; 
 scalar_t__ try_gso ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int siw_proc_mpareply(struct siw_cep *cep)
{
	struct siw_qp_attrs qp_attrs;
	enum siw_qp_attr_mask qp_attr_mask;
	struct siw_qp *qp = cep->qp;
	struct mpa_rr *rep;
	int rv;
	u16 rep_ord;
	u16 rep_ird;
	bool ird_insufficient = false;
	enum mpa_v2_ctrl mpa_p2p_mode = MPA_V2_RDMA_NO_RTR;

	rv = siw_recv_mpa_rr(cep);
	if (rv != -EAGAIN)
		siw_cancel_mpatimer(cep);
	if (rv)
		goto out_err;

	rep = &cep->mpa.hdr;

	if (__mpa_rr_revision(rep->params.bits) > MPA_REVISION_2) {
		/* allow for 0, 1,  and 2 only */
		rv = -EPROTO;
		goto out_err;
	}
	if (memcmp(rep->key, MPA_KEY_REP, 16)) {
		siw_init_terminate(qp, TERM_ERROR_LAYER_LLP, LLP_ETYPE_MPA,
				   LLP_ECODE_INVALID_REQ_RESP, 0);
		siw_send_terminate(qp);
		rv = -EPROTO;
		goto out_err;
	}
	if (rep->params.bits & MPA_RR_FLAG_REJECT) {
		siw_dbg_cep(cep, "got mpa reject\n");
		siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, -ECONNRESET);

		return -ECONNRESET;
	}
	if (try_gso && rep->params.bits & MPA_RR_FLAG_GSO_EXP) {
		siw_dbg_cep(cep, "peer allows GSO on TX\n");
		qp->tx_ctx.gso_seg_limit = 0;
	}
	if ((rep->params.bits & MPA_RR_FLAG_MARKERS) ||
	    (mpa_crc_required && !(rep->params.bits & MPA_RR_FLAG_CRC)) ||
	    (mpa_crc_strict && !mpa_crc_required &&
	     (rep->params.bits & MPA_RR_FLAG_CRC))) {
		siw_dbg_cep(cep, "reply unsupp: crc %d:%d:%d, m %d:%d\n",
			    rep->params.bits & MPA_RR_FLAG_CRC ? 1 : 0,
			    mpa_crc_required, mpa_crc_strict,
			    rep->params.bits & MPA_RR_FLAG_MARKERS ? 1 : 0, 0);

		siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, -ECONNREFUSED);

		return -EINVAL;
	}
	if (cep->enhanced_rdma_conn_est) {
		struct mpa_v2_data *v2;

		if (__mpa_rr_revision(rep->params.bits) < MPA_REVISION_2 ||
		    !(rep->params.bits & MPA_RR_FLAG_ENHANCED)) {
			/*
			 * Protocol failure: The responder MUST reply with
			 * MPA version 2 and MUST set MPA_RR_FLAG_ENHANCED.
			 */
			siw_dbg_cep(cep, "mpa reply error: vers %d, enhcd %d\n",
				    __mpa_rr_revision(rep->params.bits),
				    rep->params.bits & MPA_RR_FLAG_ENHANCED ?
					    1 :
					    0);

			siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY,
				      -ECONNRESET);
			return -EINVAL;
		}
		v2 = (struct mpa_v2_data *)cep->mpa.pdata;
		rep_ird = ntohs(v2->ird) & MPA_IRD_ORD_MASK;
		rep_ord = ntohs(v2->ord) & MPA_IRD_ORD_MASK;

		if (cep->ird < rep_ord &&
		    (relaxed_ird_negotiation == false ||
		     rep_ord > cep->sdev->attrs.max_ird)) {
			siw_dbg_cep(cep, "ird %d, rep_ord %d, max_ord %d\n",
				    cep->ird, rep_ord,
				    cep->sdev->attrs.max_ord);
			ird_insufficient = true;
		}
		if (cep->ord > rep_ird && relaxed_ird_negotiation == false) {
			siw_dbg_cep(cep, "ord %d, rep_ird %d\n", cep->ord,
				    rep_ird);
			ird_insufficient = true;
		}
		/*
		 * Always report negotiated peer values to user,
		 * even if IRD/ORD negotiation failed
		 */
		cep->ird = rep_ord;
		cep->ord = rep_ird;

		if (ird_insufficient) {
			/*
			 * If the initiator IRD is insuffient for the
			 * responder ORD, send a TERM.
			 */
			siw_init_terminate(qp, TERM_ERROR_LAYER_LLP,
					   LLP_ETYPE_MPA,
					   LLP_ECODE_INSUFFICIENT_IRD, 0);
			siw_send_terminate(qp);
			rv = -ENOMEM;
			goto out_err;
		}
		if (cep->mpa.v2_ctrl_req.ird & MPA_V2_PEER_TO_PEER)
			mpa_p2p_mode =
				cep->mpa.v2_ctrl_req.ord &
				(MPA_V2_RDMA_WRITE_RTR | MPA_V2_RDMA_READ_RTR);

		/*
		 * Check if we requested P2P mode, and if peer agrees
		 */
		if (mpa_p2p_mode != MPA_V2_RDMA_NO_RTR) {
			if ((mpa_p2p_mode & v2->ord) == 0) {
				/*
				 * We requested RTR mode(s), but the peer
				 * did not pick any mode we support.
				 */
				siw_dbg_cep(cep,
					    "rtr mode:  req %2x, got %2x\n",
					    mpa_p2p_mode,
					    v2->ord & (MPA_V2_RDMA_WRITE_RTR |
						       MPA_V2_RDMA_READ_RTR));

				siw_init_terminate(qp, TERM_ERROR_LAYER_LLP,
						   LLP_ETYPE_MPA,
						   LLP_ECODE_NO_MATCHING_RTR,
						   0);
				siw_send_terminate(qp);
				rv = -EPROTO;
				goto out_err;
			}
			mpa_p2p_mode = v2->ord & (MPA_V2_RDMA_WRITE_RTR |
						  MPA_V2_RDMA_READ_RTR);
		}
	}
	memset(&qp_attrs, 0, sizeof(qp_attrs));

	if (rep->params.bits & MPA_RR_FLAG_CRC)
		qp_attrs.flags = SIW_MPA_CRC;

	qp_attrs.irq_size = cep->ird;
	qp_attrs.orq_size = cep->ord;
	qp_attrs.sk = cep->sock;
	qp_attrs.state = SIW_QP_STATE_RTS;

	qp_attr_mask = SIW_QP_ATTR_STATE | SIW_QP_ATTR_LLP_HANDLE |
		       SIW_QP_ATTR_ORD | SIW_QP_ATTR_IRD | SIW_QP_ATTR_MPA;

	/* Move socket RX/TX under QP control */
	down_write(&qp->state_lock);
	if (qp->attrs.state > SIW_QP_STATE_RTR) {
		rv = -EINVAL;
		up_write(&qp->state_lock);
		goto out_err;
	}
	rv = siw_qp_modify(qp, &qp_attrs, qp_attr_mask);

	siw_qp_socket_assoc(cep, qp);

	up_write(&qp->state_lock);

	/* Send extra RDMA frame to trigger peer RTS if negotiated */
	if (mpa_p2p_mode != MPA_V2_RDMA_NO_RTR) {
		rv = siw_qp_mpa_rts(qp, mpa_p2p_mode);
		if (rv)
			goto out_err;
	}
	if (!rv) {
		rv = siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, 0);
		if (!rv)
			cep->state = SIW_EPSTATE_RDMA_MODE;

		return 0;
	}

out_err:
	siw_cm_upcall(cep, IW_CM_EVENT_CONNECT_REPLY, -EINVAL);

	return rv;
}