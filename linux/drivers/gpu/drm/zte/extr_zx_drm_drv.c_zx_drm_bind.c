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
struct TYPE_2__ {int min_width; int min_height; int max_width; int max_height; int /*<<< orphan*/  num_crtc; int /*<<< orphan*/ * funcs; } ;
struct drm_device {int irq_enabled; TYPE_1__ mode_config; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (struct device*,struct drm_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_fini (struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx_drm_driver ; 
 int /*<<< orphan*/  zx_drm_mode_config_funcs ; 

__attribute__((used)) static int zx_drm_bind(struct device *dev)
{
	struct drm_device *drm;
	int ret;

	drm = drm_dev_alloc(&zx_drm_driver, dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	dev_set_drvdata(dev, drm);

	drm_mode_config_init(drm);
	drm->mode_config.min_width = 16;
	drm->mode_config.min_height = 16;
	drm->mode_config.max_width = 4096;
	drm->mode_config.max_height = 4096;
	drm->mode_config.funcs = &zx_drm_mode_config_funcs;

	ret = component_bind_all(dev, drm);
	if (ret) {
		DRM_DEV_ERROR(dev, "failed to bind all components: %d\n", ret);
		goto out_unregister;
	}

	ret = drm_vblank_init(drm, drm->mode_config.num_crtc);
	if (ret < 0) {
		DRM_DEV_ERROR(dev, "failed to init vblank: %d\n", ret);
		goto out_unbind;
	}

	/*
	 * We will manage irq handler on our own.  In this case, irq_enabled
	 * need to be true for using vblank core support.
	 */
	drm->irq_enabled = true;

	drm_mode_config_reset(drm);
	drm_kms_helper_poll_init(drm);

	ret = drm_dev_register(drm, 0);
	if (ret)
		goto out_poll_fini;

	drm_fbdev_generic_setup(drm, 32);

	return 0;

out_poll_fini:
	drm_kms_helper_poll_fini(drm);
	drm_mode_config_cleanup(drm);
out_unbind:
	component_unbind_all(dev, drm);
out_unregister:
	dev_set_drvdata(dev, NULL);
	drm_dev_put(drm);
	return ret;
}