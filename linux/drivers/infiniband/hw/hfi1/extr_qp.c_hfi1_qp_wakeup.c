#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct rvt_qp {int s_flags; int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfi1_qp_schedule (struct rvt_qp*) ; 
 int /*<<< orphan*/  rvt_put_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_hfi1_qpwakeup (struct rvt_qp*,int) ; 

void hfi1_qp_wakeup(struct rvt_qp *qp, u32 flag)
{
	unsigned long flags;

	spin_lock_irqsave(&qp->s_lock, flags);
	if (qp->s_flags & flag) {
		qp->s_flags &= ~flag;
		trace_hfi1_qpwakeup(qp, flag);
		hfi1_qp_schedule(qp);
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);
	/* Notify hfi1_destroy_qp() if it is waiting. */
	rvt_put_qp(qp);
}