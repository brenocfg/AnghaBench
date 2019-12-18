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
struct vc4_dev {int /*<<< orphan*/  overflow_mem_work; int /*<<< orphan*/  v3d; } ;
struct drm_device {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_DRIVER_IRQS ; 
 int /*<<< orphan*/  V3D_INTCTL ; 
 int /*<<< orphan*/  V3D_INTDIS ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

void
vc4_irq_uninstall(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	if (!vc4->v3d)
		return;

	/* Disable sending interrupts for our driver's IRQs. */
	V3D_WRITE(V3D_INTDIS, V3D_DRIVER_IRQS);

	/* Clear any pending interrupts we might have left. */
	V3D_WRITE(V3D_INTCTL, V3D_DRIVER_IRQS);

	/* Finish any interrupt handler still in flight. */
	disable_irq(dev->irq);

	cancel_work_sync(&vc4->overflow_mem_work);
}