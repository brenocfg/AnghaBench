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
struct rvt_qp {size_t state; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_flags; struct hfi1_qp_priv* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/  list; int /*<<< orphan*/  tx_head; } ;
struct hfi1_qp_priv {TYPE_3__ s_iowait; } ;
struct hfi1_pkt_state {TYPE_2__* s_txreq; } ;
struct hfi1_ibdev {int /*<<< orphan*/  iowait_lock; int /*<<< orphan*/  memwait; int /*<<< orphan*/  mem_timer; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;
struct TYPE_5__ {TYPE_1__ txreq; } ;

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
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_hfi1_qpsleep (struct rvt_qp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_seqlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_sequnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wait_kmem(struct hfi1_ibdev *dev,
		     struct rvt_qp *qp,
		     struct hfi1_pkt_state *ps)
{
	struct hfi1_qp_priv *priv = qp->priv;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&qp->s_lock, flags);
	if (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) {
		write_seqlock(&dev->iowait_lock);
		list_add_tail(&ps->s_txreq->txreq.list,
			      &priv->s_iowait.tx_head);
		if (list_empty(&priv->s_iowait.list)) {
			if (list_empty(&dev->memwait))
				mod_timer(&dev->mem_timer, jiffies + 1);
			qp->s_flags |= RVT_S_WAIT_KMEM;
			list_add_tail(&priv->s_iowait.list, &dev->memwait);
			priv->s_iowait.lock = &dev->iowait_lock;
			trace_hfi1_qpsleep(qp, RVT_S_WAIT_KMEM);
			rvt_get_qp(qp);
		}
		write_sequnlock(&dev->iowait_lock);
		qp->s_flags &= ~RVT_S_BUSY;
		ret = -EBUSY;
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);

	return ret;
}