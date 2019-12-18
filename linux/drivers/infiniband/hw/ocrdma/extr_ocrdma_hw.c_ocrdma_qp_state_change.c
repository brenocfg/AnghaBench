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
struct ocrdma_qp {int state; int /*<<< orphan*/  q_lock; } ;
typedef  enum ocrdma_qp_state { ____Placeholder_ocrdma_qp_state } ocrdma_qp_state ;
typedef  enum ib_qp_state { ____Placeholder_ib_qp_state } ib_qp_state ;

/* Variables and functions */
 int OCRDMA_QPS_ERR ; 
 int OCRDMA_QPS_INIT ; 
 int get_ibqp_state (int) ; 
 int get_ocrdma_qp_state (int) ; 
 int /*<<< orphan*/  ocrdma_del_flush_qp (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_flush_qp (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  ocrdma_init_hwq_ptr (struct ocrdma_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ocrdma_qp_state_change(struct ocrdma_qp *qp, enum ib_qp_state new_ib_state,
			   enum ib_qp_state *old_ib_state)
{
	unsigned long flags;
	enum ocrdma_qp_state new_state;
	new_state = get_ocrdma_qp_state(new_ib_state);

	/* sync with wqe and rqe posting */
	spin_lock_irqsave(&qp->q_lock, flags);

	if (old_ib_state)
		*old_ib_state = get_ibqp_state(qp->state);
	if (new_state == qp->state) {
		spin_unlock_irqrestore(&qp->q_lock, flags);
		return 1;
	}


	if (new_state == OCRDMA_QPS_INIT) {
		ocrdma_init_hwq_ptr(qp);
		ocrdma_del_flush_qp(qp);
	} else if (new_state == OCRDMA_QPS_ERR) {
		ocrdma_flush_qp(qp);
	}

	qp->state = new_state;

	spin_unlock_irqrestore(&qp->q_lock, flags);
	return 0;
}