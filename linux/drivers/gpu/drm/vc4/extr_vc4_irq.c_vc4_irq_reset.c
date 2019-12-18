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
struct vc4_dev {int /*<<< orphan*/  job_lock; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_DRIVER_IRQS ; 
 int /*<<< orphan*/  V3D_INTCTL ; 
 int /*<<< orphan*/  V3D_INTENA ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_cancel_bin_job (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_irq_finish_render_job (struct drm_device*) ; 

void vc4_irq_reset(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	unsigned long irqflags;

	/* Acknowledge any stale IRQs. */
	V3D_WRITE(V3D_INTCTL, V3D_DRIVER_IRQS);

	/*
	 * Turn all our interrupts on.  Binner out of memory is the
	 * only one we expect to trigger at this point, since we've
	 * just come from poweron and haven't supplied any overflow
	 * memory yet.
	 */
	V3D_WRITE(V3D_INTENA, V3D_DRIVER_IRQS);

	spin_lock_irqsave(&vc4->job_lock, irqflags);
	vc4_cancel_bin_job(dev);
	vc4_irq_finish_render_job(dev);
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);
}