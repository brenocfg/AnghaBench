#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t opcode; } ;
struct rvt_swqe {int /*<<< orphan*/  psn; int /*<<< orphan*/  lpsn; TYPE_1__ wr; } ;
struct rvt_qp {scalar_t__ s_acked; scalar_t__ s_cur; scalar_t__ s_size; scalar_t__ s_tail; scalar_t__ state; scalar_t__ s_draining; int /*<<< orphan*/  s_psn; int /*<<< orphan*/  s_state; int /*<<< orphan*/  s_retry_cnt; int /*<<< orphan*/  s_retry; int /*<<< orphan*/  s_sending_hpsn; int /*<<< orphan*/  s_sending_psn; } ;
struct TYPE_4__ {int /*<<< orphan*/ * rc_delayed_comp; } ;
struct qib_ibport {TYPE_2__ rvp; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_SQD ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  OP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_LAST ; 
 int /*<<< orphan*/ * ib_qib_wc_opcode ; 
 scalar_t__ qib_cmp24 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rvt_swqe* rvt_get_swqe_ptr (struct rvt_qp*,scalar_t__) ; 
 int /*<<< orphan*/  rvt_qp_complete_swqe (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_last_psn (struct rvt_qp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct rvt_swqe *do_rc_completion(struct rvt_qp *qp,
					 struct rvt_swqe *wqe,
					 struct qib_ibport *ibp)
{
	/*
	 * Don't decrement refcount and don't generate a
	 * completion if the SWQE is being resent until the send
	 * is finished.
	 */
	if (qib_cmp24(wqe->lpsn, qp->s_sending_psn) < 0 ||
	    qib_cmp24(qp->s_sending_psn, qp->s_sending_hpsn) > 0)
		rvt_qp_complete_swqe(qp,
				     wqe,
				     ib_qib_wc_opcode[wqe->wr.opcode],
				     IB_WC_SUCCESS);
	else
		this_cpu_inc(*ibp->rvp.rc_delayed_comp);

	qp->s_retry = qp->s_retry_cnt;
	update_last_psn(qp, wqe->lpsn);

	/*
	 * If we are completing a request which is in the process of
	 * being resent, we can stop resending it since we know the
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