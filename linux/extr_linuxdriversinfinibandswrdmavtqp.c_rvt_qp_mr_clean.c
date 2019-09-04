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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ qp_type; int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  device; } ;
struct rvt_qp {scalar_t__ state; TYPE_2__ ibqp; int /*<<< orphan*/  r_lock; int /*<<< orphan*/  s_hlock; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  r_sge; } ;
struct TYPE_3__ {TYPE_2__* qp; } ;
struct ib_event {int /*<<< orphan*/  event; TYPE_1__ element; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_EVENT_QP_LAST_WQE_REACHED ; 
 scalar_t__ IB_QPS_ERR ; 
 scalar_t__ IB_QPS_RESET ; 
 scalar_t__ IB_QPT_GSI ; 
 scalar_t__ IB_QPT_SMI ; 
 int /*<<< orphan*/  IB_WC_LOC_PROT_ERR ; 
 int rvt_error_qp (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 scalar_t__ rvt_qp_acks_has_lkey (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 scalar_t__ rvt_qp_sends_has_lkey (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 scalar_t__ rvt_ss_has_lkey (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 

void rvt_qp_mr_clean(struct rvt_qp *qp, u32 lkey)
{
	bool lastwqe = false;

	if (qp->ibqp.qp_type == IB_QPT_SMI ||
	    qp->ibqp.qp_type == IB_QPT_GSI)
		/* avoid special QPs */
		return;
	spin_lock_irq(&qp->r_lock);
	spin_lock(&qp->s_hlock);
	spin_lock(&qp->s_lock);

	if (qp->state == IB_QPS_ERR || qp->state == IB_QPS_RESET)
		goto check_lwqe;

	if (rvt_ss_has_lkey(&qp->r_sge, lkey) ||
	    rvt_qp_sends_has_lkey(qp, lkey) ||
	    rvt_qp_acks_has_lkey(qp, lkey))
		lastwqe = rvt_error_qp(qp, IB_WC_LOC_PROT_ERR);
check_lwqe:
	spin_unlock(&qp->s_lock);
	spin_unlock(&qp->s_hlock);
	spin_unlock_irq(&qp->r_lock);
	if (lastwqe) {
		struct ib_event ev;

		ev.device = qp->ibqp.device;
		ev.element.qp = &qp->ibqp;
		ev.event = IB_EVENT_QP_LAST_WQE_REACHED;
		qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
	}
}