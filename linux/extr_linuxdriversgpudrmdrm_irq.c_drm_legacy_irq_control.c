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
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  struct_mutex; int /*<<< orphan*/  if_version; TYPE_1__* pdev; } ;
struct drm_control {int func; int irq; } ;
struct TYPE_2__ {int irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_HAVE_IRQ ; 
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int /*<<< orphan*/  DRM_IF_VERSION (int,int) ; 
#define  DRM_INST_HANDLER 129 
#define  DRM_UNINST_HANDLER 128 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_irq_install (struct drm_device*,int) ; 
 int drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int drm_legacy_irq_control(struct drm_device *dev, void *data,
			   struct drm_file *file_priv)
{
	struct drm_control *ctl = data;
	int ret = 0, irq;

	/* if we haven't irq we fallback for compatibility reasons -
	 * this used to be a separate function in drm_dma.h
	 */

	if (!drm_core_check_feature(dev, DRIVER_HAVE_IRQ))
		return 0;
	if (!drm_core_check_feature(dev, DRIVER_LEGACY))
		return 0;
	/* UMS was only ever supported on pci devices. */
	if (WARN_ON(!dev->pdev))
		return -EINVAL;

	switch (ctl->func) {
	case DRM_INST_HANDLER:
		irq = dev->pdev->irq;

		if (dev->if_version < DRM_IF_VERSION(1, 2) &&
		    ctl->irq != irq)
			return -EINVAL;
		mutex_lock(&dev->struct_mutex);
		ret = drm_irq_install(dev, irq);
		mutex_unlock(&dev->struct_mutex);

		return ret;
	case DRM_UNINST_HANDLER:
		mutex_lock(&dev->struct_mutex);
		ret = drm_irq_uninstall(dev);
		mutex_unlock(&dev->struct_mutex);

		return ret;
	default:
		return -EINVAL;
	}
}