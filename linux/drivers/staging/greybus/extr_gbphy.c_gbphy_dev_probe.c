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
struct gbphy_driver {int (* probe ) (struct gbphy_device*,struct gbphy_device_id const*) ;} ;
struct gbphy_device_id {int dummy; } ;
struct gbphy_device {int /*<<< orphan*/  bundle; } ;
struct device {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GB_GBPHY_AUTOSUSPEND_MS ; 
 int gb_pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 struct gbphy_device_id* gbphy_dev_match_id (struct gbphy_device*,struct gbphy_driver*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int stub1 (struct gbphy_device*,struct gbphy_device_id const*) ; 
 struct gbphy_device* to_gbphy_dev (struct device*) ; 
 struct gbphy_driver* to_gbphy_driver (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gbphy_dev_probe(struct device *dev)
{
	struct gbphy_driver *gbphy_drv = to_gbphy_driver(dev->driver);
	struct gbphy_device *gbphy_dev = to_gbphy_dev(dev);
	const struct gbphy_device_id *id;
	int ret;

	id = gbphy_dev_match_id(gbphy_dev, gbphy_drv);
	if (!id)
		return -ENODEV;

	/* for old kernels we need get_sync to resume parent devices */
	ret = gb_pm_runtime_get_sync(gbphy_dev->bundle);
	if (ret < 0)
		return ret;

	pm_runtime_set_autosuspend_delay(dev, GB_GBPHY_AUTOSUSPEND_MS);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_get_noresume(dev);
	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);

	/*
	 * Drivers should call put on the gbphy dev before returning
	 * from probe if they support runtime pm.
	 */
	ret = gbphy_drv->probe(gbphy_dev, id);
	if (ret) {
		pm_runtime_disable(dev);
		pm_runtime_set_suspended(dev);
		pm_runtime_put_noidle(dev);
		pm_runtime_dont_use_autosuspend(dev);
	}

	gb_pm_runtime_put_autosuspend(gbphy_dev->bundle);

	return ret;
}