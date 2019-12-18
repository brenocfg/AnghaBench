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
struct rvt_qp {TYPE_1__ ibqp; struct qib_qp_priv* priv; } ;
struct qib_qp_priv {int /*<<< orphan*/  iowait; } ;
struct TYPE_4__ {int /*<<< orphan*/  pending_lock; } ;
struct qib_ibdev {TYPE_2__ rdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct qib_ibdev* to_idev (int /*<<< orphan*/ ) ; 

void qib_flush_qp_waiters(struct rvt_qp *qp)
{
	struct qib_qp_priv *priv = qp->priv;
	struct qib_ibdev *dev = to_idev(qp->ibqp.device);

	spin_lock(&dev->rdi.pending_lock);
	if (!list_empty(&priv->iowait))
		list_del_init(&priv->iowait);
	spin_unlock(&dev->rdi.pending_lock);
}