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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct ib_qp_attr {int qp_access_flags; int /*<<< orphan*/  max_dest_rd_atomic; } ;
struct hns_roce_v2_qp_context {int /*<<< orphan*/  byte_76_srqn_op_en; } ;
struct hns_roce_qp {int atomic_rd_en; int /*<<< orphan*/  resp_depth; } ;

/* Variables and functions */
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_MAX_DEST_RD_ATOMIC ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_ATE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RRE_S ; 
 int /*<<< orphan*/  V2_QPC_BYTE_76_RWE_S ; 
 int /*<<< orphan*/  roce_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_access_flags(struct hns_roce_qp *hr_qp,
			     struct hns_roce_v2_qp_context *context,
			     struct hns_roce_v2_qp_context *qpc_mask,
			     const struct ib_qp_attr *attr, int attr_mask)
{
	u8 dest_rd_atomic;
	u32 access_flags;

	dest_rd_atomic = (attr_mask & IB_QP_MAX_DEST_RD_ATOMIC) ?
			 attr->max_dest_rd_atomic : hr_qp->resp_depth;

	access_flags = (attr_mask & IB_QP_ACCESS_FLAGS) ?
		       attr->qp_access_flags : hr_qp->atomic_rd_en;

	if (!dest_rd_atomic)
		access_flags &= IB_ACCESS_REMOTE_WRITE;

	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S,
		     !!(access_flags & IB_ACCESS_REMOTE_READ));
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RRE_S, 0);

	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S,
		     !!(access_flags & IB_ACCESS_REMOTE_WRITE));
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_RWE_S, 0);

	roce_set_bit(context->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S,
		     !!(access_flags & IB_ACCESS_REMOTE_ATOMIC));
	roce_set_bit(qpc_mask->byte_76_srqn_op_en, V2_QPC_BYTE_76_ATE_S, 0);
}