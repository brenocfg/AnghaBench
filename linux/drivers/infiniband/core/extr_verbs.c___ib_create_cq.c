#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* create_cq ) (struct ib_cq*,struct ib_cq_init_attr const*,int /*<<< orphan*/ *) ;} ;
struct ib_device {TYPE_1__ ops; } ;
struct ib_cq_init_attr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct ib_cq {void (* event_handler ) (struct ib_event*,void*) ;TYPE_2__ res; int /*<<< orphan*/  usecnt; void* cq_context; int /*<<< orphan*/  comp_handler; int /*<<< orphan*/ * uobject; struct ib_device* device; } ;
typedef  int /*<<< orphan*/  ib_comp_handler ;

/* Variables and functions */
 int ENOMEM ; 
 struct ib_cq* ERR_PTR (int) ; 
 int /*<<< orphan*/  RDMA_RESTRACK_CQ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_cq ; 
 int /*<<< orphan*/  kfree (struct ib_cq*) ; 
 int /*<<< orphan*/  rdma_restrack_kadd (TYPE_2__*) ; 
 int /*<<< orphan*/  rdma_restrack_set_task (TYPE_2__*,char const*) ; 
 struct ib_cq* rdma_zalloc_drv_obj (struct ib_device*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_cq*,struct ib_cq_init_attr const*,int /*<<< orphan*/ *) ; 

struct ib_cq *__ib_create_cq(struct ib_device *device,
			     ib_comp_handler comp_handler,
			     void (*event_handler)(struct ib_event *, void *),
			     void *cq_context,
			     const struct ib_cq_init_attr *cq_attr,
			     const char *caller)
{
	struct ib_cq *cq;
	int ret;

	cq = rdma_zalloc_drv_obj(device, ib_cq);
	if (!cq)
		return ERR_PTR(-ENOMEM);

	cq->device = device;
	cq->uobject = NULL;
	cq->comp_handler = comp_handler;
	cq->event_handler = event_handler;
	cq->cq_context = cq_context;
	atomic_set(&cq->usecnt, 0);
	cq->res.type = RDMA_RESTRACK_CQ;
	rdma_restrack_set_task(&cq->res, caller);

	ret = device->ops.create_cq(cq, cq_attr, NULL);
	if (ret) {
		kfree(cq);
		return ERR_PTR(ret);
	}

	rdma_restrack_kadd(&cq->res);
	return cq;
}