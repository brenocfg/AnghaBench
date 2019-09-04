#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct vc4_dev {int /*<<< orphan*/  job_lock; int /*<<< orphan*/  overflow_mem_work; } ;
struct drm_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  V3D_INTCTL ; 
 int /*<<< orphan*/  V3D_INTDIS ; 
 int V3D_INT_FLDONE ; 
 int V3D_INT_FRDONE ; 
 int V3D_INT_OUTOMEM ; 
 int V3D_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_irq_finish_bin_job (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_irq_finish_render_job (struct drm_device*) ; 

irqreturn_t
vc4_irq(int irq, void *arg)
{
	struct drm_device *dev = arg;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	uint32_t intctl;
	irqreturn_t status = IRQ_NONE;

	barrier();
	intctl = V3D_READ(V3D_INTCTL);

	/* Acknowledge the interrupts we're handling here. The binner
	 * last flush / render frame done interrupt will be cleared,
	 * while OUTOMEM will stay high until the underlying cause is
	 * cleared.
	 */
	V3D_WRITE(V3D_INTCTL, intctl);

	if (intctl & V3D_INT_OUTOMEM) {
		/* Disable OUTOMEM until the work is done. */
		V3D_WRITE(V3D_INTDIS, V3D_INT_OUTOMEM);
		schedule_work(&vc4->overflow_mem_work);
		status = IRQ_HANDLED;
	}

	if (intctl & V3D_INT_FLDONE) {
		spin_lock(&vc4->job_lock);
		vc4_irq_finish_bin_job(dev);
		spin_unlock(&vc4->job_lock);
		status = IRQ_HANDLED;
	}

	if (intctl & V3D_INT_FRDONE) {
		spin_lock(&vc4->job_lock);
		vc4_irq_finish_render_job(dev);
		spin_unlock(&vc4->job_lock);
		status = IRQ_HANDLED;
	}

	return status;
}