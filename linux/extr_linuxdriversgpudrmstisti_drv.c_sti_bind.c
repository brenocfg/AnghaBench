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
struct TYPE_2__ {scalar_t__ num_connector; } ;
struct drm_device {TYPE_1__ mode_config; int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int drm_fb_cma_fbdev_init (struct drm_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_config_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  drm_mode_config_reset (struct drm_device*) ; 
 int /*<<< orphan*/  sti_cleanup (struct drm_device*) ; 
 int /*<<< orphan*/  sti_driver ; 
 int sti_init (struct drm_device*) ; 

__attribute__((used)) static int sti_bind(struct device *dev)
{
	struct drm_device *ddev;
	int ret;

	ddev = drm_dev_alloc(&sti_driver, dev);
	if (IS_ERR(ddev))
		return PTR_ERR(ddev);

	ret = sti_init(ddev);
	if (ret)
		goto err_drm_dev_put;

	ret = component_bind_all(ddev->dev, ddev);
	if (ret)
		goto err_cleanup;

	ret = drm_dev_register(ddev, 0);
	if (ret)
		goto err_register;

	drm_mode_config_reset(ddev);

	if (ddev->mode_config.num_connector) {
		ret = drm_fb_cma_fbdev_init(ddev, 32, 0);
		if (ret)
			DRM_DEBUG_DRIVER("Warning: fails to create fbdev\n");
	}

	return 0;

err_register:
	drm_mode_config_cleanup(ddev);
err_cleanup:
	sti_cleanup(ddev);
err_drm_dev_put:
	drm_dev_put(ddev);
	return ret;
}