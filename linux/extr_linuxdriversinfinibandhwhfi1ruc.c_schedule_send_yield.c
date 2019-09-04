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
struct rvt_qp {int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_flags; } ;
struct hfi1_pkt_state {int pkts_sent; scalar_t__ timeout_int; scalar_t__ timeout; TYPE_2__* ppd; int /*<<< orphan*/  flags; int /*<<< orphan*/  cpu; int /*<<< orphan*/  in_thread; } ;
struct TYPE_4__ {TYPE_1__* dd; int /*<<< orphan*/  hfi1_wq; } ;
struct TYPE_3__ {int /*<<< orphan*/ * send_schedule; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVT_S_BUSY ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  hfi1_schedule_send (struct rvt_qp*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_hfi1_rc_expired_time_slice (struct rvt_qp*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ workqueue_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool schedule_send_yield(struct rvt_qp *qp,
				struct hfi1_pkt_state *ps)
{
	ps->pkts_sent = true;

	if (unlikely(time_after(jiffies, ps->timeout))) {
		if (!ps->in_thread ||
		    workqueue_congested(ps->cpu, ps->ppd->hfi1_wq)) {
			spin_lock_irqsave(&qp->s_lock, ps->flags);
			qp->s_flags &= ~RVT_S_BUSY;
			hfi1_schedule_send(qp);
			spin_unlock_irqrestore(&qp->s_lock, ps->flags);
			this_cpu_inc(*ps->ppd->dd->send_schedule);
			trace_hfi1_rc_expired_time_slice(qp, true);
			return true;
		}

		cond_resched();
		this_cpu_inc(*ps->ppd->dd->send_schedule);
		ps->timeout = jiffies + ps->timeout_int;
	}

	trace_hfi1_rc_expired_time_slice(qp, false);
	return false;
}