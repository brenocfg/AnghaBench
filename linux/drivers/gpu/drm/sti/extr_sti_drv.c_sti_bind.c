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
struct drm_device {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int component_bind_all (int /*<<< orphan*/ ,struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
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
		goto err_cleanup;

	drm_mode_config_reset(ddev);

	drm_fbdev_generic_setup(ddev, 32);

	return 0;

err_cleanup:
	sti_cleanup(ddev);
err_drm_dev_put:
	drm_dev_put(ddev);
	return ret;
}