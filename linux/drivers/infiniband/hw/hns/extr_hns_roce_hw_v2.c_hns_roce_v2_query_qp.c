#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_12__ {int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; } ;
struct ib_qp_init_attr {int qp_state; int path_mtu; int rq_psn; int qp_access_flags; int max_rd_atomic; int max_dest_rd_atomic; int retry_cnt; int cur_qp_state; TYPE_5__ cap; int /*<<< orphan*/  rnr_retry; void* timeout; void* min_rnr_timer; scalar_t__ sq_draining; scalar_t__ port_num; TYPE_6__ ah_attr; void* dest_qp_num; scalar_t__ sq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; } ;
struct ib_qp_attr {int qp_state; int path_mtu; int rq_psn; int qp_access_flags; int max_rd_atomic; int max_dest_rd_atomic; int retry_cnt; int cur_qp_state; TYPE_5__ cap; int /*<<< orphan*/  rnr_retry; void* timeout; void* min_rnr_timer; scalar_t__ sq_draining; scalar_t__ port_num; TYPE_6__ ah_attr; void* dest_qp_num; scalar_t__ sq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; } ;
struct ib_qp {int /*<<< orphan*/  uobject; int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {int flow_label; int sgid_index; int hop_limit; int traffic_class; TYPE_2__ dgid; } ;
struct hns_roce_v2_qp_context {int /*<<< orphan*/  rq_rnr_timer; int /*<<< orphan*/  byte_212_lsn; int /*<<< orphan*/  byte_28_at_fl; int /*<<< orphan*/  byte_80_rnr_rx_cqn; int /*<<< orphan*/  byte_140_raq; int /*<<< orphan*/  byte_208_irrl; int /*<<< orphan*/  dgid; int /*<<< orphan*/  byte_24_mtu_tc; int /*<<< orphan*/  byte_20_smac_sgid_idx; int /*<<< orphan*/  byte_76_srqn_op_en; int /*<<< orphan*/  byte_56_dqpn_err; int /*<<< orphan*/  byte_172_sq_psn; int /*<<< orphan*/  byte_108_rx_reqepsn; int /*<<< orphan*/  byte_60_qpst_tempid; } ;
struct TYPE_11__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_10__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_8__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {int state; int /*<<< orphan*/  mutex; TYPE_4__ sq; TYPE_3__ rq; scalar_t__ port; TYPE_1__ ibqp; } ;
struct hns_roce_dev {struct device* dev; } ;
struct device {int dummy; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;
typedef  enum hns_roce_v2_qp_state { ____Placeholder_hns_roce_v2_qp_state } hns_roce_v2_qp_state ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IB_MIG_ARMED ; 
 int IB_QPS_RESET ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  V2_QKEY_VAL ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_EPSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_108_RX_REQ_EPSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RR_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_140_RR_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_SQ_CUR_PSN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_172_SQ_CUR_PSN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_SR_MAX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_208_SR_MAX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGID_IDX_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SGID_IDX_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_CNT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_212_RETRY_CNT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_HOP_LIMIT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_HOP_LIMIT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_MTU_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_MTU_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_TC_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_24_TC_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_AT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_AT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_FL_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_FL_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_SL_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_28_SL_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_DQPN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_DQPN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_QP_ST_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_60_QP_ST_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_ATE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RRE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RWE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_MIN_RNR_TIME_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_MIN_RNR_TIME_S ; 
 int V2_QP_ATE_S ; 
 int V2_QP_RRE_S ; 
 int V2_QP_RWE_S ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_v2_query_qpc (struct hns_roce_dev*,struct hns_roce_qp*,struct hns_roce_v2_qp_context*) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ib_global_route* rdma_ah_retrieve_grh (TYPE_6__*) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (TYPE_6__*,int) ; 
 int roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 int to_ib_qp_st (int) ; 

__attribute__((used)) static int hns_roce_v2_query_qp(struct ib_qp *ibqp, struct ib_qp_attr *qp_attr,
				int qp_attr_mask,
				struct ib_qp_init_attr *qp_init_attr)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct hns_roce_v2_qp_context context = {};
	struct device *dev = hr_dev->dev;
	int tmp_qp_state;
	int state;
	int ret;

	memset(qp_attr, 0, sizeof(*qp_attr));
	memset(qp_init_attr, 0, sizeof(*qp_init_attr));

	mutex_lock(&hr_qp->mutex);

	if (hr_qp->state == IB_QPS_RESET) {
		qp_attr->qp_state = IB_QPS_RESET;
		ret = 0;
		goto done;
	}

	ret = hns_roce_v2_query_qpc(hr_dev, hr_qp, &context);
	if (ret) {
		dev_err(dev, "query qpc error\n");
		ret = -EINVAL;
		goto out;
	}

