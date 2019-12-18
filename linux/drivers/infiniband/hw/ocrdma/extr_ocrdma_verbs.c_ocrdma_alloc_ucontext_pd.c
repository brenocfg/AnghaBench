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
struct ocrdma_ucontext {TYPE_2__* cntxt_pd; } ;
struct ib_device {int dummy; } ;
struct ocrdma_dev {struct ib_device ibdev; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {struct ib_device* device; } ;
struct TYPE_5__ {struct ib_device* device; } ;
struct TYPE_6__ {TYPE_1__ ibpd; struct ocrdma_ucontext* uctx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int _ocrdma_alloc_pd (struct ocrdma_dev*,TYPE_2__*,struct ocrdma_ucontext*,struct ib_udata*) ; 
 TYPE_2__* get_ocrdma_pd (struct ib_pd*) ; 
 int /*<<< orphan*/  ib_pd ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 struct ib_pd* rdma_zalloc_drv_obj (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocrdma_alloc_ucontext_pd(struct ocrdma_dev *dev,
				    struct ocrdma_ucontext *uctx,
				    struct ib_udata *udata)
{
	struct ib_device *ibdev = &dev->ibdev;
	struct ib_pd *pd;
	int status;

	pd = rdma_zalloc_drv_obj(ibdev, ib_pd);
	if (!pd)
		return -ENOMEM;

	pd->device  = ibdev;
	uctx->cntxt_pd = get_ocrdma_pd(pd);

	status = _ocrdma_alloc_pd(dev, uctx->cntxt_pd, uctx, udata);
	if (status) {
		kfree(uctx->cntxt_pd);
		goto err;
	}

	uctx->cntxt_pd->uctx = uctx;
	uctx->cntxt_pd->ibpd.device = &dev->ibdev;
err:
	return status;
}