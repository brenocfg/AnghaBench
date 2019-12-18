#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* xrcd; } ;
struct TYPE_10__ {TYPE_1__ xrc; TYPE_6__* cq; } ;
struct ib_srq_init_attr {scalar_t__ srq_type; TYPE_2__ ext; int /*<<< orphan*/  srq_context; int /*<<< orphan*/  event_handler; } ;
struct TYPE_13__ {TYPE_4__* xrcd; } ;
struct TYPE_15__ {TYPE_6__* cq; TYPE_5__ xrc; } ;
struct ib_srq {scalar_t__ srq_type; TYPE_7__ ext; struct ib_pd* pd; int /*<<< orphan*/  srq_context; int /*<<< orphan*/  event_handler; TYPE_8__* device; } ;
struct ib_pd {int /*<<< orphan*/  usecnt; TYPE_8__* device; } ;
struct TYPE_11__ {int (* create_srq ) (struct ib_srq*,struct ib_srq_init_attr*,int /*<<< orphan*/ *) ;} ;
struct TYPE_16__ {TYPE_3__ ops; } ;
struct TYPE_14__ {int /*<<< orphan*/  usecnt; } ;
struct TYPE_12__ {int /*<<< orphan*/  usecnt; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 struct ib_srq* ERR_PTR (int) ; 
 scalar_t__ IB_SRQT_XRC ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_srq ; 
 scalar_t__ ib_srq_has_cq (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ib_srq*) ; 
 struct ib_srq* rdma_zalloc_drv_obj (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int stub1 (struct ib_srq*,struct ib_srq_init_attr*,int /*<<< orphan*/ *) ; 

struct ib_srq *ib_create_srq(struct ib_pd *pd,
			     struct ib_srq_init_attr *srq_init_attr)
{
	struct ib_srq *srq;
	int ret;

	if (!pd->device->ops.create_srq)
		return ERR_PTR(-EOPNOTSUPP);

	srq = rdma_zalloc_drv_obj(pd->device, ib_srq);
	if (!srq)
		return ERR_PTR(-ENOMEM);

	srq->device = pd->device;
	srq->pd = pd;
	srq->event_handler = srq_init_attr->event_handler;
	srq->srq_context = srq_init_attr->srq_context;
	srq->srq_type = srq_init_attr->srq_type;

	if (ib_srq_has_cq(srq->srq_type)) {
		srq->ext.cq = srq_init_attr->ext.cq;
		atomic_inc(&srq->ext.cq->usecnt);
	}
	if (srq->srq_type == IB_SRQT_XRC) {
		srq->ext.xrc.xrcd = srq_init_attr->ext.xrc.xrcd;
		atomic_inc(&srq->ext.xrc.xrcd->usecnt);
	}
	atomic_inc(&pd->usecnt);

	ret = pd->device->ops.create_srq(srq, srq_init_attr, NULL);
	if (ret) {
		atomic_dec(&srq->pd->usecnt);
		if (srq->srq_type == IB_SRQT_XRC)
			atomic_dec(&srq->ext.xrc.xrcd->usecnt);
		if (ib_srq_has_cq(srq->srq_type))
			atomic_dec(&srq->ext.cq->usecnt);
		kfree(srq);
		return ERR_PTR(ret);
	}

	return srq;
}