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
typedef  size_t u8 ;
typedef  scalar_t__ u32 ;
struct sdma_engine {int dummy; } ;
struct TYPE_4__ {size_t opcode; } ;
struct rvt_swqe {int /*<<< orphan*/  psn; int /*<<< orphan*/  lpsn; TYPE_1__ wr; } ;
struct rvt_qp {scalar_t__ s_last; scalar_t__ s_size; scalar_t__ s_acked; scalar_t__ s_cur; scalar_t__ s_tail; scalar_t__ state; scalar_t__ s_draining; int /*<<< orphan*/  s_psn; int /*<<< orphan*/  s_state; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  s_retry; int /*<<< orphan*/  remote_ah_attr; int /*<<< orphan*/  s_sending_hpsn; int /*<<< orphan*/  s_sending_psn; int /*<<< orphan*/  s_lock; } ;
struct hfi1_pportdata {TYPE_3__* dd; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rc_delayed_comp; } ;
struct hfi1_ibport {size_t* sl_to_sc; TYPE_2__ rvp; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int HFI1_HAS_SEND_DMA ; 
 scalar_t__ IB_QPS_SQD ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_LAST ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ cmp_psn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ib_hfi1_wc_opcode ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 struct sdma_engine* qp_to_sdma_engine (struct rvt_qp*,size_t) ; 
 size_t rdma_ah_get_sl (int /*<<< orphan*/ *) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_put_swqe (struct rvt_swqe*) ; 
 int /*<<< orphan*/  rvt_qp_swqe_complete (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_qp_wqe_unreserve (struct rvt_qp*,struct rvt_swqe*) ; 
 int /*<<< orphan*/  sdma_engine_progress_schedule (struct sdma_engine*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_hfi1_qp_send_completion (struct rvt_qp*,struct rvt_swqe*,scalar_t__) ; 
 int /*<<< orphan*/  update_last_psn (struct rvt_qp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rvt_swqe *do_rc_completion(struct rvt_qp *qp,
					 struct rvt_swqe *wqe,
					 struct hfi1_ibport *ibp)
{
	lockdep_assert_held(&qp->s_lock);
	/*
	 * Don't decrement refcount and don't generate a
	 * completion if the SWQE is being resent until the send
	 * is finished.
	 */
	if (cmp_psn(wqe->lpsn, qp->s_sending_psn) < 0 ||
	    cmp_psn(qp->s_sending_psn, qp->s_sending_hpsn) > 0) {
		u32 s_last;

		rvt_put_swqe(wqe);
		rvt_qp_wqe_unreserve(qp, wqe);
		s_last = qp->s_last;
		trace_hfi1_qp_send_completion(qp, wqe, s_last);
		if (++s_last >= qp->s_size)
			s_last = 0;
		qp->s_last = s_last;
		/* see post_send() */
		barrier();
		rvt_qp_swqe_complete(qp,
				     wqe,
				     ib_hfi1_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	} else {
		struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);

		this_cpu_inc(*ibp->rvp.rc_delayed_comp);
		/*
		 * If send progress not running attempt to progress
		 * SDMA queue.
		 */
		if (ppd->dd->flags & HFI1_HAS_SEND_DMA) {
			struct sdma_engine *engine;
			u8 sl = rdma_ah_get_sl(&qp->remote_ah_attr);
			u8 sc5;

			/* For now use sc to find engine */
			sc5 = ibp->sl_to_sc[sl];
			engine = qp_to_sdma_engine(qp, sc5);
			sdma_engine_progress_schedule(engine);
		}
	}

	qp->s_retry = qp->s_retry_cnt;
	update_last_psn(qp, wqe->lpsn);

	/*
	 * If we are completing a request which is in the process of
	 * being resent, we can stop re-sending it since we know the
	 * responder has already seen it.
	 */
	if (qp->s_acked == qp->s_cur) {
		if (++qp->s_cur >= qp->s_size)
			qp->s_cur = 0;
		qp->s_acked = qp->s_cur;
		wqe = rvt_get_swqe_ptr(qp, qp->s_cur);
		if (qp->s_acked != qp->s_tail) {
			qp->s_state = OP(SEND_LAST);
			qp->s_psn = wqe->psn;
		}
	} else {
		if (++qp->s_acked >= qp->s_size)
			qp->s_acked = 0;
		if (qp->state == IB_QPS_SQD && qp->s_acked == qp->s_cur)
			qp->s_draining = 0;
		wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	}
	return wqe;
}