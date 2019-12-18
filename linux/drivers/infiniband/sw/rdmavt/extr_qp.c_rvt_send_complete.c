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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {size_t opcode; } ;
struct rvt_swqe {TYPE_2__ wr; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {size_t state; scalar_t__ s_last; scalar_t__ s_acked; scalar_t__ s_cur; scalar_t__ s_tail; scalar_t__ s_draining; TYPE_1__ ibqp; } ;
struct rvt_dev_info {int /*<<< orphan*/ * wc_opcode; } ;
typedef  enum ib_wc_status { ____Placeholder_ib_wc_status } ib_wc_status ;

/* Variables and functions */
 size_t IB_QPS_SQD ; 
 int RVT_PROCESS_OR_FLUSH_SEND ; 
 int* ib_rvt_state_ops ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 scalar_t__ rvt_qp_complete_swqe (struct rvt_qp*,struct rvt_swqe*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_rvt_qp_send_completion (struct rvt_qp*,struct rvt_swqe*,scalar_t__) ; 

void rvt_send_complete(struct rvt_qp *qp, struct rvt_swqe *wqe,
		       enum ib_wc_status status)
{
	u32 old_last, last;
	struct rvt_dev_info *rdi;

	if (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_OR_FLUSH_SEND))
		return;
	rdi = ib_to_rvt(qp->ibqp.device);

	old_last = qp->s_last;
	trace_rvt_qp_send_completion(qp, wqe, old_last);
	last = rvt_qp_complete_swqe(qp, wqe, rdi->wc_opcode[wqe->wr.opcode],
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