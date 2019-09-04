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
struct fsl_dcu_drm_device {scalar_t__ fbdev; } ;
struct drm_device {struct fsl_dcu_drm_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_fbdev_cma_fini (scalar_t__) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 

__attribute__((used)) static void fsl_dcu_unload(struct drm_device *dev)
{
	struct fsl_dcu_drm_device *fsl_dev = dev->dev_private;

	drm_atomic_helper_shutdown(dev);
	drm_kms_helper_poll_fini(dev);

	if (fsl_dev->fbdev)
		drm_fbdev_cma_fini(fsl_dev->fbdev);

	drm_mode_config_cleanup(dev);
	drm_irq_uninstall(dev);

	dev->dev_private = NULL;
}