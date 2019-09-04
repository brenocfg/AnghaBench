#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct device_driver {int /*<<< orphan*/  (* remove ) (struct device*) ;} ;
struct device {int /*<<< orphan*/  kobj; TYPE_4__* bus; TYPE_2__* p; TYPE_1__* pm_domain; struct device_driver* driver; } ;
struct TYPE_8__ {TYPE_3__* p; int /*<<< orphan*/  (* remove ) (struct device*) ;scalar_t__ need_parent_lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  bus_notifier; } ;
struct TYPE_6__ {int /*<<< orphan*/  knode_driver; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* dismiss ) (struct device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_NOTIFY_UNBIND_DRIVER ; 
 int /*<<< orphan*/  BUS_NOTIFY_UNBOUND_DRIVER ; 
 int /*<<< orphan*/  KOBJ_UNBIND ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,int /*<<< orphan*/ *) ; 
 scalar_t__ device_links_busy (struct device*) ; 
 int /*<<< orphan*/  device_links_driver_cleanup (struct device*) ; 
 int /*<<< orphan*/  device_links_unbind_consumers (struct device*) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_pm_check_callbacks (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  devres_release_all (struct device*) ; 
 int /*<<< orphan*/  dma_deconfigure (struct device*) ; 
 int /*<<< orphan*/  driver_sysfs_remove (struct device*) ; 
 int /*<<< orphan*/  klist_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_clean_up_links (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_reinit (struct device*) ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 
 int /*<<< orphan*/  stub2 (struct device*) ; 
 int /*<<< orphan*/  stub3 (struct device*) ; 

__attribute__((used)) static void __device_release_driver(struct device *dev, struct device *parent)
{
	struct device_driver *drv;

	drv = dev->driver;
	if (drv) {
		while (device_links_busy(dev)) {
			device_unlock(dev);
			if (parent && dev->bus->need_parent_lock)
				device_unlock(parent);

			device_links_unbind_consumers(dev);
			if (parent && dev->bus->need_parent_lock)
				device_lock(parent);

			device_lock(dev);
			/*
			 * A concurrent invocation of the same function might
			 * have released the driver successfully while this one
			 * was waiting, so check for that.
			 */
			if (dev->driver != drv)
				return;
		}

		pm_runtime_get_sync(dev);
		pm_runtime_clean_up_links(dev);

		driver_sysfs_remove(dev);

		if (dev->bus)
			blocking_notifier_call_chain(&dev->bus->p->bus_notifier,
						     BUS_NOTIFY_UNBIND_DRIVER,
						     dev);

		pm_runtime_put_sync(dev);

		if (dev->bus && dev->bus->remove)
			dev->bus->remove(dev);
		else if (drv->remove)
			drv->remove(dev);

		device_links_driver_cleanup(dev);

		devres_release_all(dev);
		dma_deconfigure(dev);
		dev->driver = NULL;
		dev_set_drvdata(dev, NULL);
		if (dev->pm_domain && dev->pm_domain->dismiss)
			dev->pm_domain->dismiss(dev);
		pm_runtime_reinit(dev);
		dev_pm_set_driver_flags(dev, 0);

		klist_remove(&dev->p->knode_driver);
		device_pm_check_callbacks(dev);
		if (dev->bus)
			blocking_notifier_call_chain(&dev->bus->p->bus_notifier,
						     BUS_NOTIFY_UNBOUND_DRIVER,
						     dev);

		kobject_uevent(&dev->kobj, KOBJ_UNBIND);
	}
}