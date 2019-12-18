#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc4_dev {int /*<<< orphan*/  power_lock; TYPE_2__* v3d; scalar_t__ power_refcount; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync_suspend (int /*<<< orphan*/ *) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_irq_reset (struct drm_device*) ; 
 int /*<<< orphan*/  vc4_queue_hangcheck (struct drm_device*) ; 

__attribute__((used)) static void
vc4_reset(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	DRM_INFO("Resetting GPU.\n");

	mutex_lock(&vc4->power_lock);
	if (vc4->power_refcount) {
		/* Power the device off and back on the by dropping the
		 * reference on runtime PM.
		 */
		pm_runtime_put_sync_suspend(&vc4->v3d->pdev->dev);
		pm_runtime_get_sync(&vc4->v3d->pdev->dev);
	}
	mutex_unlock(&vc4->power_lock);

	vc4_irq_reset(dev);

	/* Rearm the hangcheck -- another job might have been waiting
	 * for our hung one to get kicked off, and vc4_irq_reset()
	 * would have started it.
	 */
	vc4_queue_hangcheck(dev);
}