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
struct kirin_drm_data {scalar_t__ register_connects; int /*<<< orphan*/  driver; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  drm_dev_put (struct drm_device*) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_unregister (struct drm_device*) ; 
 int /*<<< orphan*/  drm_fbdev_generic_setup (struct drm_device*,int) ; 
 int kirin_drm_connectors_register (struct drm_device*) ; 
 int /*<<< orphan*/  kirin_drm_kms_cleanup (struct drm_device*) ; 
 int kirin_drm_kms_init (struct drm_device*,struct kirin_drm_data*) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 

__attribute__((used)) static int kirin_drm_bind(struct device *dev)
{
	struct kirin_drm_data *driver_data;
	struct drm_device *drm_dev;
	int ret;

	driver_data = (struct kirin_drm_data *)of_device_get_match_data(dev);
	if (!driver_data)
		return -EINVAL;

	drm_dev = drm_dev_alloc(driver_data->driver, dev);
	if (IS_ERR(drm_dev))
		return PTR_ERR(drm_dev);
	dev_set_drvdata(dev, drm_dev);

	/* display controller init */
	ret = kirin_drm_kms_init(drm_dev, driver_data);
	if (ret)
		goto err_drm_dev_put;

	ret = drm_dev_register(drm_dev, 0);
	if (ret)
		goto err_kms_cleanup;

	drm_fbdev_generic_setup(drm_dev, 32);

	/* connectors should be registered after drm device register */
	if (driver_data->register_connects) {
		ret = kirin_drm_connectors_register(drm_dev);
		if (ret)
			goto err_drm_dev_unregister;
	}

	return 0;

err_drm_dev_unregister:
	drm_dev_unregister(drm_dev);
err_kms_cleanup:
	kirin_drm_kms_cleanup(drm_dev);
err_drm_dev_put:
	drm_dev_put(drm_dev);

	return ret;
}