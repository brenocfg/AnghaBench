#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_11__ {scalar_t__ opcode; } ;
struct rvt_swqe {int lpsn; int psn; TYPE_5__ wr; TYPE_4__* sg_list; } ;
struct TYPE_7__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {scalar_t__ s_acked; int s_last_psn; int s_flags; scalar_t__ s_tail; scalar_t__ s_cur; int s_psn; int s_state; int s_rnr_retry; int s_rnr_retry_cnt; scalar_t__ s_last; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  s_retry; TYPE_1__ ibqp; scalar_t__ s_num_rd_atomic; int /*<<< orphan*/  s_lock; struct hfi1_qp_priv* priv; } ;
struct rvt_dev_info {TYPE_2__* post_parms; } ;
struct hfi1_qp_priv {scalar_t__ s_tid_cur; int /*<<< orphan*/  pending_tid_w_resp; int /*<<< orphan*/  timeout_shift; } ;
struct TYPE_9__ {int n_rc_resends; int /*<<< orphan*/  n_other_naks; int /*<<< orphan*/  n_seq_naks; int /*<<< orphan*/  n_rnr_naks; int /*<<< orphan*/ * rc_acks; } ;
struct hfi1_ibport {TYPE_3__ rvp; } ;
struct hfi1_ctxtdata {int dummy; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_12__ {int /*<<< orphan*/  ack_pending; } ;
struct TYPE_10__ {int /*<<< orphan*/ * vaddr; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_ACKNOWLEDGE ; 
 scalar_t__ HFI1_QP_WQE_INVALID ; 
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
 scalar_t__ IB_WR_OPFN ; 
 scalar_t__ IB_WR_RDMA_READ ; 
 scalar_t__ IB_WR_TID_RDMA_READ ; 
 scalar_t__ IB_WR_TID_RDMA_WRITE ; 
 int OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_LAST ; 
 int /*<<< orphan*/  RDMA_READ_RESPONSE_ONLY ; 
 int /*<<< orphan*/  READ_RESP ; 
 int RVT_OPERATION_IGN_RNR_CNT ; 
 int RVT_S_WAIT_ACK ; 
 int RVT_S_WAIT_FENCE ; 
 int RVT_S_WAIT_RDMAR ; 
 int RVT_S_WAIT_RNR ; 
 int RVT_S_WAIT_SSN_CREDIT ; 
 int /*<<< orphan*/  SEND_LAST ; 
 int TID_OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_RESP ; 
 int /*<<< orphan*/  cmp_psn (int,int) ; 
 int delta_psn (int,int) ; 
 struct rvt_swqe* do_rc_completion (struct rvt_qp*,struct rvt_swqe*,struct hfi1_ibport*) ; 
 int /*<<< orphan*/  hfi1_kern_read_tid_flow_free (struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_restart_rc (struct rvt_qp*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfi1_schedule_send (struct rvt_qp*) ; 
 int /*<<< orphan*/  hfi1_trdma_send_complete (struct rvt_qp*,struct rvt_swqe*,int) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opfn_conn_reply (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 struct hfi1_ibport* rcd_to_iport (struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  reset_psn (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  rvt_add_rnr_timer (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  rvt_error_qp (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_get_credit (struct rvt_qp*,int) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_mod_retry_timer (struct rvt_qp*) ; 
 int /*<<< orphan*/  rvt_mod_retry_timer_ext (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_stop_rc_timers (struct rvt_qp*) ; 
 int /*<<< orphan*/  set_restart_qp (struct rvt_qp*,struct hfi1_ctxtdata*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_rc_ack_do (struct rvt_qp*,int,int,struct rvt_swqe*) ; 
 int /*<<< orphan*/  trace_hfi1_sender_do_rc_ack (struct rvt_qp*) ; 
 int /*<<< orphan*/  update_last_psn (struct rvt_qp*,int) ; 
 int /*<<< orphan*/  update_qp_retry_state (struct rvt_qp*,int,int,int) ; 
 TYPE_6__* wqe_to_tid_req (struct rvt_swqe*) ; 

int do_rc_ack(struct rvt_qp *qp, u32 aeth, u32 psn, int opcode,
	      u64 val, struct hfi1_ctxtdata *rcd)
{
	struct hfi1_ibport *ibp;
	enum ib_wc_status status;
	struct hfi1_qp_priv *qpriv = qp->priv;
	struct rvt_swqe *wqe;
	int ret = 0;
	u32 ack_psn;
	int diff;
	struct rvt_dev_info *rdi;

	lockdep_assert_held(&qp->s_lock);
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
	ibp = rcd_to_iport(rcd);

	/*
	 * The MSN might be for a later WQE than the PSN indicates so
	 * only complete WQEs that the PSN finishes.
	 */
	while ((diff = delta_psn(ack_psn, wqe->lpsn)) >= 0) {
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
			goto bail_stop;
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
		    (wqe->wr.opcode == IB_WR_TID_RDMA_READ &&
		     (opcode != TID_OP(READ_RESP) || diff != 0)) ||
		    ((wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		      wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) &&
		     (opcode != OP(ATOMIC_ACKNOWLEDGE) || diff != 0)) ||
		    (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE &&
		     (delta_psn(psn, qp->s_last_psn) != 1))) {
			set_restart_qp(qp, rcd);
			/*
			 * No need to process the ACK/NAK since we are
			 * restarting an earlier request.
			 */
			goto bail_stop;
		}
		if (wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) {
			u64 *vaddr = wqe->sg_list[0].vaddr;
			*vaddr = val;
		}
		if (wqe->wr.opcode == IB_WR_OPFN)
			opfn_conn_reply(qp, val);

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
				hfi1_schedule_send(qp);
			} else if (qp->s_flags & RVT_S_WAIT_RDMAR) {
				qp->s_flags &= ~(RVT_S_WAIT_RDMAR |
						 RVT_S_WAIT_ACK);
				hfi1_schedule_send(qp);
			}
		}

		/*
		 * TID RDMA WRITE requests will be completed by the TID RDMA
		 * ACK packet handler (see tid_rdma.c).
		 */
		if (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE)
			break;

		wqe = do_rc_completion(qp, wqe, ibp);
		if (qp->s_acked == qp->s_tail)
			break;
	}

	trace_hfi1_rc_ack_do(qp, aeth, psn, wqe);
	trace_hfi1_sender_do_rc_ack(qp);
	switch (aeth >> IB_AETH_NAK_SHIFT) {
	case 0:         /* ACK */
		this_cpu_inc(*ibp->rvp.rc_acks);
		if (wqe->wr.opcode == IB_WR_TID_RDMA_READ) {
			if (wqe_to_tid_req(wqe)->ack_pending)
				rvt_mod_retry_timer_ext(qp,
							qpriv->timeout_shift);
			else
				rvt_stop_rc_timers(qp);
		} else if (qp->s_acked != qp->s_tail) {
			struct rvt_swqe *__w = NULL;

			if (qpriv->s_tid_cur != HFI1_QP_WQE_INVALID)
				__w = rvt_get_swqe_ptr(qp, qpriv->s_tid_cur);

			/*
			 * Stop timers if we've received all of the TID RDMA
			 * WRITE * responses.
			 */
			if (__w && __w->wr.opcode == IB_WR_TID_RDMA_WRITE &&
			    opcode == TID_OP(WRITE_RESP)) {
				/*
				 * Normally, the loop above would correctly
				 * process all WQEs from s_acked onward and
				 * either complete them or check for correct
				 * PSN sequencing.
				 * However, for TID RDMA, due to pipelining,
				 * the response may not be for the request at
				 * s_acked so the above look would just be
				 * skipped. This does not allow for checking
				 * the PSN sequencing. It has to be done
				 * separately.
				 */
				if (cmp_psn(psn, qp->s_last_psn + 1)) {
					set_restart_qp(qp, rcd);
					goto bail_stop;
				}
				/*
				 * If the psn is being resent, stop the
				 * resending.
				 */
				if (qp->s_cur != qp->s_tail &&
				    cmp_psn(qp->s_psn, psn) <= 0)
					update_qp_retry_state(qp, psn,
							      __w->psn,
							      __w->lpsn);
				else if (--qpriv->pending_tid_w_resp)
					rvt_mod_retry_timer(qp);
				else
					rvt_stop_rc_timers(qp);
			} else {
				/*
				 * We are expecting more ACKs so
				 * mod the retry timer.
				 */
				rvt_mod_retry_timer(qp);
				/*
				 * We can stop re-sending the earlier packets
				 * and continue with the next packet the
				 * receiver wants.
				 */
				if (cmp_psn(qp->s_psn, psn) <= 0)
					reset_psn(qp, psn + 1);
			}
		} else {
			/* No more acks - kill all timers */
			rvt_stop_rc_timers(qp);
			if (cmp_psn(qp->s_psn, psn) <= 0) {
				qp->s_state = OP(SEND_LAST);
				qp->s_psn = psn + 1;
			}
		}
		if (qp->s_flags & RVT_S_WAIT_ACK) {
			qp->s_flags &= ~RVT_S_WAIT_ACK;
			hfi1_schedule_send(qp);
		}
		rvt_get_credit(qp, aeth);
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		qp->s_retry = qp->s_retry_cnt;
		/*
		 * If the current request is a TID RDMA WRITE request and the
		 * response is not a TID RDMA WRITE RESP packet, s_last_psn
		 * can't be advanced.
		 */
		if (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE &&
		    opcode != TID_OP(WRITE_RESP) &&
		    cmp_psn(psn, wqe->psn) >= 0)
			return 1;
		update_last_psn(qp, psn);
		return 1;

	case 1:         /* RNR NAK */
		ibp->rvp.n_rnr_naks++;
		if (qp->s_acked == qp->s_tail)
			goto bail_stop;
		if (qp->s_flags & RVT_S_WAIT_RNR)
			goto bail_stop;
		rdi = ib_to_rvt(qp->ibqp.device);
		if (qp->s_rnr_retry == 0 &&
		    !((rdi->post_parms[wqe->wr.opcode].flags &
		      RVT_OPERATION_IGN_RNR_CNT) &&
		      qp->s_rnr_retry_cnt == 0)) {
			status = IB_WC_RNR_RETRY_EXC_ERR;
			goto class_b;
		}
		if (qp->s_rnr_retry_cnt < 7 && qp->s_rnr_retry_cnt > 0)
			qp->s_rnr_retry--;

		/*
		 * The last valid PSN is the previous PSN. For TID RDMA WRITE
		 * request, s_last_psn should be incremented only when a TID
		 * RDMA WRITE RESP is received to avoid skipping lost TID RDMA
		 * WRITE RESP packets.
		 */
		if (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE) {
			reset_psn(qp, qp->s_last_psn + 1);
		} else {
			update_last_psn(qp, psn - 1);
			reset_psn(qp, psn);
		}

		ibp->rvp.n_rc_resends += delta_psn(qp->s_psn, psn);
		qp->s_flags &= ~(RVT_S_WAIT_SSN_CREDIT | RVT_S_WAIT_ACK);
		rvt_stop_rc_timers(qp);
		rvt_add_rnr_timer(qp, aeth);
		return 0;

	case 3:         /* NAK */
		if (qp->s_acked == qp->s_tail)
			goto bail_stop;
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
			hfi1_restart_rc(qp, psn, 0);
			hfi1_schedule_send(qp);
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
				if (wqe->wr.opcode == IB_WR_TID_RDMA_READ)
					hfi1_kern_read_tid_flow_free(qp);

				hfi1_trdma_send_complete(qp, wqe, status);
				rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
			}
			break;

		default:
			/* Ignore other reserved NAK error codes */
			goto reserved;
		}
		qp->s_retry = qp->s_retry_cnt;
		qp->s_rnr_retry = qp->s_rnr_retry_cnt;
		goto bail_stop;

	default:                /* 2: reserved */
reserved:
		/* Ignore reserved NAK codes. */
		goto bail_stop;
	}
	/* cannot be reached  */
bail_stop:
	rvt_stop_rc_timers(qp);
	return ret;
}