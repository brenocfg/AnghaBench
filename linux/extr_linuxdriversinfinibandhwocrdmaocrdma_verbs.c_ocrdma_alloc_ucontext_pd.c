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
struct ocrdma_dev {int /*<<< orphan*/  ibdev; } ;
struct ib_udata {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * device; } ;
struct TYPE_6__ {TYPE_1__ ibpd; struct ocrdma_ucontext* uctx; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 TYPE_2__* _ocrdma_alloc_pd (struct ocrdma_dev*,struct ocrdma_ucontext*,struct ib_udata*) ; 

__attribute__((used)) static int ocrdma_alloc_ucontext_pd(struct ocrdma_dev *dev,
				    struct ocrdma_ucontext *uctx,
				    struct ib_udata *udata)
{
	int status = 0;

	uctx->cntxt_pd = _ocrdma_alloc_pd(dev, uctx, udata);
	if (IS_ERR(uctx->cntxt_pd)) {
		status = PTR_ERR(uctx->cntxt_pd);
		uctx->cntxt_pd = NULL;
		goto err;
	}

	uctx->cntxt_pd->uctx = uctx;
	uctx->cntxt_pd->ibpd.device = &dev->ibdev;
err:
	return status;
}