	state = roce_get_field(context.byte_60_qpst_tempid,
			       V2_QPC_BYTE_60_QP_ST_M, V2_QPC_BYTE_60_QP_ST_S);
	tmp_qp_state = to_ib_qp_st((enum hns_roce_v2_qp_state)state);
	if (tmp_qp_state == -1) {
		dev_err(dev, "Illegal ib_qp_state\n");
		ret = -EINVAL;
		goto out;
	}
	hr_qp->state = (u8)tmp_qp_state;
	qp_attr->qp_state = (enum ib_qp_state)hr_qp->state;
	qp_attr->path_mtu = (enum ib_mtu)roce_get_field(context.byte_24_mtu_tc,
							V2_QPC_BYTE_24_MTU_M,
							V2_QPC_BYTE_24_MTU_S);
	qp_attr->path_mig_state = IB_MIG_ARMED;
	qp_attr->ah_attr.type   = RDMA_AH_ATTR_TYPE_ROCE;
	if (hr_qp->ibqp.qp_type == IB_QPT_UD)
		qp_attr->qkey = V2_QKEY_VAL;

	qp_attr->rq_psn = roce_get_field(context.byte_108_rx_reqepsn,
					 V2_QPC_BYTE_108_RX_REQ_EPSN_M,
					 V2_QPC_BYTE_108_RX_REQ_EPSN_S);
	qp_attr->sq_psn = (u32)roce_get_field(context.byte_172_sq_psn,
					      V2_QPC_BYTE_172_SQ_CUR_PSN_M,
					      V2_QPC_BYTE_172_SQ_CUR_PSN_S);
	qp_attr->dest_qp_num = (u8)roce_get_field(context.byte_56_dqpn_err,
						  V2_QPC_BYTE_56_DQPN_M,
						  V2_QPC_BYTE_56_DQPN_S);
	qp_attr->qp_access_flags = ((roce_get_bit(context.byte_76_srqn_op_en,
				    V2_QPC_BYTE_76_RRE_S)) << V2_QP_RRE_S) |
				    ((roce_get_bit(context.byte_76_srqn_op_en,
				    V2_QPC_BYTE_76_RWE_S)) << V2_QP_RWE_S) |
				    ((roce_get_bit(context.byte_76_srqn_op_en,
				    V2_QPC_BYTE_76_ATE_S)) << V2_QP_ATE_S);

	if (hr_qp->ibqp.qp_type == IB_QPT_RC ||
	    hr_qp->ibqp.qp_type == IB_QPT_UC) {
		struct ib_global_route *grh =
				rdma_ah_retrieve_grh(&qp_attr->ah_attr);

		rdma_ah_set_sl(&qp_attr->ah_attr,
			       roce_get_field(context.byte_28_at_fl,
					      V2_QPC_BYTE_28_SL_M,
					      V2_QPC_BYTE_28_SL_S));
		grh->flow_label = roce_get_field(context.byte_28_at_fl,
						 V2_QPC_BYTE_28_FL_M,
						 V2_QPC_BYTE_28_FL_S);
		grh->sgid_index = roce_get_field(context.byte_20_smac_sgid_idx,
						 V2_QPC_BYTE_20_SGID_IDX_M,
						 V2_QPC_BYTE_20_SGID_IDX_S);
		grh->hop_limit = roce_get_field(context.byte_24_mtu_tc,
						V2_QPC_BYTE_24_HOP_LIMIT_M,
						V2_QPC_BYTE_24_HOP_LIMIT_S);
		grh->traffic_class = roce_get_field(context.byte_24_mtu_tc,
						    V2_QPC_BYTE_24_TC_M,
						    V2_QPC_BYTE_24_TC_S);

		memcpy(grh->dgid.raw, context.dgid, sizeof(grh->dgid.raw));
	}

	qp_attr->port_num = hr_qp->port + 1;
	qp_attr->sq_draining = 0;
	qp_attr->max_rd_atomic = 1 << roce_get_field(context.byte_208_irrl,
						     V2_QPC_BYTE_208_SR_MAX_M,
						     V2_QPC_BYTE_208_SR_MAX_S);
	qp_attr->max_dest_rd_atomic = 1 << roce_get_field(context.byte_140_raq,
						     V2_QPC_BYTE_140_RR_MAX_M,
						     V2_QPC_BYTE_140_RR_MAX_S);
	qp_attr->min_rnr_timer = (u8)roce_get_field(context.byte_80_rnr_rx_cqn,
						 V2_QPC_BYTE_80_MIN_RNR_TIME_M,
						 V2_QPC_BYTE_80_MIN_RNR_TIME_S);
	qp_attr->timeout = (u8)roce_get_field(context.byte_28_at_fl,
					      V2_QPC_BYTE_28_AT_M,
					      V2_QPC_BYTE_28_AT_S);
	qp_attr->retry_cnt = roce_get_field(context.byte_212_lsn,
					    V2_QPC_BYTE_212_RETRY_CNT_M,
					    V2_QPC_BYTE_212_RETRY_CNT_S);
	qp_attr->rnr_retry = le32_to_cpu(context.rq_rnr_timer);

done:
	qp_attr->cur_qp_state = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr = hr_qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge = hr_qp->rq.max_gs;

	if (!ibqp->uobject) {
		qp_attr->cap.max_send_wr = hr_qp->sq.wqe_cnt;
		qp_attr->cap.max_send_sge = hr_qp->sq.max_gs;
	} else {
		qp_attr->cap.max_send_wr = 0;
		qp_attr->cap.max_send_sge = 0;
	}

	qp_init_attr->cap = qp_attr->cap;

out:
	mutex_unlock(&hr_qp->mutex);
	return ret;
}