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
struct omap_drm_private {int /*<<< orphan*/  wq; struct drm_device* ddev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_atomic_helper_shutdown (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  omap_crtc_pre_uninit (struct omap_drm_private*) ; 
 int /*<<< orphan*/  omap_disconnect_pipelines (struct drm_device*) ; 
 int /*<<< orphan*/  omap_drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  omap_fbdev_fini (struct drm_device*) ; 
 int /*<<< orphan*/  omap_gem_deinit (struct drm_device*) ; 
 int /*<<< orphan*/  omap_modeset_disable_external_hpd (struct drm_device*) ; 

__attribute__((used)) static void omapdrm_cleanup(struct omap_drm_private *priv)
{
	struct drm_device *ddev = priv->ddev;

	DBG("");

	drm_dev_unregister(ddev);

	omap_modeset_disable_external_hpd(ddev);
	drm_kms_helper_poll_fini(ddev);

	omap_fbdev_fini(ddev);

	drm_atomic_helper_shutdown(ddev);

	drm_mode_config_cleanup(ddev);

	omap_drm_irq_uninstall(ddev);
	omap_gem_deinit(ddev);

	destroy_workqueue(priv->wq);

	omap_disconnect_pipelines(ddev);
	omap_crtc_pre_uninit(priv);

	drm_dev_put(ddev);
}