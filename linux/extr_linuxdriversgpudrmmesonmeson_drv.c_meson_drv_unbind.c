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
struct meson_drm {int /*<<< orphan*/  fbdev; } ;
struct drm_device {struct meson_drm* dev_private; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct drm_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_fbdev_cma_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 

__attribute__((used)) static void meson_drv_unbind(struct device *dev)
{
	struct drm_device *drm = dev_get_drvdata(dev);
	struct meson_drm *priv = drm->dev_private;

	drm_dev_unregister(drm);
	drm_kms_helper_poll_fini(drm);
	drm_fbdev_cma_fini(priv->fbdev);
	drm_mode_config_cleanup(drm);
	drm_dev_put(drm);

}