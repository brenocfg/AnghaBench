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
struct ib_qp_attr {int qp_access_flags; scalar_t__ qkey; } ;
struct ib_qp {scalar_t__ qp_type; scalar_t__ srq; int /*<<< orphan*/  send_cq; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  pd; } ;
struct hns_roce_v2_qp_context {int /*<<< orphan*/  byte_168_irrl_idx; int /*<<< orphan*/  byte_56_dqpn_err; int /*<<< orphan*/  byte_4_sqpn_tst; scalar_t__ qkey_xrcd; int /*<<< orphan*/  byte_76_srqn_op_en; int /*<<< orphan*/  byte_252_err_txcqn; int /*<<< orphan*/  byte_80_rnr_rx_cqn; int /*<<< orphan*/  byte_16_buf_ba_pg_sz; int /*<<< orphan*/  byte_20_smac_sgid_idx; } ;
struct TYPE_11__ {int max_gs; scalar_t__ wqe_cnt; } ;
struct TYPE_10__ {scalar_t__ wqe_cnt; } ;
struct TYPE_9__ {scalar_t__ sge_cnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  qp_type; } ;
struct hns_roce_qp {int access_flags; TYPE_4__ sq; int /*<<< orphan*/  qpn; TYPE_3__ rq; TYPE_2__ sge; TYPE_1__ ibqp; } ;
struct TYPE_14__ {int /*<<< orphan*/  cqn; } ;
struct TYPE_13__ {int /*<<< orphan*/  pdn; } ;
struct TYPE_12__ {int /*<<< orphan*/  srqn; } ;

/* Variables and functions */
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 scalar_t__ IB_QPT_GSI ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_DEST_QPN ; 
 int IB_QP_QKEY ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_SHIFT_BAK_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_168_SQ_SHIFT_BAK_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_PD_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_16_PD_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SQ_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SQ_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_252_TX_CQN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_252_TX_CQN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SGE_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SGE_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SQPN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SQPN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_TST_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_TST_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_DQPN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_56_DQPN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_ATE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RRE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RWE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_SRQN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_SRQN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_SRQ_EN_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_RX_CQN_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_80_RX_CQN_S ; 
 int /*<<< orphan*/  ilog2 (unsigned int) ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* to_hr_cq (int /*<<< orphan*/ ) ; 
 TYPE_6__* to_hr_pd (int /*<<< orphan*/ ) ; 
 struct hns_roce_qp* to_hr_qp (struct ib_qp*) ; 
 int /*<<< orphan*/  to_hr_qp_type (int /*<<< orphan*/ ) ; 
 TYPE_5__* to_hr_srq (scalar_t__) ; 

__attribute__((used)) static void modify_qp_init_to_init(struct ib_qp *ibqp,
				   const struct ib_qp_attr *attr, int attr_mask,
				   struct hns_roce_v2_qp_context *context,
				   struct hns_roce_v2_qp_context *qpc_mask)
{
	struct hns_roce_qp *hr_qp = to_hr_qp(ibqp);

