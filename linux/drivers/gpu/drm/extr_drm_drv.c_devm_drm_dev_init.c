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
struct drm_driver {int /*<<< orphan*/  release; } ;
struct drm_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int devm_add_action (struct device*,int /*<<< orphan*/  (*) (struct drm_device*),struct drm_device*) ; 
 int /*<<< orphan*/  devm_drm_dev_init_release (struct drm_device*) ; 
 int drm_dev_init (struct drm_device*,struct drm_driver*,struct device*) ; 

int devm_drm_dev_init(struct device *parent,
		      struct drm_device *dev,
		      struct drm_driver *driver)
{
	int ret;

	if (WARN_ON(!parent || !driver->release))
		return -EINVAL;

	ret = drm_dev_init(dev, driver, parent);
	if (ret)
		return ret;

	ret = devm_add_action(parent, devm_drm_dev_init_release, dev);
	if (ret)
		devm_drm_dev_init_release(dev);

	return ret;
}