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
struct ib_udata {int dummy; } ;
struct ib_cq {int poll_ctx; struct ib_cq* wc; struct ib_cq* dim; int /*<<< orphan*/  work; TYPE_2__* device; int /*<<< orphan*/  res; int /*<<< orphan*/  iop; int /*<<< orphan*/  usecnt; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy_cq ) (struct ib_cq*,struct ib_udata*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;

/* Variables and functions */
#define  IB_POLL_DIRECT 131 
#define  IB_POLL_SOFTIRQ 130 
#define  IB_POLL_UNBOUND_WORKQUEUE 129 
#define  IB_POLL_WORKQUEUE 128 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_poll_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_cq*) ; 
 int /*<<< orphan*/  rdma_restrack_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_cq*,struct ib_udata*) ; 

void ib_free_cq_user(struct ib_cq *cq, struct ib_udata *udata)
{
	if (WARN_ON_ONCE(atomic_read(&cq->usecnt)))
		return;

	switch (cq->poll_ctx) {
	case IB_POLL_DIRECT:
		break;
	case IB_POLL_SOFTIRQ:
		irq_poll_disable(&cq->iop);
		break;
	case IB_POLL_WORKQUEUE:
	case IB_POLL_UNBOUND_WORKQUEUE:
		cancel_work_sync(&cq->work);
		break;
	default:
		WARN_ON_ONCE(1);
	}

	rdma_restrack_del(&cq->res);
	cq->device->ops.destroy_cq(cq, udata);
	if (cq->dim)
		cancel_work_sync(&cq->dim->work);
	kfree(cq->dim);
	kfree(cq->wc);
	kfree(cq);
}