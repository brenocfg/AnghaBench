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
struct vc4_dev {int /*<<< orphan*/  overflow_mem_work; int /*<<< orphan*/  job_wait_queue; int /*<<< orphan*/  v3d; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_DRIVER_IRQS ; 
 int /*<<< orphan*/  V3D_INTCTL ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_overflow_mem_work ; 

void
vc4_irq_preinstall(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	if (!vc4->v3d)
		return;

	init_waitqueue_head(&vc4->job_wait_queue);
	INIT_WORK(&vc4->overflow_mem_work, vc4_overflow_mem_work);

	/* Clear any pending interrupts someone might have left around
	 * for us.
	 */
	V3D_WRITE(V3D_INTCTL, V3D_DRIVER_IRQS);
}