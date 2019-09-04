#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int is_late_suspended; int /*<<< orphan*/  completion; scalar_t__ direct_complete; scalar_t__ syscore; } ;
struct device {TYPE_2__ power; TYPE_1__* driver; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
typedef  scalar_t__ pm_callback_t ;
struct TYPE_3__ {scalar_t__ pm; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  TRACE_DEVICE (struct device*) ; 
 int /*<<< orphan*/  TRACE_SUSPEND (int) ; 
 int /*<<< orphan*/  __pm_runtime_disable (struct device*,int) ; 
 int async_error ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 scalar_t__ dev_pm_smart_suspend_and_suspended (struct device*) ; 
 int /*<<< orphan*/  dpm_propagate_wakeup_to_parent (struct device*) ; 
 int dpm_run_callback (scalar_t__,struct device*,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ dpm_subsys_suspend_late_cb (struct device*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  dpm_subsys_suspend_noirq_cb (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dpm_wait_for_subordinate (struct device*,int) ; 
 scalar_t__ pm_late_early_op (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pm_wakeup_pending () ; 

__attribute__((used)) static int __device_suspend_late(struct device *dev, pm_message_t state, bool async)
{
	pm_callback_t callback;
	const char *info;
	int error = 0;

	TRACE_DEVICE(dev);
	TRACE_SUSPEND(0);

	__pm_runtime_disable(dev, false);

	dpm_wait_for_subordinate(dev, async);

	if (async_error)
		goto Complete;

	if (pm_wakeup_pending()) {
		async_error = -EBUSY;
		goto Complete;
	}

	if (dev->power.syscore || dev->power.direct_complete)
		goto Complete;

	callback = dpm_subsys_suspend_late_cb(dev, state, &info);
	if (callback)
		goto Run;

	if (dev_pm_smart_suspend_and_suspended(dev) &&
	    !dpm_subsys_suspend_noirq_cb(dev, state, NULL))
		goto Skip;

	if (dev->driver && dev->driver->pm) {
		info = "late driver ";
		callback = pm_late_early_op(dev->driver->pm, state);
	}

Run:
	error = dpm_run_callback(callback, dev, state, info);
	if (error) {
		async_error = error;
		goto Complete;
	}
	dpm_propagate_wakeup_to_parent(dev);

Skip:
	dev->power.is_late_suspended = true;

Complete:
	TRACE_SUSPEND(error);
	complete_all(&dev->power.completion);
	return error;
}