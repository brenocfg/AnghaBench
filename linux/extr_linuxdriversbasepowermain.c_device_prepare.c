#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int wakeup_path; int direct_complete; int /*<<< orphan*/  lock; scalar_t__ no_pm_callbacks; scalar_t__ syscore; } ;
struct device {TYPE_11__ power; TYPE_10__* driver; TYPE_8__* bus; TYPE_6__* class; TYPE_4__* type; TYPE_2__* pm_domain; } ;
struct TYPE_16__ {scalar_t__ event; } ;
typedef  TYPE_12__ pm_message_t ;
struct TYPE_25__ {int (* prepare ) (struct device*) ;} ;
struct TYPE_24__ {TYPE_7__* pm; } ;
struct TYPE_23__ {int (* prepare ) (struct device*) ;} ;
struct TYPE_22__ {TYPE_5__* pm; } ;
struct TYPE_21__ {int (* prepare ) (struct device*) ;} ;
struct TYPE_20__ {TYPE_3__* pm; } ;
struct TYPE_19__ {int (* prepare ) (struct device*) ;} ;
struct TYPE_17__ {int (* prepare ) (struct device*) ;} ;
struct TYPE_18__ {TYPE_1__ ops; } ;
struct TYPE_14__ {TYPE_9__* pm; } ;

/* Variables and functions */
 int DPM_FLAG_LEAVE_SUSPENDED ; 
 int DPM_FLAG_NEVER_SKIP ; 
 int DPM_FLAG_SMART_SUSPEND ; 
 scalar_t__ PM_EVENT_SUSPEND ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ dev_pm_test_driver_flags (struct device*,int) ; 
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enabled (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 
 scalar_t__ pm_runtime_suspended (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  suspend_report_result (int (*) (struct device*),int) ; 

__attribute__((used)) static int device_prepare(struct device *dev, pm_message_t state)
{
	int (*callback)(struct device *) = NULL;
	int ret = 0;

	if (dev->power.syscore)
		return 0;

	WARN_ON(!pm_runtime_enabled(dev) &&
		dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND |
					      DPM_FLAG_LEAVE_SUSPENDED));

	/*
	 * If a device's parent goes into runtime suspend at the wrong time,
	 * it won't be possible to resume the device.  To prevent this we
	 * block runtime suspend here, during the prepare phase, and allow
	 * it again during the complete phase.
	 */
	pm_runtime_get_noresume(dev);

	device_lock(dev);

	dev->power.wakeup_path = false;

	if (dev->power.no_pm_callbacks)
		goto unlock;

	if (dev->pm_domain)
		callback = dev->pm_domain->ops.prepare;
	else if (dev->type && dev->type->pm)
		callback = dev->type->pm->prepare;
	else if (dev->class && dev->class->pm)
		callback = dev->class->pm->prepare;
	else if (dev->bus && dev->bus->pm)
		callback = dev->bus->pm->prepare;

	if (!callback && dev->driver && dev->driver->pm)
		callback = dev->driver->pm->prepare;

	if (callback)
		ret = callback(dev);

unlock:
	device_unlock(dev);

	if (ret < 0) {
		suspend_report_result(callback, ret);
		pm_runtime_put(dev);
		return ret;
	}
	/*
	 * A positive return value from ->prepare() means "this device appears
	 * to be runtime-suspended and its state is fine, so if it really is
	 * runtime-suspended, you can leave it in that state provided that you
	 * will do the same thing with all of its descendants".  This only
	 * applies to suspend transitions, however.
	 */
	spin_lock_irq(&dev->power.lock);
	dev->power.direct_complete = state.event == PM_EVENT_SUSPEND &&
		((pm_runtime_suspended(dev) && ret > 0) ||
		 dev->power.no_pm_callbacks) &&
		!dev_pm_test_driver_flags(dev, DPM_FLAG_NEVER_SKIP);
	spin_unlock_irq(&dev->power.lock);
	return 0;
}