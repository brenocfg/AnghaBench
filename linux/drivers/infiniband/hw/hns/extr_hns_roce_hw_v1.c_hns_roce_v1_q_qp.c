#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_12__ {int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; } ;
struct TYPE_16__ {int /*<<< orphan*/  type; } ;
struct ib_qp_init_attr {int qp_state; int path_mtu; int rq_psn; int qp_access_flags; int pkey_index; int max_rd_atomic; int max_dest_rd_atomic; int retry_cnt; int cur_qp_state; TYPE_3__ cap; void* rnr_retry; void* timeout; void* min_rnr_timer; scalar_t__ sq_draining; scalar_t__ port_num; TYPE_7__ ah_attr; void* dest_qp_num; scalar_t__ sq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; } ;
struct ib_qp_attr {int qp_state; int path_mtu; int rq_psn; int qp_access_flags; int pkey_index; int max_rd_atomic; int max_dest_rd_atomic; int retry_cnt; int cur_qp_state; TYPE_3__ cap; void* rnr_retry; void* timeout; void* min_rnr_timer; scalar_t__ sq_draining; scalar_t__ port_num; TYPE_7__ ah_attr; void* dest_qp_num; scalar_t__ sq_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  path_mig_state; } ;
struct ib_qp {int /*<<< orphan*/  uobject; int /*<<< orphan*/  device; } ;
struct TYPE_15__ {int /*<<< orphan*/  raw; } ;
struct ib_global_route {int flow_label; int sgid_index; int hop_limit; int traffic_class; TYPE_6__ dgid; } ;
struct hns_roce_qp_context {int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  qpc_bytes_148; int /*<<< orphan*/  qpc_bytes_156; int /*<<< orphan*/  qpc_bytes_24; int /*<<< orphan*/  qpc_bytes_32; int /*<<< orphan*/  qpc_bytes_12; int /*<<< orphan*/  dgid; int /*<<< orphan*/  qpc_bytes_48; int /*<<< orphan*/  qpc_bytes_44; int /*<<< orphan*/  qpc_bytes_36; int /*<<< orphan*/  qpc_bytes_4; int /*<<< orphan*/  qpc_bytes_164; int /*<<< orphan*/  qpc_bytes_88; int /*<<< orphan*/  qpc_bytes_144; } ;
struct TYPE_11__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_10__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_14__ {scalar_t__ qp_type; } ;
struct hns_roce_qp {int state; int /*<<< orphan*/  mutex; TYPE_2__ sq; TYPE_1__ rq; scalar_t__ port; TYPE_5__ ibqp; } ;
struct hns_roce_dev {TYPE_4__* pdev; } ;
struct device {int dummy; } ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;
typedef  enum hns_roce_qp_state { ____Placeholder_hns_roce_qp_state } hns_roce_qp_state ;
struct TYPE_13__ {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_AH_GRH ; 
 int /*<<< orphan*/  IB_MIG_ARMED ; 
 int IB_QPS_RESET ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ IB_QPT_UD ; 
 int /*<<< orphan*/  QKEY_VAL ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_144_QP_STATE_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_144_QP_STATE_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_156_SL_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_156_SL_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_164_SQ_PSN_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_164_SQ_PSN_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_36_DEST_QP_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_36_DEST_QP_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_44_HOPLMT_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_44_HOPLMT_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_48_MTU_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_48_MTU_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_48_TCLASS_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_48_TCLASS_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_M ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTE_4_ATOMIC_OPERATION_ENABLE_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTE_4_RDMA_READ_ENABLE_S ; 
 int /*<<< orphan*/  QP_CONTEXT_QPC_BYTE_4_RDMA_WRITE_ENABLE_S ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int hns_roce_v1_query_qpc (struct hns_roce_dev*,struct hns_roce_qp*,struct hns_roce_qp_context*) ; 
 int /*<<< orphan*/  kfree (struct hns_roce_qp_context*) ; 
 struct hns_roce_qp_context* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ib_global_route* rdma_ah_retrieve_grh (TYPE_7__*) ; 
 int /*<<< orphan*/  rdma_ah_set_ah_flags (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (TYPE_7__*,int) ; 
 int roce_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roce_get_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hns_roce_dev* to_hr_dev (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 scalar_t__ to_ib_qp_state (int) ; 

__attribute__((used)) static int hns_roce_v1_q_qp(struct ib_qp *ibqp, struct ib_qp_attr *qp_attr,
			    int qp_attr_mask,
			    struct ib_qp_init_attr *qp_init_attr)
{
	struct hns_roce_dev *hr_dev = to_hr_dev(ibqp->device);
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);
	struct device *dev = &hr_dev->pdev->dev;
	struct hns_roce_qp_context *context;
	int tmp_qp_state = 0;
	int ret = 0;
	int state;

	context = kzalloc(sizeof(*context), GFP_KERNEL);
	if (!context)
		return -ENOMEM;

	memset(qp_attr, 0, sizeof(*qp_attr));
	memset(qp_init_attr, 0, sizeof(*qp_init_attr));

	mutex_lock(&hr_qp->mutex);

	if (hr_qp->state == IB_QPS_RESET) {
		qp_attr->qp_state = IB_QPS_RESET;
		goto done;
	}

	ret = hns_roce_v1_query_qpc(hr_dev, hr_qp, context);
	if (ret) {
		dev_err(dev, "query qpc error\n");
		ret = -EINVAL;
		goto out;
	}

	state = roce_get_field(context->qpc_bytes_144,
			       QP_CONTEXT_QPC_BYTES_144_QP_STATE_M,
			       QP_CONTEXT_QPC_BYTES_144_QP_STATE_S);
	tmp_qp_state = (int)to_ib_qp_state((enum hns_roce_qp_state)state);
	if (tmp_qp_state == -1) {
		dev_err(dev, "to_ib_qp_state error\n");
		ret = -EINVAL;
		goto out;
	}
	hr_qp->state = (u8)tmp_qp_state;
	qp_attr->qp_state = (enum ib_qp_state)hr_qp->state;
	qp_attr->path_mtu = (enum ib_mtu)roce_get_field(context->qpc_bytes_48,
					       QP_CONTEXT_QPC_BYTES_48_MTU_M,
					       QP_CONTEXT_QPC_BYTES_48_MTU_S);
	qp_attr->path_mig_state = IB_MIG_ARMED;
	qp_attr->ah_attr.type   = RDMA_AH_ATTR_TYPE_ROCE;
	if (hr_qp->ibqp.qp_type == IB_QPT_UD)
		qp_attr->qkey = QKEY_VAL;

	qp_attr->rq_psn = roce_get_field(context->qpc_bytes_88,
					 QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_M,
					 QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_S);
	qp_attr->sq_psn = (u32)roce_get_field(context->qpc_bytes_164,
					     QP_CONTEXT_QPC_BYTES_164_SQ_PSN_M,
					     QP_CONTEXT_QPC_BYTES_164_SQ_PSN_S);
	qp_attr->dest_qp_num = (u8)roce_get_field(context->qpc_bytes_36,
					QP_CONTEXT_QPC_BYTES_36_DEST_QP_M,
					QP_CONTEXT_QPC_BYTES_36_DEST_QP_S);
	qp_attr->qp_access_flags = ((roce_get_bit(context->qpc_bytes_4,
			QP_CONTEXT_QPC_BYTE_4_RDMA_READ_ENABLE_S)) << 2) |
				   ((roce_get_bit(context->qpc_bytes_4,
			QP_CONTEXT_QPC_BYTE_4_RDMA_WRITE_ENABLE_S)) << 1) |
				   ((roce_get_bit(context->qpc_bytes_4,
			QP_CONTEXT_QPC_BYTE_4_ATOMIC_OPERATION_ENABLE_S)) << 3);

	if (hr_qp->ibqp.qp_type == IB_QPT_RC ||
	    hr_qp->ibqp.qp_type == IB_QPT_UC) {
		struct ib_global_route *grh =
			rdma_ah_retrieve_grh(&qp_attr->ah_attr);

		rdma_ah_set_sl(&qp_attr->ah_attr,
			       roce_get_field(context->qpc_bytes_156,
					      QP_CONTEXT_QPC_BYTES_156_SL_M,
					      QP_CONTEXT_QPC_BYTES_156_SL_S));
		rdma_ah_set_ah_flags(&qp_attr->ah_attr, IB_AH_GRH);
		grh->flow_label =
			roce_get_field(context->qpc_bytes_48,
				       QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_M,
				       QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_S);
		grh->sgid_index =
			roce_get_field(context->qpc_bytes_36,
				       QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_M,
				       QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_S);
		grh->hop_limit =
			roce_get_field(context->qpc_bytes_44,
				       QP_CONTEXT_QPC_BYTES_44_HOPLMT_M,
				       QP_CONTEXT_QPC_BYTES_44_HOPLMT_S);
		grh->traffic_class =
			roce_get_field(context->qpc_bytes_48,
				       QP_CONTEXT_QPC_BYTES_48_TCLASS_M,
				       QP_CONTEXT_QPC_BYTES_48_TCLASS_S);

		memcpy(grh->dgid.raw, context->dgid,
		       sizeof(grh->dgid.raw));
	}

	qp_attr->pkey_index = roce_get_field(context->qpc_bytes_12,
			      QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_M,
			      QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S);
	qp_attr->port_num = hr_qp->port + 1;
	qp_attr->sq_draining = 0;
	qp_attr->max_rd_atomic = 1 << roce_get_field(context->qpc_bytes_156,
				 QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_M,
				 QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_S);
	qp_attr->max_dest_rd_atomic = 1 << roce_get_field(context->qpc_bytes_32,
				 QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_M,
				 QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_S);
	qp_attr->min_rnr_timer = (u8)(roce_get_field(context->qpc_bytes_24,
			QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_M,
			QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_S));
	qp_attr->timeout = (u8)(roce_get_field(context->qpc_bytes_156,
			    QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_M,
			    QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_S));
	qp_attr->retry_cnt = roce_get_field(context->qpc_bytes_148,
			     QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_M,
			     QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_S);
	qp_attr->rnr_retry = (u8)le32_to_cpu(context->rnr_retry);

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
	kfree(context);
	return ret;
}