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
struct timer_list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {int s_flags; int port_num; int /*<<< orphan*/  r_lock; int /*<<< orphan*/  s_lock; scalar_t__ s_last_psn; int /*<<< orphan*/  s_timer; TYPE_1__ ibqp; } ;
struct rvt_ibport {int /*<<< orphan*/  n_rc_timeouts; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* schedule_send ) (struct rvt_qp*) ;int /*<<< orphan*/  (* notify_restart_rc ) (struct rvt_qp*,scalar_t__,int) ;} ;
struct rvt_dev_info {TYPE_2__ driver_f; struct rvt_ibport** ports; } ;

/* Variables and functions */
 int RVT_S_TIMER ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 struct rvt_qp* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct rvt_dev_info* ib_to_rvt (int /*<<< orphan*/ ) ; 
 struct rvt_qp* qp ; 
 int /*<<< orphan*/  s_timer ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct rvt_qp*,scalar_t__,int) ; 
 int /*<<< orphan*/  stub2 (struct rvt_qp*) ; 
 int /*<<< orphan*/  trace_rvt_rc_timeout (struct rvt_qp*,scalar_t__) ; 

__attribute__((used)) static void rvt_rc_timeout(struct timer_list *t)
{
	struct rvt_qp *qp = from_timer(qp, t, s_timer);
	struct rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);
	unsigned long flags;

	spin_lock_irqsave(&qp->r_lock, flags);
	spin_lock(&qp->s_lock);
	if (qp->s_flags & RVT_S_TIMER) {
		struct rvt_ibport *rvp = rdi->ports[qp->port_num - 1];

		qp->s_flags &= ~RVT_S_TIMER;
		rvp->n_rc_timeouts++;
		del_timer(&qp->s_timer);
		trace_rvt_rc_timeout(qp, qp->s_last_psn + 1);
		if (rdi->driver_f.notify_restart_rc)
			rdi->driver_f.notify_restart_rc(qp,
							qp->s_last_psn + 1,
							1);
		rdi->driver_f.schedule_send(qp);
	}
	spin_unlock(&qp->s_lock);
	spin_unlock_irqrestore(&qp->r_lock, flags);
}