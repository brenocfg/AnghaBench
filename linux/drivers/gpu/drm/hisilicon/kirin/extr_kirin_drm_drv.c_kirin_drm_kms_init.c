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
struct kirin_drm_data {int /*<<< orphan*/  mode_config_funcs; int /*<<< orphan*/  config_max_width; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_crtc; int /*<<< orphan*/  funcs; int /*<<< orphan*/  max_height; int /*<<< orphan*/  max_width; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {int irq_enabled; int /*<<< orphan*/  dev; TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int component_bind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  component_unbind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 int /*<<< orphan*/  drm_kms_helper_poll_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_init (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int drm_vblank_init (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kirin_drm_private_cleanup (struct drm_device*) ; 
 int kirin_drm_private_init (struct drm_device*,struct kirin_drm_data const*) ; 

__attribute__((used)) static int kirin_drm_kms_init(struct drm_device *dev,
			      const struct kirin_drm_data *driver_data)
{
	int ret;

	/* dev->mode_config initialization */
	drm_mode_config_init(dev);
	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = driver_data->config_max_width;
	dev->mode_config.max_height = driver_data->config_max_width;
	dev->mode_config.funcs = driver_data->mode_config_funcs;

	/* display controller init */
	ret = kirin_drm_private_init(dev, driver_data);
	if (ret)
		goto err_mode_config_cleanup;

	/* bind and init sub drivers */
	ret = component_bind_all(dev->dev, dev);
	if (ret) {
		DRM_ERROR("failed to bind all component.\n");
		goto err_private_cleanup;
	}

	/* vblank init */
	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	if (ret) {
		DRM_ERROR("failed to initialize vblank.\n");
		goto err_unbind_all;
	}
	/* with irq_enabled = true, we can use the vblank feature. */
	dev->irq_enabled = true;

	/* reset all the states of crtc/plane/encoder/connector */
	drm_mode_config_reset(dev);

	/* init kms poll for handling hpd */
	drm_kms_helper_poll_init(dev);

	return 0;

err_unbind_all:
	component_unbind_all(dev->dev, dev);
err_private_cleanup:
	kirin_drm_private_cleanup(dev);
err_mode_config_cleanup:
	drm_mode_config_cleanup(dev);
	return ret;
}