#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ocrdma_qp_params {int path_mtu_pkey_indx; int hop_lmt_rq_psn; int tclass_sq_psn; int ack_to_rnr_rtc_dest_qpn; int rnt_rc_sl_fl; int max_sge_recv_flags; int max_ord_ird; int /*<<< orphan*/ * dgid; int /*<<< orphan*/  qkey; } ;
struct TYPE_11__ {int /*<<< orphan*/  max_sges; scalar_t__ max_cnt; } ;
struct TYPE_10__ {int /*<<< orphan*/  max_sges; scalar_t__ max_cnt; } ;
struct ocrdma_qp {scalar_t__ qp_type; int /*<<< orphan*/  sgid_idx; int /*<<< orphan*/  max_inline_data; TYPE_2__ rq; TYPE_1__ sq; int /*<<< orphan*/  cap_flags; } ;
struct ocrdma_dev {int /*<<< orphan*/  dev_lock; } ;
struct TYPE_12__ {int /*<<< orphan*/  max_inline_data; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; scalar_t__ max_recv_wr; scalar_t__ max_send_wr; } ;
struct ib_qp_init_attr {TYPE_3__ cap; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; } ;
struct ib_qp_attr {int path_mtu; int rq_psn; int sq_psn; int dest_qp_num; int timeout; int rnr_retry; int retry_cnt; int port_num; int sq_draining; int max_dest_rd_atomic; int max_rd_atomic; int en_sqd_async_notify; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  cur_qp_state; struct ocrdma_qp_params alt_ah_attr; scalar_t__ alt_timeout; scalar_t__ alt_port_num; scalar_t__ alt_pkey_index; TYPE_4__ ah_attr; scalar_t__ pkey_index; scalar_t__ min_rnr_timer; TYPE_3__ cap; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  qkey; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
typedef  int /*<<< orphan*/  params ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MIG_MIGRATED ; 
 scalar_t__ IB_QPT_UD ; 
 int OCRDMA_QPS_SQ_DRAINING ; 
 int OCRDMA_QP_PARAMS_ACK_TIMEOUT_MASK ; 
 int OCRDMA_QP_PARAMS_ACK_TIMEOUT_SHIFT ; 
 int OCRDMA_QP_PARAMS_DEST_QPN_MASK ; 
 int OCRDMA_QP_PARAMS_FLAGS_SQD_ASYNC ; 
 int OCRDMA_QP_PARAMS_FLOW_LABEL_MASK ; 
 int OCRDMA_QP_PARAMS_HOP_LMT_MASK ; 
 int OCRDMA_QP_PARAMS_HOP_LMT_SHIFT ; 
 int OCRDMA_QP_PARAMS_MAX_IRD_MASK ; 
 int OCRDMA_QP_PARAMS_MAX_ORD_SHIFT ; 
 int OCRDMA_QP_PARAMS_PATH_MTU_MASK ; 
 int OCRDMA_QP_PARAMS_PATH_MTU_SHIFT ; 
 int OCRDMA_QP_PARAMS_RETRY_CNT_MASK ; 
 int OCRDMA_QP_PARAMS_RETRY_CNT_SHIFT ; 
 int OCRDMA_QP_PARAMS_RNR_RETRY_CNT_MASK ; 
 int OCRDMA_QP_PARAMS_RNR_RETRY_CNT_SHIFT ; 
 int OCRDMA_QP_PARAMS_RQ_PSN_MASK ; 
 int OCRDMA_QP_PARAMS_SL_MASK ; 
 int OCRDMA_QP_PARAMS_SL_SHIFT ; 
 int OCRDMA_QP_PARAMS_SQ_PSN_MASK ; 
 int OCRDMA_QP_PARAMS_STATE_MASK ; 
 int OCRDMA_QP_PARAMS_STATE_SHIFT ; 
 int OCRDMA_QP_PARAMS_TCLASS_MASK ; 
 int OCRDMA_QP_PARAMS_TCLASS_SHIFT ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  get_ibqp_state (int) ; 
 struct ocrdma_dev* get_ocrdma_dev (int /*<<< orphan*/ ) ; 
 struct ocrdma_qp* get_ocrdma_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  memset (struct ocrdma_qp_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ocrdma_mbx_query_qp (struct ocrdma_dev*,struct ocrdma_qp*,struct ocrdma_qp_params*) ; 
 int ocrdma_mtu_int_to_enum (int) ; 
 int /*<<< orphan*/  ocrdma_qp_state_change (struct ocrdma_qp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocrdma_to_ib_qp_acc_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_dgid_raw (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (TYPE_4__*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (TYPE_4__*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (TYPE_4__*,int /*<<< orphan*/ ) ; 

int ocrdma_query_qp(struct ib_qp *ibqp,
		    struct ib_qp_attr *qp_attr,
		    int attr_mask, struct ib_qp_init_attr *qp_init_attr)
{
	int status;
	u32 qp_state;
	struct ocrdma_qp_params params;
	struct ocrdma_qp *qp = get_ocrdma_qp(ibqp);
	struct ocrdma_dev *dev = get_ocrdma_dev(ibqp->device);

	memset(&params, 0, sizeof(params));
	mutex_lock(&dev->dev_lock);
	status = ocrdma_mbx_query_qp(dev, qp, &params);
	mutex_unlock(&dev->dev_lock);
	if (status)
		goto mbx_err;
	if (qp->qp_type == IB_QPT_UD)
		qp_attr->qkey = params.qkey;
	qp_attr->path_mtu =
		ocrdma_mtu_int_to_enum(params.path_mtu_pkey_indx &
				OCRDMA_QP_PARAMS_PATH_MTU_MASK) >>
				OCRDMA_QP_PARAMS_PATH_MTU_SHIFT;
	qp_attr->path_mig_state = IB_MIG_MIGRATED;
	qp_attr->rq_psn = params.hop_lmt_rq_psn & OCRDMA_QP_PARAMS_RQ_PSN_MASK;
	qp_attr->sq_psn = params.tclass_sq_psn & OCRDMA_QP_PARAMS_SQ_PSN_MASK;
	qp_attr->dest_qp_num =
	    params.ack_to_rnr_rtc_dest_qpn & OCRDMA_QP_PARAMS_DEST_QPN_MASK;

	qp_attr->qp_access_flags = ocrdma_to_ib_qp_acc_flags(qp->cap_flags);
	qp_attr->cap.max_send_wr = qp->sq.max_cnt - 1;
	qp_attr->cap.max_recv_wr = qp->rq.max_cnt - 1;
	qp_attr->cap.max_send_sge = qp->sq.max_sges;
	qp_attr->cap.max_recv_sge = qp->rq.max_sges;
	qp_attr->cap.max_inline_data = qp->max_inline_data;
	qp_init_attr->cap = qp_attr->cap;
	qp_attr->ah_attr.type = RDMA_AH_ATTR_TYPE_ROCE;

	rdma_ah_set_grh(&qp_attr->ah_attr, NULL,
			params.rnt_rc_sl_fl &
			  OCRDMA_QP_PARAMS_FLOW_LABEL_MASK,
			qp->sgid_idx,
			(params.hop_lmt_rq_psn &
			 OCRDMA_QP_PARAMS_HOP_LMT_MASK) >>
			 OCRDMA_QP_PARAMS_HOP_LMT_SHIFT,
			(params.tclass_sq_psn &
			 OCRDMA_QP_PARAMS_TCLASS_MASK) >>
			 OCRDMA_QP_PARAMS_TCLASS_SHIFT);
	rdma_ah_set_dgid_raw(&qp_attr->ah_attr, &params.dgid[0]);

	rdma_ah_set_port_num(&qp_attr->ah_attr, 1);
	rdma_ah_set_sl(&qp_attr->ah_attr, (params.rnt_rc_sl_fl &
					   OCRDMA_QP_PARAMS_SL_MASK) >>
					   OCRDMA_QP_PARAMS_SL_SHIFT);
	qp_attr->timeout = (params.ack_to_rnr_rtc_dest_qpn &
			    OCRDMA_QP_PARAMS_ACK_TIMEOUT_MASK) >>
				OCRDMA_QP_PARAMS_ACK_TIMEOUT_SHIFT;
	qp_attr->rnr_retry = (params.ack_to_rnr_rtc_dest_qpn &
			      OCRDMA_QP_PARAMS_RNR_RETRY_CNT_MASK) >>
				OCRDMA_QP_PARAMS_RNR_RETRY_CNT_SHIFT;
	qp_attr->retry_cnt =
	    (params.rnt_rc_sl_fl & OCRDMA_QP_PARAMS_RETRY_CNT_MASK) >>
		OCRDMA_QP_PARAMS_RETRY_CNT_SHIFT;
	qp_attr->min_rnr_timer = 0;
	qp_attr->pkey_index = 0;
	qp_attr->port_num = 1;
	rdma_ah_set_path_bits(&qp_attr->ah_attr, 0);
	rdma_ah_set_static_rate(&qp_attr->ah_attr, 0);
	qp_attr->alt_pkey_index = 0;
	qp_attr->alt_port_num = 0;
	qp_attr->alt_timeout = 0;
	memset(&qp_attr->alt_ah_attr, 0, sizeof(qp_attr->alt_ah_attr));
	qp_state = (params.max_sge_recv_flags & OCRDMA_QP_PARAMS_STATE_MASK) >>
		    OCRDMA_QP_PARAMS_STATE_SHIFT;
	qp_attr->qp_state = get_ibqp_state(qp_state);
	qp_attr->cur_qp_state = qp_attr->qp_state;
	qp_attr->sq_draining = (qp_state == OCRDMA_QPS_SQ_DRAINING) ? 1 : 0;
	qp_attr->max_dest_rd_atomic =
	    params.max_ord_ird >> OCRDMA_QP_PARAMS_MAX_ORD_SHIFT;
	qp_attr->max_rd_atomic =
	    params.max_ord_ird & OCRDMA_QP_PARAMS_MAX_IRD_MASK;
	qp_attr->en_sqd_async_notify = (params.max_sge_recv_flags &
				OCRDMA_QP_PARAMS_FLAGS_SQD_ASYNC) ? 1 : 0;
	/* Sync driver QP state with FW */
	ocrdma_qp_state_change(qp, qp_attr->qp_state, NULL);
mbx_err:
	return status;
}