	/*
	 * In v2 engine, software pass context and context mask to hardware
	 * when modifying qp. If software need modify some fields in context,
	 * we should set all bits of the relevant fields in context mask to
	 * 0 at the same time, else set them to 0x1.
	 */
	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_TST_M,
		       V2_QPC_BYTE_4_TST_S, to_hr_qp_type(hr_qp->ibqp.qp_type));
	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_TST_M,
		       V2_QPC_BYTE_4_TST_S, 0);

	if (ibqp->qp_type == IB_QPT_GSI)
		roce_set_field(context->byte_4_sqpn_tst,
			       V2_QPC_BYTE_4_SGE_SHIFT_M,
			       V2_QPC_BYTE_4_SGE_SHIFT_S,
			       ilog2((unsigned int)hr_qp->sge.sge_cnt));
	else
		roce_set_field(context->byte_4_sqpn_tst,
			       V2_QPC_BYTE_4_SGE_SHIFT_M,
			       V2_QPC_BYTE_4_SGE_SHIFT_S, hr_qp->sq.max_gs > 2 ?
			       ilog2((unsigned int)hr_qp->sge.sge_cnt) : 0);

	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_SGE_SHIFT_M,
		       V2_QPC_BYTE_4_SGE_SHIFT_S, 0);

	if (attr_mask & IB_QP_ACCESS_FLAGS) {
		roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S,
			     !!(attr->qp_access_flags & IB_ACCESS_REMOTE_READ));
		roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S,
			     0);

		roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S,
			     !!(attr->qp_access_flags &
			     IB_ACCESS_REMOTE_WRITE));
		roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S,
			     0);

		roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S,
			     !!(attr->qp_access_flags &
			     IB_ACCESS_REMOTE_ATOMIC));
		roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S,
			     0);
	} else {
		roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S,
			     !!(hr_qp->access_flags & IB_ACCESS_REMOTE_READ));
		roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S,
			     0);

		roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S,
			     !!(hr_qp->access_flags & IB_ACCESS_REMOTE_WRITE));
		roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S,
			     0);

		roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S,
			     !!(hr_qp->access_flags & IB_ACCESS_REMOTE_ATOMIC));
		roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S,
			     0);
	}

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SQ_SHIFT_M, V2_QPC_BYTE_20_SQ_SHIFT_S,
		       ilog2((unsigned int)hr_qp->sq.wqe_cnt));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SQ_SHIFT_M, V2_QPC_BYTE_20_SQ_SHIFT_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_SHIFT_M, V2_QPC_BYTE_20_RQ_SHIFT_S,
		       ilog2((unsigned int)hr_qp->rq.wqe_cnt));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_SHIFT_M, V2_QPC_BYTE_20_RQ_SHIFT_S, 0);

	roce_set_field(context->byte_16_buf_ba_pg_sz, V2_QPC_BYTE_16_PD_M,
		       V2_QPC_BYTE_16_PD_S, to_hr_pd(ibqp->pd)->pdn);
	roce_set_field(qpc_mask->byte_16_buf_ba_pg_sz, V2_QPC_BYTE_16_PD_M,
		       V2_QPC_BYTE_16_PD_S, 0);

	roce_set_field(context->byte_80_rnr_rx_cqn, V2_QPC_BYTE_80_RX_CQN_M,
		       V2_QPC_BYTE_80_RX_CQN_S, to_hr_cq(ibqp->recv_cq)->cqn);
	roce_set_field(qpc_mask->byte_80_rnr_rx_cqn, V2_QPC_BYTE_80_RX_CQN_M,
		       V2_QPC_BYTE_80_RX_CQN_S, 0);

	roce_set_field(context->byte_252_err_txcqn, V2_QPC_BYTE_252_TX_CQN_M,
		       V2_QPC_BYTE_252_TX_CQN_S, to_hr_cq(ibqp->send_cq)->cqn);
	roce_set_field(qpc_mask->byte_252_err_txcqn, V2_QPC_BYTE_252_TX_CQN_M,
		       V2_QPC_BYTE_252_TX_CQN_S, 0);

	if (ibqp->srq) {
		roce_set_bit(context->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_SRQ_EN_S, 1);
		roce_set_bit(qpc_mask->byte_76_srqn_op_en,
			     V2_QPC_BYTE_76_SRQ_EN_S, 0);
		roce_set_field(context->byte_76_srqn_op_en,
			       V2_QPC_BYTE_76_SRQN_M, V2_QPC_BYTE_76_SRQN_S,
			       to_hr_srq(ibqp->srq)->srqn);
		roce_set_field(qpc_mask->byte_76_srqn_op_en,
			       V2_QPC_BYTE_76_SRQN_M, V2_QPC_BYTE_76_SRQN_S, 0);
	}

	if (attr_mask & IB_QP_QKEY) {
		context->qkey_xrcd = attr->qkey;
		qpc_mask->qkey_xrcd = 0;
	}

	roce_set_field(context->byte_4_sqpn_tst, V2_QPC_BYTE_4_SQPN_M,
		       V2_QPC_BYTE_4_SQPN_S, hr_qp->qpn);
	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_SQPN_M,
		       V2_QPC_BYTE_4_SQPN_S, 0);

	if (attr_mask & IB_QP_DEST_QPN) {
		roce_set_field(context->byte_56_dqpn_err, V2_QPC_BYTE_56_DQPN_M,
			       V2_QPC_BYTE_56_DQPN_S, hr_qp->qpn);
		roce_set_field(qpc_mask->byte_56_dqpn_err,
			       V2_QPC_BYTE_56_DQPN_M, V2_QPC_BYTE_56_DQPN_S, 0);
	}
	roce_set_field(context->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_M,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_S,
		       ilog2((unsigned int)hr_qp->sq.wqe_cnt));
	roce_set_field(qpc_mask->byte_168_irrl_idx,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_M,
		       V2_QPC_BYTE_168_SQ_SHIFT_BAK_S, 0);
}