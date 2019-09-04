#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v3d_dev {int /*<<< orphan*/  dev; TYPE_4__* render_job; TYPE_2__* bin_job; int /*<<< orphan*/  overflow_mem_work; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_7__ {int /*<<< orphan*/  done_fence; } ;
struct TYPE_8__ {TYPE_3__ render; } ;
struct TYPE_5__ {int /*<<< orphan*/  done_fence; } ;
struct TYPE_6__ {TYPE_1__ bin; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int V3D_CORE_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  V3D_CTL_INT_CLR ; 
 int /*<<< orphan*/  V3D_CTL_INT_STS ; 
 int V3D_INT_FLDONE ; 
 int V3D_INT_FRDONE ; 
 int V3D_INT_GMPV ; 
 int V3D_INT_OUTOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_fence_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
v3d_irq(int irq, void *arg)
{
	struct v3d_dev *v3d = arg;
	u32 intsts;
	irqreturn_t status = IRQ_NONE;

	intsts = V3D_CORE_READ(0, V3D_CTL_INT_STS);

	/* Acknowledge the interrupts we're handling here. */
	V3D_CORE_WRITE(0, V3D_CTL_INT_CLR, intsts);

	if (intsts & V3D_INT_OUTOMEM) {
		/* Note that the OOM status is edge signaled, so the
		 * interrupt won't happen again until the we actually
		 * add more memory.
		 */
		schedule_work(&v3d->overflow_mem_work);
		status = IRQ_HANDLED;
	}

	if (intsts & V3D_INT_FLDONE) {
		dma_fence_signal(v3d->bin_job->bin.done_fence);
		status = IRQ_HANDLED;
	}

	if (intsts & V3D_INT_FRDONE) {
		dma_fence_signal(v3d->render_job->render.done_fence);
		status = IRQ_HANDLED;
	}

	/* We shouldn't be triggering these if we have GMP in
	 * always-allowed mode.
	 */
	if (intsts & V3D_INT_GMPV)
		dev_err(v3d->dev, "GMP violation\n");

	return status;
}