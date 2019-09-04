#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_10__ {size_t opcode; } ;
struct rvt_swqe {TYPE_5__ wr; scalar_t__ lpsn; } ;
struct rvt_qp {size_t state; scalar_t__ s_acked; scalar_t__ s_tail; int s_flags; scalar_t__ s_last; scalar_t__ s_size; scalar_t__ s_psn; scalar_t__ s_sending_hpsn; scalar_t__ s_sending_psn; int /*<<< orphan*/  s_rdma_ack_cnt; int /*<<< orphan*/  s_lock; struct hfi1_qp_priv* priv; } ;
struct ib_other_headers {int dummy; } ;
struct TYPE_6__ {struct ib_other_headers oth; } ;
struct TYPE_7__ {TYPE_1__ l; struct ib_other_headers oth; } ;
struct ib_header {TYPE_2__ u; } ;
struct hfi1_qp_priv {scalar_t__ hdr_type; } ;
struct TYPE_8__ {struct ib_other_headers oth; } ;
struct TYPE_9__ {TYPE_3__ l; struct ib_other_headers oth; } ;
struct hfi1_16b_header {TYPE_4__ u; } ;
struct hfi1_opa_header {struct hfi1_16b_header opah; struct ib_header ibh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACKNOWLEDGE ; 
 scalar_t__ HFI1_LRH_BTH ; 
 scalar_t__ HFI1_PKT_TYPE_9B ; 
 scalar_t__ IB_BTH_REQ_ACK ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 scalar_t__ OP (int /*<<< orphan*/ ) ; 
 scalar_t__ OPA_16B_L4_IB_LOCAL ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_FIRST ; 
 int RVT_PROCESS_RECV_OK ; 
 int RVT_SEND_OR_FLUSH_OR_RECV_OK ; 
 int RVT_S_TIMER ; 
 int RVT_S_WAIT_PSN ; 
 int RVT_S_WAIT_RNR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ cmp_psn (scalar_t__,scalar_t__) ; 
 scalar_t__ hfi1_16B_get_l4 (struct hfi1_16b_header*) ; 
 int /*<<< orphan*/  hfi1_schedule_send (struct rvt_qp*) ; 
 scalar_t__ ib_bth_get_opcode (struct ib_other_headers*) ; 
 scalar_t__ ib_bth_get_psn (struct ib_other_headers*) ; 
 scalar_t__ ib_get_lnh (struct ib_header*) ; 
 int /*<<< orphan*/ * ib_hfi1_wc_opcode ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_sending_psn (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_add_retry_timer (struct rvt_qp*) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_put_swqe (struct rvt_swqe*) ; 
 int /*<<< orphan*/  rvt_qp_swqe_complete (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_qp_wqe_unreserve (struct rvt_qp*,struct rvt_swqe*) ; 
 int /*<<< orphan*/  trace_hfi1_qp_send_completion (struct rvt_qp*,struct rvt_swqe*,scalar_t__) ; 
 int /*<<< orphan*/  trace_hfi1_sendcomplete (struct rvt_qp*,scalar_t__) ; 

void hfi1_rc_send_complete(struct rvt_qp *qp, struct hfi1_opa_header *opah)
{
	struct ib_other_headers *ohdr;
	struct hfi1_qp_priv *priv = qp->priv;
	struct rvt_swqe *wqe;
	struct ib_header *hdr = NULL;
	struct hfi1_16b_header *hdr_16b = NULL;
	u32 opcode;
	u32 psn;

	lockdep_assert_held(&qp->s_lock);
	if (!(ib_rvt_state_ops[qp->state] & RVT_SEND_OR_FLUSH_OR_RECV_OK))
		return;

	/* Find out where the BTH is */
	if (priv->hdr_type == HFI1_PKT_TYPE_9B) {
		hdr = &opah->ibh;
		if (ib_get_lnh(hdr) == HFI1_LRH_BTH)
			ohdr = &hdr->u.oth;
		else
			ohdr = &hdr->u.l.oth;
	} else {
		u8 l4;

		hdr_16b = &opah->opah;
		l4  = hfi1_16B_get_l4(hdr_16b);
		if (l4 == OPA_16B_L4_IB_LOCAL)
			ohdr = &hdr_16b->u.oth;
		else
			ohdr = &hdr_16b->u.l.oth;
	}

	opcode = ib_bth_get_opcode(ohdr);
	if (opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	    opcode <= OP(ATOMIC_ACKNOWLEDGE)) {
		WARN_ON(!qp->s_rdma_ack_cnt);
		qp->s_rdma_ack_cnt--;
		return;
	}

	psn = ib_bth_get_psn(ohdr);
	reset_sending_psn(qp, psn);

	/*
	 * Start timer after a packet requesting an ACK has been sent and
	 * there are still requests that haven't been acked.
	 */
	if ((psn & IB_BTH_REQ_ACK) && qp->s_acked != qp->s_tail &&
	    !(qp->s_flags &
		(RVT_S_TIMER | RVT_S_WAIT_RNR | RVT_S_WAIT_PSN)) &&
		(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		rvt_add_retry_timer(qp);

	while (qp->s_last != qp->s_acked) {
		u32 s_last;

		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		if (cmp_psn(wqe->lpsn, qp->s_sending_psn) >= 0 &&
		    cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)
			break;
		rvt_qp_wqe_unreserve(qp, wqe);
		s_last = qp->s_last;
		trace_hfi1_qp_send_completion(qp, wqe, s_last);
		if (++s_last >= qp->s_size)
			s_last = 0;
		qp->s_last = s_last;
		/* see post_send() */
		barrier();
		rvt_put_swqe(wqe);
		rvt_qp_swqe_complete(qp,
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