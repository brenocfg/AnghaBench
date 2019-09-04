#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int drop_msg; int /*<<< orphan*/  opcode; } ;
struct rxe_qp {TYPE_1__ resp; } ;
struct rxe_pkt_info {int /*<<< orphan*/  opcode; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;

/* Variables and functions */
#define  IB_OPCODE_RC_RDMA_WRITE_FIRST 146 
#define  IB_OPCODE_RC_RDMA_WRITE_LAST 145 
#define  IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE 144 
#define  IB_OPCODE_RC_RDMA_WRITE_MIDDLE 143 
#define  IB_OPCODE_RC_SEND_FIRST 142 
#define  IB_OPCODE_RC_SEND_LAST 141 
#define  IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE 140 
#define  IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE 139 
#define  IB_OPCODE_RC_SEND_MIDDLE 138 
#define  IB_OPCODE_UC_RDMA_WRITE_FIRST 137 
#define  IB_OPCODE_UC_RDMA_WRITE_LAST 136 
#define  IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE 135 
#define  IB_OPCODE_UC_RDMA_WRITE_MIDDLE 134 
#define  IB_OPCODE_UC_SEND_FIRST 133 
#define  IB_OPCODE_UC_SEND_LAST 132 
#define  IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE 131 
#define  IB_OPCODE_UC_SEND_MIDDLE 130 
#define  IB_QPT_RC 129 
#define  IB_QPT_UC 128 
 int RESPST_CHK_OP_VALID ; 
 int RESPST_CLEANUP ; 
 int RESPST_ERR_MISSING_OPCODE_FIRST ; 
 int RESPST_ERR_MISSING_OPCODE_LAST_C ; 
 int RESPST_ERR_MISSING_OPCODE_LAST_D1E ; 
 int qp_type (struct rxe_qp*) ; 

__attribute__((used)) static enum resp_states check_op_seq(struct rxe_qp *qp,
				     struct rxe_pkt_info *pkt)
{
	switch (qp_type(qp)) {
	case IB_QPT_RC:
		switch (qp->resp.opcode) {
		case IB_OPCODE_RC_SEND_FIRST:
		case IB_OPCODE_RC_SEND_MIDDLE:
			switch (pkt->opcode) {
			case IB_OPCODE_RC_SEND_MIDDLE:
			case IB_OPCODE_RC_SEND_LAST:
			case IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE:
			case IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE:
				return RESPST_CHK_OP_VALID;
			default:
				return RESPST_ERR_MISSING_OPCODE_LAST_C;
			}

		case IB_OPCODE_RC_RDMA_WRITE_FIRST:
		case IB_OPCODE_RC_RDMA_WRITE_MIDDLE:
			switch (pkt->opcode) {
			case IB_OPCODE_RC_RDMA_WRITE_MIDDLE:
			case IB_OPCODE_RC_RDMA_WRITE_LAST:
			case IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				return RESPST_CHK_OP_VALID;
			default:
				return RESPST_ERR_MISSING_OPCODE_LAST_C;
			}

		default:
			switch (pkt->opcode) {
			case IB_OPCODE_RC_SEND_MIDDLE:
			case IB_OPCODE_RC_SEND_LAST:
			case IB_OPCODE_RC_SEND_LAST_WITH_IMMEDIATE:
			case IB_OPCODE_RC_SEND_LAST_WITH_INVALIDATE:
			case IB_OPCODE_RC_RDMA_WRITE_MIDDLE:
			case IB_OPCODE_RC_RDMA_WRITE_LAST:
			case IB_OPCODE_RC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				return RESPST_ERR_MISSING_OPCODE_FIRST;
			default:
				return RESPST_CHK_OP_VALID;
			}
		}
		break;

	case IB_QPT_UC:
		switch (qp->resp.opcode) {
		case IB_OPCODE_UC_SEND_FIRST:
		case IB_OPCODE_UC_SEND_MIDDLE:
			switch (pkt->opcode) {
			case IB_OPCODE_UC_SEND_MIDDLE:
			case IB_OPCODE_UC_SEND_LAST:
			case IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE:
				return RESPST_CHK_OP_VALID;
			default:
				return RESPST_ERR_MISSING_OPCODE_LAST_D1E;
			}

		case IB_OPCODE_UC_RDMA_WRITE_FIRST:
		case IB_OPCODE_UC_RDMA_WRITE_MIDDLE:
			switch (pkt->opcode) {
			case IB_OPCODE_UC_RDMA_WRITE_MIDDLE:
			case IB_OPCODE_UC_RDMA_WRITE_LAST:
			case IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				return RESPST_CHK_OP_VALID;
			default:
				return RESPST_ERR_MISSING_OPCODE_LAST_D1E;
			}

		default:
			switch (pkt->opcode) {
			case IB_OPCODE_UC_SEND_MIDDLE:
			case IB_OPCODE_UC_SEND_LAST:
			case IB_OPCODE_UC_SEND_LAST_WITH_IMMEDIATE:
			case IB_OPCODE_UC_RDMA_WRITE_MIDDLE:
			case IB_OPCODE_UC_RDMA_WRITE_LAST:
			case IB_OPCODE_UC_RDMA_WRITE_LAST_WITH_IMMEDIATE:
				qp->resp.drop_msg = 1;
				return RESPST_CLEANUP;
			default:
				return RESPST_CHK_OP_VALID;
			}
		}
		break;

	default:
		return RESPST_CHK_OP_VALID;
	}
}