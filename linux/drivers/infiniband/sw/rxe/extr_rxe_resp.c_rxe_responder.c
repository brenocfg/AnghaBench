#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int state; int drop_msg; int /*<<< orphan*/  goto_error; int /*<<< orphan*/ * wqe; void* status; int /*<<< orphan*/  psn; int /*<<< orphan*/  aeth_syndrome; } ;
struct TYPE_5__ {int min_rnr_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct rxe_qp {TYPE_3__ resp; int /*<<< orphan*/  srq; TYPE_2__ attr; int /*<<< orphan*/  valid; TYPE_1__ ibqp; } ;
struct rxe_pkt_info {int /*<<< orphan*/  psn; } ;
struct rxe_dev {int dummy; } ;
typedef  enum resp_states { ____Placeholder_resp_states } resp_states ;

/* Variables and functions */
 int /*<<< orphan*/  AETH_ACK_UNLIMITED ; 
 int /*<<< orphan*/  AETH_NAK_INVALID_REQ ; 
 int AETH_NAK_PSN_SEQ_ERROR ; 
 int /*<<< orphan*/  AETH_NAK_REM_ACC_ERR ; 
 int /*<<< orphan*/  AETH_NAK_REM_OP_ERR ; 
 int AETH_RNR_NAK ; 
 int AETH_TYPE_MASK ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  IB_QPT_RC ; 
 void* IB_WC_LOC_QP_OP_ERR ; 
 void* IB_WC_REM_ACCESS_ERR ; 
 void* IB_WC_REM_INV_REQ_ERR ; 
#define  QP_STATE_RESET 157 
#define  RESPST_ACKNOWLEDGE 156 
#define  RESPST_CHK_LENGTH 155 
#define  RESPST_CHK_OP_SEQ 154 
#define  RESPST_CHK_OP_VALID 153 
#define  RESPST_CHK_PSN 152 
#define  RESPST_CHK_RESOURCE 151 
#define  RESPST_CHK_RKEY 150 
#define  RESPST_CLEANUP 149 
#define  RESPST_COMPLETE 148 
#define  RESPST_DONE 147 
#define  RESPST_DUPLICATE_REQUEST 146 
#define  RESPST_ERROR 145 
#define  RESPST_ERR_CQ_OVERFLOW 144 
#define  RESPST_ERR_LENGTH 143 
#define  RESPST_ERR_MALFORMED_WQE 142 
#define  RESPST_ERR_MISALIGNED_ATOMIC 141 
#define  RESPST_ERR_MISSING_OPCODE_FIRST 140 
#define  RESPST_ERR_MISSING_OPCODE_LAST_C 139 
#define  RESPST_ERR_MISSING_OPCODE_LAST_D1E 138 
#define  RESPST_ERR_PSN_OUT_OF_SEQ 137 
#define  RESPST_ERR_RKEY_VIOLATION 136 
#define  RESPST_ERR_RNR 135 
#define  RESPST_ERR_TOO_MANY_RDMA_ATM_REQ 134 
#define  RESPST_ERR_UNSUPPORTED_OPCODE 133 
#define  RESPST_EXECUTE 132 
#define  RESPST_EXIT 131 
#define  RESPST_GET_REQ 130 
#define  RESPST_READ_REPLY 129 
#define  RESPST_RESET 128 
 int /*<<< orphan*/  RXE_CNT_SND_RNR ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int acknowledge (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int check_length (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int check_op_seq (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int check_op_valid (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int check_psn (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int check_resource (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int check_rkey (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int cleanup (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int /*<<< orphan*/  do_class_ac_error (struct rxe_qp*,int /*<<< orphan*/ ,void*) ; 
 int do_class_d1e_error (struct rxe_qp*) ; 
 int do_complete (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int duplicate_request (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int execute (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int get_req (struct rxe_qp*,struct rxe_pkt_info**) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qp_num (struct rxe_qp*) ; 
 int /*<<< orphan*/  qp_type (struct rxe_qp*) ; 
 int read_reply (struct rxe_qp*,struct rxe_pkt_info*) ; 
 int /*<<< orphan*/ * resp_state_name ; 
 int /*<<< orphan*/  rxe_add_ref (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_counter_inc (struct rxe_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_drain_req_pkts (struct rxe_qp*,int) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_qp*) ; 
 int /*<<< orphan*/  rxe_qp_error (struct rxe_qp*) ; 
 int /*<<< orphan*/  send_ack (struct rxe_qp*,struct rxe_pkt_info*,int,int /*<<< orphan*/ ) ; 
 struct rxe_dev* to_rdev (int /*<<< orphan*/ ) ; 

int rxe_responder(void *arg)
{
	struct rxe_qp *qp = (struct rxe_qp *)arg;
	struct rxe_dev *rxe = to_rdev(qp->ibqp.device);
	enum resp_states state;
	struct rxe_pkt_info *pkt = NULL;
	int ret = 0;

	rxe_add_ref(qp);

	qp->resp.aeth_syndrome = AETH_ACK_UNLIMITED;

	if (!qp->valid) {
		ret = -EINVAL;
		goto done;
	}

	switch (qp->resp.state) {
	case QP_STATE_RESET:
		state = RESPST_RESET;
		break;

	default:
		state = RESPST_GET_REQ;
		break;
	}

	while (1) {
		pr_debug("qp#%d state = %s\n", qp_num(qp),
			 resp_state_name[state]);
		switch (state) {
		case RESPST_GET_REQ:
			state = get_req(qp, &pkt);
			break;
		case RESPST_CHK_PSN:
			state = check_psn(qp, pkt);
			break;
		case RESPST_CHK_OP_SEQ:
			state = check_op_seq(qp, pkt);
			break;
		case RESPST_CHK_OP_VALID:
			state = check_op_valid(qp, pkt);
			break;
		case RESPST_CHK_RESOURCE:
			state = check_resource(qp, pkt);
			break;
		case RESPST_CHK_LENGTH:
			state = check_length(qp, pkt);
			break;
		case RESPST_CHK_RKEY:
			state = check_rkey(qp, pkt);
			break;
		case RESPST_EXECUTE:
			state = execute(qp, pkt);
			break;
		case RESPST_COMPLETE:
			state = do_complete(qp, pkt);
			break;
		case RESPST_READ_REPLY:
			state = read_reply(qp, pkt);
			break;
		case RESPST_ACKNOWLEDGE:
			state = acknowledge(qp, pkt);
			break;
		case RESPST_CLEANUP:
			state = cleanup(qp, pkt);
			break;
		case RESPST_DUPLICATE_REQUEST:
			state = duplicate_request(qp, pkt);
			break;
		case RESPST_ERR_PSN_OUT_OF_SEQ:
			/* RC only - Class B. Drop packet. */
			send_ack(qp, pkt, AETH_NAK_PSN_SEQ_ERROR, qp->resp.psn);
			state = RESPST_CLEANUP;
			break;

		case RESPST_ERR_TOO_MANY_RDMA_ATM_REQ:
		case RESPST_ERR_MISSING_OPCODE_FIRST:
		case RESPST_ERR_MISSING_OPCODE_LAST_C:
		case RESPST_ERR_UNSUPPORTED_OPCODE:
		case RESPST_ERR_MISALIGNED_ATOMIC:
			/* RC Only - Class C. */
			do_class_ac_error(qp, AETH_NAK_INVALID_REQ,
					  IB_WC_REM_INV_REQ_ERR);
			state = RESPST_COMPLETE;
			break;

		case RESPST_ERR_MISSING_OPCODE_LAST_D1E:
			state = do_class_d1e_error(qp);
			break;
		case RESPST_ERR_RNR:
			if (qp_type(qp) == IB_QPT_RC) {
				rxe_counter_inc(rxe, RXE_CNT_SND_RNR);
				/* RC - class B */
				send_ack(qp, pkt, AETH_RNR_NAK |
					 (~AETH_TYPE_MASK &
					 qp->attr.min_rnr_timer),
					 pkt->psn);
			} else {
				/* UD/UC - class D */
				qp->resp.drop_msg = 1;
			}
			state = RESPST_CLEANUP;
			break;

		case RESPST_ERR_RKEY_VIOLATION:
			if (qp_type(qp) == IB_QPT_RC) {
				/* Class C */
				do_class_ac_error(qp, AETH_NAK_REM_ACC_ERR,
						  IB_WC_REM_ACCESS_ERR);
				state = RESPST_COMPLETE;
			} else {
				qp->resp.drop_msg = 1;
				if (qp->srq) {
					/* UC/SRQ Class D */
					qp->resp.status = IB_WC_REM_ACCESS_ERR;
					state = RESPST_COMPLETE;
				} else {
					/* UC/non-SRQ Class E. */
					state = RESPST_CLEANUP;
				}
			}
			break;

		case RESPST_ERR_LENGTH:
			if (qp_type(qp) == IB_QPT_RC) {
				/* Class C */
				do_class_ac_error(qp, AETH_NAK_INVALID_REQ,
						  IB_WC_REM_INV_REQ_ERR);
				state = RESPST_COMPLETE;
			} else if (qp->srq) {
				/* UC/UD - class E */
				qp->resp.status = IB_WC_REM_INV_REQ_ERR;
				state = RESPST_COMPLETE;
			} else {
				/* UC/UD - class D */
				qp->resp.drop_msg = 1;
				state = RESPST_CLEANUP;
			}
			break;

		case RESPST_ERR_MALFORMED_WQE:
			/* All, Class A. */
			do_class_ac_error(qp, AETH_NAK_REM_OP_ERR,
					  IB_WC_LOC_QP_OP_ERR);
			state = RESPST_COMPLETE;
			break;

		case RESPST_ERR_CQ_OVERFLOW:
			/* All - Class G */
			state = RESPST_ERROR;
			break;

		case RESPST_DONE:
			if (qp->resp.goto_error) {
				state = RESPST_ERROR;
				break;
			}

			goto done;

		case RESPST_EXIT:
			if (qp->resp.goto_error) {
				state = RESPST_ERROR;
				break;
			}

			goto exit;

		case RESPST_RESET:
			rxe_drain_req_pkts(qp, false);
			qp->resp.wqe = NULL;
			goto exit;

		case RESPST_ERROR:
			qp->resp.goto_error = 0;
			pr_warn("qp#%d moved to error state\n", qp_num(qp));
			rxe_qp_error(qp);
			goto exit;

		default:
			WARN_ON_ONCE(1);
		}
	}

exit:
	ret = -EAGAIN;
done:
	rxe_drop_ref(qp);
	return ret;
}