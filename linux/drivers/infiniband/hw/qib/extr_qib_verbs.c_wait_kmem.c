#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rvt_qp {size_t state; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_flags; struct qib_qp_priv* priv; } ;
struct qib_qp_priv {int /*<<< orphan*/  iowait; } ;
struct TYPE_2__ {int /*<<< orphan*/  pending_lock; } ;
struct qib_ibdev {TYPE_1__ rdi; int /*<<< orphan*/  memwait; int /*<<< orphan*/  mem_timer; } ;

/* Variables and functions */
 int EBUSY ; 
 int RVT_PROCESS_RECV_OK ; 
 int /*<<< orphan*/  RVT_S_BUSY ; 
 int /*<<< orphan*/  RVT_S_WAIT_KMEM ; 
 int* ib_rvt_state_ops ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int wait_kmem(struct qib_ibdev *dev, struct rvt_qp *qp)
{
	struct qib_qp_priv *priv = qp->priv;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&qp->s_lock, flags);
	if (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) {
		spin_lock(&dev->rdi.pending_lock);
		if (list_empty(&priv->iowait)) {
			if (list_empty(&dev->memwait))
				mod_timer(&dev->mem_timer, jiffies + 1);
			qp->s_flags |= RVT_S_WAIT_KMEM;
			list_add_tail(&priv->iowait, &dev->memwait);
		}
		spin_unlock(&dev->rdi.pending_lock);
		qp->s_flags &= ~RVT_S_BUSY;
		ret = -EBUSY;
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);

	return ret;
}