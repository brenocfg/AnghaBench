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
struct cxl_ioctl_start_work {int flags; scalar_t__ num_interrupts; int /*<<< orphan*/  work_element_descriptor; } ;
struct cxl_context {TYPE_1__* afu; } ;
struct TYPE_2__ {scalar_t__ pp_irqs; scalar_t__ irqs_max; } ;

/* Variables and functions */
 int CXL_START_WORK_NUM_IRQS ; 
 int EINVAL ; 
 int afu_register_irqs (struct cxl_context*,scalar_t__) ; 
 int /*<<< orphan*/  afu_release_irqs (struct cxl_context*,struct cxl_context*) ; 
 int /*<<< orphan*/  current ; 
 int cxl_start_context (struct cxl_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cxl_start_work(struct cxl_context *ctx,
		   struct cxl_ioctl_start_work *work)
{
	int rc;

	/* code taken from afu_ioctl_start_work */
	if (!(work->flags & CXL_START_WORK_NUM_IRQS))
		work->num_interrupts = ctx->afu->pp_irqs;
	else if ((work->num_interrupts < ctx->afu->pp_irqs) ||
		 (work->num_interrupts > ctx->afu->irqs_max)) {
		return -EINVAL;
	}

	rc = afu_register_irqs(ctx, work->num_interrupts);
	if (rc)
		return rc;

	rc = cxl_start_context(ctx, work->work_element_descriptor, current);
	if (rc < 0) {
		afu_release_irqs(ctx, ctx);
		return rc;
	}

	return 0;
}