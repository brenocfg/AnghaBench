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
struct ib_qp {struct ib_device* device; } ;
struct rvt_qp {int /*<<< orphan*/  s_flags; struct ib_qp ibqp; struct hfi1_qp_priv* priv; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lock; int /*<<< orphan*/  list; } ;
struct hfi1_qp_priv {TYPE_1__ s_iowait; } ;
struct hfi1_ibdev {int /*<<< orphan*/  iowait_lock; int /*<<< orphan*/  memwait; int /*<<< orphan*/  mem_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVT_S_WAIT_KMEM ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  rvt_get_qp (struct rvt_qp*) ; 
 struct hfi1_ibdev* to_idev (struct ib_device*) ; 
 int /*<<< orphan*/  trace_hfi1_qpsleep (struct rvt_qp*,int /*<<< orphan*/ ) ; 

void hfi1_wait_kmem(struct rvt_qp *qp)
{
	struct hfi1_qp_priv *priv = qp->priv;
	struct ib_qp *ibqp = &qp->ibqp;
	struct ib_device *ibdev = ibqp->device;
	struct hfi1_ibdev *dev = to_idev(ibdev);

	if (list_empty(&priv->s_iowait.list)) {
		if (list_empty(&dev->memwait))
			mod_timer(&dev->mem_timer, jiffies + 1);
		qp->s_flags |= RVT_S_WAIT_KMEM;
		list_add_tail(&priv->s_iowait.list, &dev->memwait);
		priv->s_iowait.lock = &dev->iowait_lock;
		trace_hfi1_qpsleep(qp, RVT_S_WAIT_KMEM);
		rvt_get_qp(qp);
	}
}