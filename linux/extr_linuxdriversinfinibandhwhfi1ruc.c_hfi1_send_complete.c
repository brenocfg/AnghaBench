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
typedef  scalar_t__ u32 ;
struct TYPE_7__ {size_t opcode; } ;
struct TYPE_6__ {int /*<<< orphan*/  ah; } ;
struct rvt_swqe {TYPE_3__ wr; TYPE_2__ ud_wr; } ;
struct TYPE_5__ {scalar_t__ qp_type; } ;
struct rvt_qp {size_t state; scalar_t__ s_last; scalar_t__ s_size; scalar_t__ s_acked; scalar_t__ s_cur; scalar_t__ s_tail; scalar_t__ s_draining; TYPE_1__ ibqp; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;
struct TYPE_8__ {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 size_t IB_QPS_SQD ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 scalar_t__ IB_QPT_UD ; 
 int RVT_PROCESS_OR_FLUSH_SEND ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/ * ib_hfi1_wc_opcode ; 
 int* ib_rvt_state_ops ; 
 TYPE_4__* ibah_to_rvtah (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvt_put_swqe (struct rvt_swqe*) ; 
 int /*<<< orphan*/  rvt_qp_swqe_complete (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_hfi1_qp_send_completion (struct rvt_qp*,struct rvt_swqe*,scalar_t__) ; 

void hfi1_send_complete(struct rvt_qp *qp, struct rvt_swqe *wqe,
			enum ib_wc_status status)
{
	u32 old_last, last;

	if (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_OR_FLUSH_SEND))
		return;

	last = qp->s_last;
	old_last = last;
	trace_hfi1_qp_send_completion(qp, wqe, last);
	if (++last >= qp->s_size)
		last = 0;
	trace_hfi1_qp_send_completion(qp, wqe, last);
	qp->s_last = last;
	/* See post_send() */
	barrier();
	rvt_put_swqe(wqe);
	if (qp->ibqp.qp_type == IB_QPT_UD ||
	    qp->ibqp.qp_type == IB_QPT_SMI ||
	    qp->ibqp.qp_type == IB_QPT_GSI)
		atomic_dec(&ibah_to_rvtah(wqe->ud_wr.ah)->refcount);

	rvt_qp_swqe_complete(qp,
			     wqe,
			     ib_hfi1_wc_opcode[wqe->wr.opcode],
			     status);

	if (qp->s_acked == old_last)
		qp->s_acked = last;
	if (qp->s_cur == old_last)
		qp->s_cur = last;
	if (qp->s_tail == old_last)
		qp->s_tail = last;
	if (qp->state == IB_QPS_SQD && last == qp->s_cur)
		qp->s_draining = 0;
}