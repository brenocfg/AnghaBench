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
struct TYPE_3__ {int /*<<< orphan*/  device; } ;
struct rvt_qp {size_t state; int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_flags; TYPE_1__ ibqp; struct qib_qp_priv* priv; } ;
struct qib_qp_priv {int /*<<< orphan*/  iowait; } ;
struct TYPE_4__ {int /*<<< orphan*/  pending_lock; } ;
struct qib_ibdev {TYPE_2__ rdi; int /*<<< orphan*/  piowait; int /*<<< orphan*/  n_piowait; } ;
struct qib_devdata {int /*<<< orphan*/  (* f_wantpiobuf_intr ) (struct qib_devdata*,int) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int RVT_PROCESS_RECV_OK ; 
 int /*<<< orphan*/  RVT_S_BUSY ; 
 int /*<<< orphan*/  RVT_S_WAIT_PIO ; 
 struct qib_devdata* dd_from_dev (struct qib_ibdev*) ; 
 int* ib_rvt_state_ops ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct qib_devdata*,int) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int no_bufs_available(struct rvt_qp *qp)
{
	struct qib_qp_priv *priv = qp->priv;
	struct qib_ibdev *dev = to_idev(qp->ibqp.device);
	struct qib_devdata *dd;
	unsigned long flags;
	int ret = 0;

	/*
	 * Note that as soon as want_buffer() is called and
	 * possibly before it returns, qib_ib_piobufavail()
	 * could be called. Therefore, put QP on the I/O wait list before
	 * enabling the PIO avail interrupt.
	 */
	spin_lock_irqsave(&qp->s_lock, flags);
	if (ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK) {
		spin_lock(&dev->rdi.pending_lock);
		if (list_empty(&priv->iowait)) {
			dev->n_piowait++;
			qp->s_flags |= RVT_S_WAIT_PIO;
			list_add_tail(&priv->iowait, &dev->piowait);
			dd = dd_from_dev(dev);
			dd->f_wantpiobuf_intr(dd, 1);
		}
		spin_unlock(&dev->rdi.pending_lock);
		qp->s_flags &= ~RVT_S_BUSY;
		ret = -EBUSY;
	}
	spin_unlock_irqrestore(&qp->s_lock, flags);
	return ret;
}