#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct v3d_fence {int /*<<< orphan*/  base; int /*<<< orphan*/  seqno; } ;
struct v3d_dev {scalar_t__ single_irq_line; int /*<<< orphan*/  dev; int /*<<< orphan*/  drm; TYPE_6__* csd_job; TYPE_4__* render_job; TYPE_2__* bin_job; int /*<<< orphan*/  overflow_mem_work; } ;
typedef  scalar_t__ irqreturn_t ;
struct TYPE_11__ {int /*<<< orphan*/  irq_fence; } ;
struct TYPE_12__ {TYPE_5__ base; } ;
struct TYPE_9__ {int /*<<< orphan*/  irq_fence; } ;
struct TYPE_10__ {TYPE_3__ base; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq_fence; } ;
struct TYPE_8__ {TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ IRQ_HANDLED ; 
 scalar_t__ IRQ_NONE ; 
 int V3D_CORE_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_CORE_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  V3D_CTL_INT_CLR ; 
 int /*<<< orphan*/  V3D_CTL_INT_STS ; 
 int V3D_INT_CSDDONE ; 
 int V3D_INT_FLDONE ; 
 int V3D_INT_FRDONE ; 
 int V3D_INT_GMPV ; 
 int V3D_INT_OUTOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_fence_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct v3d_fence* to_v3d_fence (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_v3d_bcl_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_v3d_csd_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_v3d_rcl_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ v3d_hub_irq (int,void*) ; 

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
		 * add more memory.  Also, as of V3D 4.1, FLDONE won't
		 * be reported until any OOM state has been cleared.
		 */
		schedule_work(&v3d->overflow_mem_work);
		status = IRQ_HANDLED;
	}

	if (intsts & V3D_INT_FLDONE) {
		struct v3d_fence *fence =
			to_v3d_fence(v3d->bin_job->base.irq_fence);

		trace_v3d_bcl_irq(&v3d->drm, fence->seqno);
		dma_fence_signal(&fence->base);
		status = IRQ_HANDLED;
	}

	if (intsts & V3D_INT_FRDONE) {
		struct v3d_fence *fence =
			to_v3d_fence(v3d->render_job->base.irq_fence);

		trace_v3d_rcl_irq(&v3d->drm, fence->seqno);
		dma_fence_signal(&fence->base);
		status = IRQ_HANDLED;
	}

	if (intsts & V3D_INT_CSDDONE) {
		struct v3d_fence *fence =
			to_v3d_fence(v3d->csd_job->base.irq_fence);

		trace_v3d_csd_irq(&v3d->drm, fence->seqno);
		dma_fence_signal(&fence->base);
		status = IRQ_HANDLED;
	}

	/* We shouldn't be triggering these if we have GMP in
	 * always-allowed mode.
	 */
	if (intsts & V3D_INT_GMPV)
		dev_err(v3d->dev, "GMP violation\n");

	/* V3D 4.2 wires the hub and core IRQs together, so if we &
	 * didn't see the common one then check hub for MMU IRQs.
	 */
	if (v3d->single_irq_line && status == IRQ_NONE)
		return v3d_hub_irq(irq, arg);

	return status;
}