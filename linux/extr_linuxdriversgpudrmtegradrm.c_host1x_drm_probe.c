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
struct host1x_device {int /*<<< orphan*/  dev; } ;
struct drm_driver {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_device*) ; 
 int PTR_ERR (struct drm_device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct drm_device*) ; 
 struct drm_device* drm_dev_alloc (struct drm_driver*,int /*<<< orphan*/ *) ; 
 int drm_dev_register (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_unref (struct drm_device*) ; 
 struct drm_driver tegra_drm_driver ; 

__attribute__((used)) static int host1x_drm_probe(struct host1x_device *dev)
{
	struct drm_driver *driver = &tegra_drm_driver;
	struct drm_device *drm;
	int err;

	drm = drm_dev_alloc(driver, &dev->dev);
	if (IS_ERR(drm))
		return PTR_ERR(drm);

	dev_set_drvdata(&dev->dev, drm);

	err = drm_dev_register(drm, 0);
	if (err < 0)
		goto unref;

	return 0;

unref:
	drm_dev_unref(drm);
	return err;
}