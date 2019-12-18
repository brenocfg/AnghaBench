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
struct hns_roce_v2_qp_context {int /*<<< orphan*/  byte_20_smac_sgid_idx; int /*<<< orphan*/  byte_4_sqpn_tst; } ;
struct TYPE_8__ {scalar_t__ wqe_cnt; } ;
struct TYPE_7__ {scalar_t__ qp_type; scalar_t__ srq; } ;
struct TYPE_6__ {scalar_t__ max_gs; scalar_t__ wqe_cnt; } ;
struct TYPE_5__ {scalar_t__ sge_cnt; } ;
struct hns_roce_qp {TYPE_4__ rq; TYPE_3__ ibqp; TYPE_2__ sq; TYPE_1__ sge; } ;

/* Variables and functions */
 scalar_t__ HNS_ROCE_V2_UC_RC_SGE_NUM_IN_WQE ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_XRC_INI ; 
 scalar_t__ IB_QPT_XRC_TGT ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_RQ_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SQ_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_20_SQ_SHIFT_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SGE_SHIFT_M ; 
 int /*<<< orphan*/  V2_QPC_BYTE_4_SGE_SHIFT_S ; 
 int /*<<< orphan*/  ilog2 (unsigned int) ; 
 int /*<<< orphan*/  roce_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_qpc_wqe_cnt(struct hns_roce_qp *hr_qp,
			    struct hns_roce_v2_qp_context *context,
			    struct hns_roce_v2_qp_context *qpc_mask)
{
	if (hr_qp->ibqp.qp_type == IB_QPT_GSI)
		roce_set_field(context->byte_4_sqpn_tst,
			       V2_QPC_BYTE_4_SGE_SHIFT_M,
			       V2_QPC_BYTE_4_SGE_SHIFT_S,
			       ilog2((unsigned int)hr_qp->sge.sge_cnt));
	else
		roce_set_field(context->byte_4_sqpn_tst,
			       V2_QPC_BYTE_4_SGE_SHIFT_M,
			       V2_QPC_BYTE_4_SGE_SHIFT_S,
			       hr_qp->sq.max_gs >
			       HNS_ROCE_V2_UC_RC_SGE_NUM_IN_WQE ?
			       ilog2((unsigned int)hr_qp->sge.sge_cnt) : 0);

	roce_set_field(qpc_mask->byte_4_sqpn_tst, V2_QPC_BYTE_4_SGE_SHIFT_M,
		       V2_QPC_BYTE_4_SGE_SHIFT_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SQ_SHIFT_M, V2_QPC_BYTE_20_SQ_SHIFT_S,
		       ilog2((unsigned int)hr_qp->sq.wqe_cnt));
	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_SQ_SHIFT_M, V2_QPC_BYTE_20_SQ_SHIFT_S, 0);

	roce_set_field(context->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_SHIFT_M, V2_QPC_BYTE_20_RQ_SHIFT_S,
		       (hr_qp->ibqp.qp_type == IB_QPT_XRC_INI ||
		       hr_qp->ibqp.qp_type == IB_QPT_XRC_TGT ||
		       hr_qp->ibqp.srq) ? 0 :
		       ilog2((unsigned int)hr_qp->rq.wqe_cnt));

	roce_set_field(qpc_mask->byte_20_smac_sgid_idx,
		       V2_QPC_BYTE_20_RQ_SHIFT_M, V2_QPC_BYTE_20_RQ_SHIFT_S, 0);
}