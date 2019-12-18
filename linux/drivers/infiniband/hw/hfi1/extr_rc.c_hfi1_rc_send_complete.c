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
struct tid_rdma_request {scalar_t__ comp_seg; scalar_t__ total_segs; scalar_t__ ack_seg; scalar_t__ cur_seg; } ;
struct TYPE_2__ {size_t opcode; } ;
struct rvt_swqe {TYPE_1__ wr; scalar_t__ lpsn; } ;
struct rvt_qp {size_t state; scalar_t__ s_size; scalar_t__ s_tail; scalar_t__ s_acked; int s_flags; scalar_t__ s_last; scalar_t__ s_psn; scalar_t__ s_sending_hpsn; scalar_t__ s_sending_psn; int /*<<< orphan*/  s_rdma_ack_cnt; int /*<<< orphan*/  s_lock; struct hfi1_qp_priv* priv; } ;
struct ib_other_headers {int dummy; } ;
struct hfi1_qp_priv {scalar_t__ s_tid_head; scalar_t__ s_tid_cur; int s_flags; int /*<<< orphan*/  timeout_shift; } ;
struct hfi1_opa_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK ; 
 int /*<<< orphan*/  ATOMIC_ACKNOWLEDGE ; 
 int HFI1_S_TID_RETRY_TIMER ; 
 scalar_t__ IB_BTH_REQ_ACK ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 size_t IB_WR_TID_RDMA_WRITE ; 
 scalar_t__ OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_FIRST ; 
 int /*<<< orphan*/  READ_REQ ; 
 int /*<<< orphan*/  READ_RESP ; 
 int /*<<< orphan*/  RESYNC ; 
 int RVT_PROCESS_RECV_OK ; 
 int RVT_SEND_OR_FLUSH_OR_RECV_OK ; 
 int RVT_S_TIMER ; 
 int RVT_S_WAIT_PSN ; 
 int RVT_S_WAIT_RNR ; 
 scalar_t__ TID_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_DATA ; 
 int /*<<< orphan*/  WRITE_DATA_LAST ; 
 int /*<<< orphan*/  WRITE_REQ ; 
 int /*<<< orphan*/  WRITE_RESP ; 
 scalar_t__ cmp_psn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  hfi1_add_tid_retry_timer (struct rvt_qp*) ; 
 struct ib_other_headers* hfi1_get_rc_ohdr (struct hfi1_opa_header*) ; 
 int /*<<< orphan*/  hfi1_schedule_send (struct rvt_qp*) ; 
 scalar_t__ ib_bth_get_opcode (struct ib_other_headers*) ; 
 scalar_t__ ib_bth_get_psn (struct ib_other_headers*) ; 
 int /*<<< orphan*/ * ib_hfi1_wc_opcode ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_sending_psn (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_add_retry_timer (struct rvt_qp*) ; 
 int /*<<< orphan*/  rvt_add_retry_timer_ext (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_qp_complete_swqe (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_qp_send_completion (struct rvt_qp*,struct rvt_swqe*,scalar_t__) ; 
 int /*<<< orphan*/  trace_hfi1_sendcomplete (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  trdma_clean_swqe (struct rvt_qp*,struct rvt_swqe*) ; 
 struct tid_rdma_request* wqe_to_tid_req (struct rvt_swqe*) ; 

void hfi1_rc_send_complete(struct rvt_qp *qp, struct hfi1_opa_header *opah)
{
	struct ib_other_headers *ohdr;
	struct hfi1_qp_priv *priv = qp->priv;
	struct rvt_swqe *wqe;
	u32 opcode, head, tail;
	u32 psn;
	struct tid_rdma_request *req;

	lockdep_assert_held(&qp->s_lock);
	if (!(ib_rvt_state_ops[qp->state] & RVT_SEND_OR_FLUSH_OR_RECV_OK))
		return;

	ohdr = hfi1_get_rc_ohdr(opah);
	opcode = ib_bth_get_opcode(ohdr);
	if ((opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	     opcode <= OP(ATOMIC_ACKNOWLEDGE)) ||
	    opcode == TID_OP(READ_RESP) ||
	    opcode == TID_OP(WRITE_RESP)) {
		WARN_ON(!qp->s_rdma_ack_cnt);
		qp->s_rdma_ack_cnt--;
		return;
	}

	psn = ib_bth_get_psn(ohdr);
	/*
	 * Don't attempt to reset the sending PSN for packets in the
	 * KDETH PSN space since the PSN does not match anything.
	 */
	if (opcode != TID_OP(WRITE_DATA) &&
	    opcode != TID_OP(WRITE_DATA_LAST) &&
	    opcode != TID_OP(ACK) && opcode != TID_OP(RESYNC))
		reset_sending_psn(qp, psn);

	/* Handle TID RDMA WRITE packets differently */
	if (opcode >= TID_OP(WRITE_REQ) &&
	    opcode <= TID_OP(WRITE_DATA_LAST)) {
		head = priv->s_tid_head;
		tail = priv->s_tid_cur;
		/*
		 * s_tid_cur is set to s_tid_head in the case, where
		 * a new TID RDMA request is being started and all
		 * previous ones have been completed.
		 * Therefore, we need to do a secondary check in order
		 * to properly determine whether we should start the
		 * RC timer.
		 */
		wqe = rvt_get_swqe_ptr(qp, tail);
		req = wqe_to_tid_req(wqe);
		if (head == tail && req->comp_seg < req->total_segs) {
			if (tail == 0)
				tail = qp->s_size - 1;
			else
				tail -= 1;
		}
	} else {
		head = qp->s_tail;
		tail = qp->s_acked;
	}

	/*
	 * Start timer after a packet requesting an ACK has been sent and
	 * there are still requests that haven't been acked.
	 */
	if ((psn & IB_BTH_REQ_ACK) && tail != head &&
	    opcode != TID_OP(WRITE_DATA) && opcode != TID_OP(WRITE_DATA_LAST) &&
	    opcode != TID_OP(RESYNC) &&
	    !(qp->s_flags &
	      (RVT_S_TIMER | RVT_S_WAIT_RNR | RVT_S_WAIT_PSN)) &&
	    (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) {
		if (opcode == TID_OP(READ_REQ))
			rvt_add_retry_timer_ext(qp, priv->timeout_shift);
		else
			rvt_add_retry_timer(qp);
	}

	/* Start TID RDMA ACK timer */
	if ((opcode == TID_OP(WRITE_DATA) ||
	     opcode == TID_OP(WRITE_DATA_LAST) ||
	     opcode == TID_OP(RESYNC)) &&
	    (psn & IB_BTH_REQ_ACK) &&
	    !(priv->s_flags & HFI1_S_TID_RETRY_TIMER) &&
	    (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) {
		/*
		 * The TID RDMA ACK packet could be received before this
		 * function is called. Therefore, add the timer only if TID
		 * RDMA ACK packets are actually pending.
		 */
		wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
		req = wqe_to_tid_req(wqe);
		if (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE &&
		    req->ack_seg < req->cur_seg)
			hfi1_add_tid_retry_timer(qp);
	}

	while (qp->s_last != qp->s_acked) {
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		if (cmp_psn(wqe->lpsn, qp->s_sending_psn) >= 0 &&
		    cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)
			break;
		trdma_clean_swqe(qp, wqe);
		trace_hfi1_qp_send_completion(qp, wqe, qp->s_last);
		rvt_qp_complete_swqe(qp,
				     wqe,
				     ib_hfi1_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	}
	/*
	 * If we were waiting for sends to complete before re-sending,
	 * and they are now complete, restart sending.
	 */
	trace_hfi1_sendcomplete(qp, psn);
	if (qp->s_flags & RVT_S_WAIT_PSN &&
	    cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) > 0) {
		qp->s_flags &= ~RVT_S_WAIT_PSN;
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
		hfi1_schedule_send(qp);
	}
}