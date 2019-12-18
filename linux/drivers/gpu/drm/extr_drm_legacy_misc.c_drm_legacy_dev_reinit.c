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
struct TYPE_2__ {int /*<<< orphan*/ * lock; } ;
struct drm_device {scalar_t__ if_version; scalar_t__ last_context; scalar_t__ context_flag; TYPE_1__ sigdata; int /*<<< orphan*/  struct_mutex; scalar_t__ irq_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_agp_clear (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_dma_takedown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_sg_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_vma_flush (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_legacy_dev_reinit(struct drm_device *dev)
{
	if (dev->irq_enabled)
		drm_irq_uninstall(dev);

	mutex_lock(&dev->struct_mutex);

	drm_legacy_agp_clear(dev);

	drm_legacy_sg_cleanup(dev);
	drm_legacy_vma_flush(dev);
	drm_legacy_dma_takedown(dev);

	mutex_unlock(&dev->struct_mutex);

	dev->sigdata.lock = NULL;

	dev->context_flag = 0;
	dev->last_context = 0;
	dev->if_version = 0;

	DRM_DEBUG("lastclose completed\n");
}