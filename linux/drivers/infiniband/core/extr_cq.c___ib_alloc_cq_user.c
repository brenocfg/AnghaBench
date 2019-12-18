#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ib_udata {int dummy; } ;
struct TYPE_5__ {int (* create_cq ) (struct ib_cq*,struct ib_cq_init_attr*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* destroy_cq ) (struct ib_cq*,struct ib_udata*) ;} ;
struct ib_device {TYPE_1__ ops; } ;
struct ib_cq_init_attr {int cqe; int comp_vector; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct ib_cq {int poll_ctx; struct ib_cq* wc; struct ib_device* device; TYPE_2__ res; int /*<<< orphan*/  comp_wq; int /*<<< orphan*/  work; int /*<<< orphan*/  comp_handler; int /*<<< orphan*/  iop; int /*<<< orphan*/  usecnt; void* cq_context; } ;
typedef  enum ib_poll_context { ____Placeholder_ib_poll_context } ib_poll_context ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IB_CQ_NEXT_COMP ; 
 int /*<<< orphan*/  IB_POLL_BATCH ; 
 int /*<<< orphan*/  IB_POLL_BUDGET_IRQ ; 
#define  IB_POLL_DIRECT 131 
#define  IB_POLL_SOFTIRQ 130 
#define  IB_POLL_UNBOUND_WORKQUEUE 129 
#define  IB_POLL_WORKQUEUE 128 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_CQ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_comp_unbound_wq ; 
 int /*<<< orphan*/  ib_comp_wq ; 
 int /*<<< orphan*/  ib_cq ; 
 int /*<<< orphan*/  ib_cq_completion_direct ; 
 int /*<<< orphan*/  ib_cq_completion_softirq ; 
 int /*<<< orphan*/  ib_cq_completion_workqueue ; 
 int /*<<< orphan*/  ib_cq_poll_work ; 
 int /*<<< orphan*/  ib_poll_handler ; 
 int /*<<< orphan*/  ib_req_notify_cq (struct ib_cq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_poll_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ib_cq*) ; 
 struct ib_cq* kmalloc_array (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_dim_init (struct ib_cq*) ; 
 int /*<<< orphan*/  rdma_restrack_del (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_restrack_kadd (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_restrack_set_task (TYPE_2__*,char const*) ; 
 struct ib_cq* rdma_zalloc_drv_obj (struct ib_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_cq*,struct ib_cq_init_attr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct ib_cq*,struct ib_udata*) ; 

struct ib_cq *__ib_alloc_cq_user(struct ib_device *dev, void *private,
				 int nr_cqe, int comp_vector,
				 enum ib_poll_context poll_ctx,
				 const char *caller, struct ib_udata *udata)
{
	struct ib_cq_init_attr cq_attr = {
		.cqe		= nr_cqe,
		.comp_vector	= comp_vector,
	};
	struct ib_cq *cq;
	int ret = -ENOMEM;

	cq = rdma_zalloc_drv_obj(dev, ib_cq);
	if (!cq)
		return ERR_PTR(ret);

	cq->device = dev;
	cq->cq_context = private;
	cq->poll_ctx = poll_ctx;
	atomic_set(&cq->usecnt, 0);

	cq->wc = kmalloc_array(IB_POLL_BATCH, sizeof(*cq->wc), GFP_KERNEL);
	if (!cq->wc)
		goto out_free_cq;

	cq->res.type = RDMA_RESTRACK_CQ;
	rdma_restrack_set_task(&cq->res, caller);

	ret = dev->ops.create_cq(cq, &cq_attr, NULL);
	if (ret)
		goto out_free_wc;

	rdma_restrack_kadd(&cq->res);

	rdma_dim_init(cq);

	switch (cq->poll_ctx) {
	case IB_POLL_DIRECT:
		cq->comp_handler = ib_cq_completion_direct;
		break;
	case IB_POLL_SOFTIRQ:
		cq->comp_handler = ib_cq_completion_softirq;

		irq_poll_init(&cq->iop, IB_POLL_BUDGET_IRQ, ib_poll_handler);
		ib_req_notify_cq(cq, IB_CQ_NEXT_COMP);
		break;
	case IB_POLL_WORKQUEUE:
	case IB_POLL_UNBOUND_WORKQUEUE:
		cq->comp_handler = ib_cq_completion_workqueue;
		INIT_WORK(&cq->work, ib_cq_poll_work);
		ib_req_notify_cq(cq, IB_CQ_NEXT_COMP);
		cq->comp_wq = (cq->poll_ctx == IB_POLL_WORKQUEUE) ?
				ib_comp_wq : ib_comp_unbound_wq;
		break;
	default:
		ret = -EINVAL;
		goto out_destroy_cq;
	}

	return cq;

out_destroy_cq:
	rdma_restrack_del(&cq->res);
	cq->device->ops.destroy_cq(cq, udata);
out_free_wc:
	kfree(cq->wc);
out_free_cq:
	kfree(cq);
	return ERR_PTR(ret);
}