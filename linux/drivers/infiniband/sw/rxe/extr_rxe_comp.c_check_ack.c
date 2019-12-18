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
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  opcode; } ;
struct rxe_send_wqe {void* status; TYPE_2__ wr; int /*<<< orphan*/  last_psn; int /*<<< orphan*/  first_psn; } ;
struct TYPE_8__ {int /*<<< orphan*/  task; int /*<<< orphan*/  wait_psn; } ;
struct TYPE_7__ {int opcode; int /*<<< orphan*/  psn; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct rxe_qp {TYPE_4__ req; TYPE_3__ comp; TYPE_1__ ibqp; } ;
struct rxe_pkt_info {unsigned int mask; int const opcode; int /*<<< orphan*/  psn; } ;
struct rxe_dev {int dummy; } ;
typedef  enum comp_state { ____Placeholder_comp_state } comp_state ;

/* Variables and functions */
#define  AETH_ACK 140 
#define  AETH_NAK 139 
#define  AETH_NAK_INVALID_REQ 138 
#define  AETH_NAK_PSN_SEQ_ERROR 137 
#define  AETH_NAK_REM_ACC_ERR 136 
#define  AETH_NAK_REM_OP_ERR 135 
#define  AETH_RNR_NAK 134 
 int AETH_TYPE_MASK ; 
 int COMPST_ATOMIC ; 
 int COMPST_ERROR ; 
 int COMPST_ERROR_RETRY ; 
 int COMPST_READ ; 
 int COMPST_RNR_RETRY ; 
 int COMPST_WRITE_SEND ; 
#define  IB_OPCODE_RC_ACKNOWLEDGE 133 
#define  IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE 132 
#define  IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST 131 
#define  IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST 130 
#define  IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE 129 
#define  IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY 128 
 void* IB_WC_FATAL_ERR ; 
 void* IB_WC_REM_ACCESS_ERR ; 
 void* IB_WC_REM_INV_REQ_ERR ; 
 void* IB_WC_REM_OP_ERR ; 
 int /*<<< orphan*/  IB_WR_ATOMIC_CMP_AND_SWP ; 
 int /*<<< orphan*/  IB_WR_ATOMIC_FETCH_AND_ADD ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ ; 
 int /*<<< orphan*/  IB_WR_RDMA_READ_WITH_INV ; 
 int /*<<< orphan*/  RXE_CNT_RCV_RNR ; 
 int /*<<< orphan*/  RXE_CNT_RCV_SEQ_ERR ; 
 unsigned int RXE_START_MASK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int aeth_syn (struct rxe_pkt_info*) ; 
 int /*<<< orphan*/  pr_warn (char*,...) ; 
 int /*<<< orphan*/  psn_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_retry_counters (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_counter_inc (struct rxe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_run_task (int /*<<< orphan*/ *,int) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline enum comp_state check_ack(struct rxe_qp *qp,
					struct rxe_pkt_info *pkt,
					struct rxe_send_wqe *wqe)
{
	unsigned int mask = pkt->mask;
	u8 syn;
	struct rxe_dev *rxe = to_rdev(qp->ibqp.device);

	/* Check the sequence only */
	switch (qp->comp.opcode) {
	case -1:
		/* Will catch all *_ONLY cases. */
		if (!(mask & RXE_START_MASK))
			return COMPST_ERROR;

		break;

	case IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST:
	case IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE:
		if (pkt->opcode != IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE &&
		    pkt->opcode != IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST) {
			/* read retries of partial data may restart from
			 * read response first or response only.
			 */
			if ((pkt->psn == wqe->first_psn &&
			     pkt->opcode ==
			     IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST) ||
			    (wqe->first_psn == wqe->last_psn &&
			     pkt->opcode ==
			     IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY))
				break;

			return COMPST_ERROR;
		}
		break;
	default:
		WARN_ON_ONCE(1);
	}

	/* Check operation validity. */
	switch (pkt->opcode) {
	case IB_OPCODE_RC_RDMA_READ_RESPONSE_FIRST:
	case IB_OPCODE_RC_RDMA_READ_RESPONSE_LAST:
	case IB_OPCODE_RC_RDMA_READ_RESPONSE_ONLY:
		syn = aeth_syn(pkt);

		if ((syn & AETH_TYPE_MASK) != AETH_ACK)
			return COMPST_ERROR;

		/* fall through */
		/* (IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE doesn't have an AETH)
		 */
	case IB_OPCODE_RC_RDMA_READ_RESPONSE_MIDDLE:
		if (wqe->wr.opcode != IB_WR_RDMA_READ &&
		    wqe->wr.opcode != IB_WR_RDMA_READ_WITH_INV) {
			wqe->status = IB_WC_FATAL_ERR;
			return COMPST_ERROR;
		}
		reset_retry_counters(qp);
		return COMPST_READ;

	case IB_OPCODE_RC_ATOMIC_ACKNOWLEDGE:
		syn = aeth_syn(pkt);

		if ((syn & AETH_TYPE_MASK) != AETH_ACK)
			return COMPST_ERROR;

		if (wqe->wr.opcode != IB_WR_ATOMIC_CMP_AND_SWP &&
		    wqe->wr.opcode != IB_WR_ATOMIC_FETCH_AND_ADD)
			return COMPST_ERROR;
		reset_retry_counters(qp);
		return COMPST_ATOMIC;

	case IB_OPCODE_RC_ACKNOWLEDGE:
		syn = aeth_syn(pkt);
		switch (syn & AETH_TYPE_MASK) {
		case AETH_ACK:
			reset_retry_counters(qp);
			return COMPST_WRITE_SEND;

		case AETH_RNR_NAK:
			rxe_counter_inc(rxe, RXE_CNT_RCV_RNR);
			return COMPST_RNR_RETRY;

		case AETH_NAK:
			switch (syn) {
			case AETH_NAK_PSN_SEQ_ERROR:
				/* a nak implicitly acks all packets with psns
				 * before
				 */
				if (psn_compare(pkt->psn, qp->comp.psn) > 0) {
					rxe_counter_inc(rxe,
							RXE_CNT_RCV_SEQ_ERR);
					qp->comp.psn = pkt->psn;
					if (qp->req.wait_psn) {
						qp->req.wait_psn = 0;
						rxe_run_task(&qp->req.task, 1);
					}
				}
				return COMPST_ERROR_RETRY;

			case AETH_NAK_INVALID_REQ:
				wqe->status = IB_WC_REM_INV_REQ_ERR;
				return COMPST_ERROR;

			case AETH_NAK_REM_ACC_ERR:
				wqe->status = IB_WC_REM_ACCESS_ERR;
				return COMPST_ERROR;

			case AETH_NAK_REM_OP_ERR:
				wqe->status = IB_WC_REM_OP_ERR;
				return COMPST_ERROR;

			default:
				pr_warn("unexpected nak %x\n", syn);
				wqe->status = IB_WC_REM_OP_ERR;
				return COMPST_ERROR;
			}

		default:
			return COMPST_ERROR;
		}
		break;

	default:
		pr_warn("unexpected opcode\n");
	}

	return COMPST_ERROR;
}