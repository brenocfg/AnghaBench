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
typedef  int u32 ;
struct TYPE_6__ {size_t opcode; } ;
struct rvt_swqe {TYPE_3__ wr; scalar_t__ lpsn; } ;
struct rvt_qp {size_t state; scalar_t__ s_acked; scalar_t__ s_tail; int s_flags; scalar_t__ s_last; scalar_t__ s_psn; scalar_t__ s_sending_hpsn; scalar_t__ s_sending_psn; int /*<<< orphan*/  s_rdma_ack_cnt; } ;
struct ib_other_headers {int /*<<< orphan*/ * bth; } ;
struct TYPE_4__ {struct ib_other_headers oth; } ;
struct TYPE_5__ {TYPE_1__ l; struct ib_other_headers oth; } ;
struct ib_header {TYPE_2__ u; int /*<<< orphan*/ * lrh; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACKNOWLEDGE ; 
 int IB_BTH_REQ_ACK ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int OP (int /*<<< orphan*/ ) ; 
 int QIB_LRH_BTH ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_FIRST ; 
 int RVT_PROCESS_RECV_OK ; 
 int RVT_SEND_OR_FLUSH_OR_RECV_OK ; 
 int RVT_S_TIMER ; 
 int RVT_S_WAIT_PSN ; 
 int RVT_S_WAIT_RNR ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ib_qib_wc_opcode ; 
 int* ib_rvt_state_ops ; 
 scalar_t__ qib_cmp24 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qib_schedule_send (struct rvt_qp*) ; 
 int /*<<< orphan*/  reset_sending_psn (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  rvt_add_retry_timer (struct rvt_qp*) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_qp_complete_swqe (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qib_rc_send_complete(struct rvt_qp *qp, struct ib_header *hdr)
{
	struct ib_other_headers *ohdr;
	struct rvt_swqe *wqe;
	u32 opcode;
	u32 psn;

	if (!(ib_rvt_state_ops[qp->state] & RVT_SEND_OR_FLUSH_OR_RECV_OK))
		return;

	/* Find out where the BTH is */
	if ((be16_to_cpu(hdr->lrh[0]) & 3) == QIB_LRH_BTH)
		ohdr = &hdr->u.oth;
	else
		ohdr = &hdr->u.l.oth;

	opcode = be32_to_cpu(ohdr->bth[0]) >> 24;
	if (opcode >= OP(RDMA_READ_RESPONSE_FIRST) &&
	    opcode <= OP(ATOMIC_ACKNOWLEDGE)) {
		WARN_ON(!qp->s_rdma_ack_cnt);
		qp->s_rdma_ack_cnt--;
		return;
	}

	psn = be32_to_cpu(ohdr->bth[2]);
	reset_sending_psn(qp, psn);

	/*
	 * Start timer after a packet requesting an ACK has been sent and
	 * there are still requests that haven't been acked.
	 */
	if ((psn & IB_BTH_REQ_ACK) && qp->s_acked != qp->s_tail &&
	    !(qp->s_flags & (RVT_S_TIMER | RVT_S_WAIT_RNR | RVT_S_WAIT_PSN)) &&
	    (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		rvt_add_retry_timer(qp);

	while (qp->s_last != qp->s_acked) {
		wqe = rvt_get_swqe_ptr(qp, qp->s_last);
		if (qib_cmp24(wqe->lpsn, qp->s_sending_psn) >= 0 &&
		    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) <= 0)
			break;
		rvt_qp_complete_swqe(qp,
				     wqe,
				     ib_qib_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	}
	/*
	 * If we were waiting for sends to complete before resending,
	 * and they are now complete, restart sending.
	 */
	if (qp->s_flags & RVT_S_WAIT_PSN &&
	    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) > 0) {
		qp->s_flags &= ~RVT_S_WAIT_PSN;
		qp->s_sending_psn = qp->s_psn;
		qp->s_sending_hpsn = qp->s_psn - 1;
		qib_schedule_send(qp);
	}
}