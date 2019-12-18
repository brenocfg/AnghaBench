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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ opcode; } ;
struct rvt_swqe {TYPE_1__ wr; int /*<<< orphan*/  psn; } ;
struct rvt_qp {scalar_t__ s_acked; scalar_t__ s_cur; scalar_t__ s_size; scalar_t__ s_tail; scalar_t__ s_psn; scalar_t__ s_sending_psn; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_sending_hpsn; void* s_state; scalar_t__ s_num_rd_atomic; int /*<<< orphan*/  s_lock; struct hfi1_qp_priv* priv; } ;
struct hfi1_qp_priv {int /*<<< orphan*/  s_flags; scalar_t__ pending_tid_w_resp; scalar_t__ pending_tid_r_segs; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_S_AHG_VALID ; 
 int /*<<< orphan*/  HFI1_S_TID_WAIT_INTERLCK ; 
#define  IB_WR_RDMA_READ 134 
#define  IB_WR_RDMA_WRITE 133 
#define  IB_WR_RDMA_WRITE_WITH_IMM 132 
#define  IB_WR_SEND 131 
#define  IB_WR_SEND_WITH_IMM 130 
#define  IB_WR_TID_RDMA_READ 129 
#define  IB_WR_TID_RDMA_WRITE 128 
 void* OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_FIRST ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_LAST ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_MIDDLE ; 
 int /*<<< orphan*/  READ_RESP ; 
 int /*<<< orphan*/  RVT_S_WAIT_PSN ; 
 int /*<<< orphan*/  SEND_LAST ; 
 void* TID_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_RESP ; 
 int cmp_psn (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  trace_hfi1_sender_reset_psn (struct rvt_qp*) ; 
 int /*<<< orphan*/  update_num_rd_atomic (struct rvt_qp*,scalar_t__,struct rvt_swqe*) ; 

__attribute__((used)) static void reset_psn(struct rvt_qp *qp, u32 psn)
{
	u32 n = qp->s_acked;
	struct rvt_swqe *wqe = rvt_get_swqe_ptr(qp, n);
	u32 opcode;
	struct hfi1_qp_priv *priv = qp->priv;

	lockdep_assert_held(&qp->s_lock);
	qp->s_cur = n;
	priv->pending_tid_r_segs = 0;
	priv->pending_tid_w_resp = 0;
	qp->s_num_rd_atomic = 0;

	/*
	 * If we are starting the request from the beginning,
	 * let the normal send code handle initialization.
	 */
	if (cmp_psn(psn, wqe->psn) <= 0) {
		qp->s_state = OP(SEND_LAST);
		goto done;
	}
	update_num_rd_atomic(qp, psn, wqe);

	/* Find the work request opcode corresponding to the given PSN. */
	for (;;) {
		int diff;

		if (++n == qp->s_size)
			n = 0;
		if (n == qp->s_tail)
			break;
		wqe = rvt_get_swqe_ptr(qp, n);
		diff = cmp_psn(psn, wqe->psn);
		if (diff < 0) {
			/* Point wqe back to the previous one*/
			wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
			break;
		}
		qp->s_cur = n;
		/*
		 * If we are starting the request from the beginning,
		 * let the normal send code handle initialization.
		 */
		if (diff == 0) {
			qp->s_state = OP(SEND_LAST);
			goto done;
		}

		update_num_rd_atomic(qp, psn, wqe);
	}
	opcode = wqe->wr.opcode;

	/*
	 * Set the state to restart in the middle of a request.
	 * Don't change the s_sge, s_cur_sge, or s_cur_size.
	 * See hfi1_make_rc_req().
	 */
	switch (opcode) {
	case IB_WR_SEND:
	case IB_WR_SEND_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_FIRST);
		break;

	case IB_WR_RDMA_WRITE:
	case IB_WR_RDMA_WRITE_WITH_IMM:
		qp->s_state = OP(RDMA_READ_RESPONSE_LAST);
		break;

	case IB_WR_TID_RDMA_WRITE:
		qp->s_state = TID_OP(WRITE_RESP);
		break;

	case IB_WR_RDMA_READ:
		qp->s_state = OP(RDMA_READ_RESPONSE_MIDDLE);
		break;

	case IB_WR_TID_RDMA_READ:
		qp->s_state = TID_OP(READ_RESP);
		break;

	default:
		/*
		 * This case shouldn't happen since its only
		 * one PSN per req.
		 */
		qp->s_state = OP(SEND_LAST);
	}
done:
	priv->s_flags &= ~HFI1_S_TID_WAIT_INTERLCK;
	qp->s_psn = psn;
	/*
	 * Set RVT_S_WAIT_PSN as rc_complete() may start the timer
	 * asynchronously before the send engine can get scheduled.
	 * Doing it in hfi1_make_rc_req() is too late.
	 */
	if ((cmp_psn(qp->s_psn, qp->s_sending_hpsn) <= 0) &&
	    (cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) <= 0))
		qp->s_flags |= RVT_S_WAIT_PSN;
	qp->s_flags &= ~HFI1_S_AHG_VALID;
	trace_hfi1_sender_reset_psn(qp);
}