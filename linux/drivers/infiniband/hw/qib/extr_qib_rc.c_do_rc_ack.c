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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_7__ {scalar_t__ opcode; } ;
struct rvt_swqe {int lpsn; TYPE_3__ wr; TYPE_2__* sg_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {scalar_t__ s_acked; int r_flags; int s_last_psn; int s_flags; scalar_t__ s_tail; int s_psn; int s_state; int s_rnr_retry; int s_rnr_retry_cnt; scalar_t__ s_last; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  s_retry; scalar_t__ s_num_rd_atomic; int /*<<< orphan*/  rspwait; int /*<<< orphan*/  port_num; TYPE_1__ ibqp; } ;
struct TYPE_8__ {int n_rc_resends; int /*<<< orphan*/  n_other_naks; int /*<<< orphan*/  n_seq_naks; int /*<<< orphan*/  n_rnr_naks; int /*<<< orphan*/ * rc_acks; } ;
struct qib_ibport {TYPE_4__ rvp; } ;
struct qib_ctxtdata {int /*<<< orphan*/  qp_wait_list; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_6__ {int /*<<< orphan*/ * vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACKNOWLEDGE ; 
 int IB_AETH_CREDIT_MASK ; 
 int IB_AETH_CREDIT_SHIFT ; 
 int IB_AETH_NAK_SHIFT ; 
 int IB_WC_REM_ACCESS_ERR ; 
 int IB_WC_REM_INV_REQ_ERR ; 
 int IB_WC_REM_OP_ERR ; 
 int IB_WC_RNR_RETRY_EXC_ERR ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 scalar_t__ IB_WR_ATOMIC_CMP_AND_SWP ; 
 scalar_t__ IB_WR_ATOMIC_FETCH_AND_ADD ; 
 scalar_t__ IB_WR_RDMA_READ ; 
 int OP (int /*<<< orphan*/ ) ; 
 int QIB_PSN_MASK ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_LAST ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_ONLY ; 
 int RVT_R_RDMAR_SEQ ; 
 int RVT_R_RSP_SEND ; 
 int RVT_S_WAIT_ACK ; 
 int RVT_S_WAIT_FENCE ; 
 int RVT_S_WAIT_RDMAR ; 
 int RVT_S_WAIT_RNR ; 
 int RVT_S_WAIT_SSN_CREDIT ; 
 int /*<<< orphan*/  SEND_LAST ; 
 struct rvt_swqe* do_rc_completion (struct rvt_qp*,struct rvt_swqe*,struct qib_ibport*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int qib_cmp24 (int,int) ; 
 int /*<<< orphan*/  qib_restart_rc (struct rvt_qp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_schedule_send (struct rvt_qp*) ; 
 int /*<<< orphan*/  reset_psn (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  rvt_add_rnr_timer (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  rvt_error_qp (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_get_credit (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_mod_retry_timer (struct rvt_qp*) ; 
 int /*<<< orphan*/  rvt_send_complete (struct rvt_qp*,struct rvt_swqe*,int) ; 
 int /*<<< orphan*/  rvt_stop_rc_timers (struct rvt_qp*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct qib_ibport* to_iport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_last_psn (struct rvt_qp*,int) ; 

__attribute__((used)) static int do_rc_ack(struct rvt_qp *qp, u32 aeth, u32 psn, int opcode,
		     u64 val, struct qib_ctxtdata *rcd)
{
	struct qib_ibport *ibp;
	enum ib_wc_status status;
	struct rvt_swqe *wqe;
	int ret = 0;
	u32 ack_psn;
	int diff;

	/*
	 * Note that NAKs implicitly ACK outstanding SEND and RDMA write
	 * requests and implicitly NAK RDMA read and atomic requests issued
	 * before the NAK'ed request.  The MSN won't include the NAK'ed
	 * request but will include an ACK'ed request(s).
	 */
	ack_psn = psn;
	if (aeth >> IB_AETH_NAK_SHIFT)
		ack_psn--;
	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	ibp = to_iport(qp->ibqp.device, qp->port_num);

	/*
	 * The MSN might be for a later WQE than the PSN indicates so
	 * only complete WQEs that the PSN finishes.
	 */
	while ((diff = qib_cmp24(ack_psn, wqe->lpsn)) >= 0) {
		/*
		 * RDMA_READ_RESPONSE_ONLY is a special case since
		 * we want to generate completion events for everything
		 * before the RDMA read, copy the data, then generate
		 * the completion for the read.
		 */
		if (wqe->wr.opcode == IB_WR_RDMA_READ &&
		    opcode == OP(RDMA_READ_RESPONSE_ONLY) &&
		    diff == 0) {
			ret = 1;
			goto bail;
		}
		/*
		 * If this request is a RDMA read or atomic, and the ACK is
		 * for a later operation, this ACK NAKs the RDMA read or
		 * atomic.  In other words, only a RDMA_READ_LAST or ONLY
		 * can ACK a RDMA read and likewise for atomic ops.  Note
		 * that the NAK case can only happen if relaxed ordering is
		 * used and requests are sent after an RDMA read or atomic
		 * is sent but before the response is received.
		 */
		if ((wqe->wr.opcode == IB_WR_RDMA_READ &&
		     (opcode != OP(RDMA_READ_RESPONSE_LAST) || diff != 0)) ||
		    ((wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		      wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) &&
		     (opcode != OP(ATOMIC_ACKNOWLEDGE) || diff != 0))) {
			/* Retry this request. */
			if (!(qp->r_flags & RVT_R_RDMAR_SEQ)) {
				qp->r_flags |= RVT_R_RDMAR_SEQ;
				qib_restart_rc(qp, qp->s_last_psn + 1, 0);
				if (list_empty(&qp->rspwait)) {
					qp->r_flags |= RVT_R_RSP_SEND;
					rvt_get_qp(qp);
					list_add_tail(&qp->rspwait,
						      &rcd->qp_wait_list);
				}
			}
			/*
			 * No need to process the ACK/NAK since we are
			 * restarting an earlier request.
			 */
			goto bail;
		}
		if (wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) {
			u64 *vaddr = wqe->sg_list[0].vaddr;
			*vaddr = val;
		}
		if (qp->s_num_rd_atomic &&
		    (wqe->wr.opcode == IB_WR_RDMA_READ ||
		     wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		     wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD)) {
			qp->s_num_rd_atomic--;
			/* Restart sending task if fence is complete */
			if ((qp->s_flags & RVT_S_WAIT_FENCE) &&
			    !qp->s_num_rd_atomic) {
				qp->s_flags &= ~(RVT_S_WAIT_FENCE |
						 RVT_S_WAIT_ACK);
				qib_schedule_send(qp);
			} else if (qp->s_flags & RVT_S_WAIT_RDMAR) {
				qp->s_flags &= ~(RVT_S_WAIT_RDMAR |
						 RVT_S_WAIT_ACK);
				qib_schedule_send(qp);
			}
		}
		wqe = do_rc_completion(qp, wqe, ibp);
		if (qp->s_acked == qp->s_tail)
			break;
	}

	switch (aeth >> IB_AETH_NAK_SHIFT) {
	case 0:         /* ACK */
		this_cpu_inc(*ibp->rvp.rc_acks);
		if (qp->s_acked != qp->s_tail) {
			/*
			 * We are expecting more ACKs so
			 * reset the retransmit timer.
			 */
			rvt_mod_retry_timer(qp);
			/*
			 * We can stop resending the earlier packets and
			 * continue with the next packet the receiver wants.
			 */
			if (qib_cmp24(qp->s_psn, psn) <= 0)
				reset_psn(qp, psn + 1);
		} else {
			/* No more acks - kill all timers */
			rvt_stop_rc_timers(qp);
			if (qib_cmp24(qp->s_psn, psn) <= 0) {
				qp->s_state = OP(SEND_LAST);
				qp->s_psn = psn + 1;
			}
		}
		if (qp->s_flags & RVT_S_WAIT_ACK) {
			qp->s_flags &= ~RVT_S_WAIT_ACK;
			qib_schedule_send(qp);
		}
		rvt_get_credit(qp, aeth);
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		qp->s_retry = qp->s_retry_cnt;
		update_last_psn(qp, psn);
		return 1;

	case 1:         /* RNR NAK */
		ibp->rvp.n_rnr_naks++;
		if (qp->s_acked == qp->s_tail)
			goto bail;
		if (qp->s_flags & RVT_S_WAIT_RNR)
			goto bail;
		if (qp->s_rnr_retry == 0) {
			status = IB_WC_RNR_RETRY_EXC_ERR;
			goto class_b;
		}
		if (qp->s_rnr_retry_cnt < 7)
			qp->s_rnr_retry--;

		/* The last valid PSN is the previous PSN. */
		update_last_psn(qp, psn - 1);

		ibp->rvp.n_rc_resends += (qp->s_psn - psn) & QIB_PSN_MASK;

		reset_psn(qp, psn);

		qp->s_flags &= ~(RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_ACK);
		rvt_stop_rc_timers(qp);
		rvt_add_rnr_timer(qp, aeth);
		return 0;

	case 3:         /* NAK */
		if (qp->s_acked == qp->s_tail)
			goto bail;
		/* The last valid PSN is the previous PSN. */
		update_last_psn(qp, psn - 1);
		switch ((aeth >> IB_AETH_CREDIT_SHIFT) &
			IB_AETH_CREDIT_MASK) {
		case 0: /* PSN sequence error */
			ibp->rvp.n_seq_naks++;
			/*
			 * Back up to the responder's expected PSN.
			 * Note that we might get a NAK in the middle of an
			 * RDMA READ response which terminates the RDMA
			 * READ.
			 */
			qib_restart_rc(qp, psn, 0);
			qib_schedule_send(qp);
			break;

		case 1: /* Invalid Request */
			status = IB_WC_REM_INV_REQ_ERR;
			ibp->rvp.n_other_naks++;
			goto class_b;

		case 2: /* Remote Access Error */
			status = IB_WC_REM_ACCESS_ERR;
			ibp->rvp.n_other_naks++;
			goto class_b;

		case 3: /* Remote Operation Error */
			status = IB_WC_REM_OP_ERR;
			ibp->rvp.n_other_naks++;
class_b:
			if (qp->s_last == qp->s_acked) {
				rvt_send_complete(qp, wqe, status);
				rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			}
			break;

		default:
			/* Ignore other reserved NAK error codes */
			goto reserved;
		}
		qp->s_retry = qp->s_retry_cnt;
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		goto bail;

	default:                /* 2: reserved */
reserved:
		/* Ignore reserved NAK codes. */
		goto bail;
	}

bail:
	rvt_stop_rc_timers(qp);
	return ret;
}