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
struct intel_runtime_pm {int /*<<< orphan*/  available; struct device* kdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPM_FLAG_NEVER_SKIP ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  dev_pm_set_driver_flags (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 

void intel_runtime_pm_enable(struct intel_runtime_pm *rpm)
{
	struct device *kdev = rpm->kdev;

	/*
	 * Disable the system suspend direct complete optimization, which can
	 * leave the device suspended skipping the driver's suspend handlers
	 * if the device was already runtime suspended. This is needed due to
	 * the difference in our runtime and system suspend sequence and
	 * becaue the HDA driver may require us to enable the audio power
	 * domain during system suspend.
	 */
	dev_pm_set_driver_flags(kdev, DPM_FLAG_NEVER_SKIP);

	pm_runtime_set_autosuspend_delay(kdev, 10000); /* 10s */
	pm_runtime_mark_last_busy(kdev);

	/*
	 * Take a permanent reference to disable the RPM functionality and drop
	 * it only when unloading the driver. Use the low level get/put helpers,
	 * so the driver's own RPM reference tracking asserts also work on
	 * platforms without RPM support.
	 */
	if (!rpm->available) {
		int ret;

		pm_runtime_dont_use_autosuspend(kdev);
		ret = pm_runtime_get_sync(kdev);
		WARN(ret < 0, "pm_runtime_get_sync() failed: %d\n", ret);
	} else {
		pm_runtime_use_autosuspend(kdev);
	}

	/*
	 * The core calls the driver load handler with an RPM reference held.
	 * We drop that here and will reacquire it during unloading in
	 * intel_power_domains_fini().
	 */
	pm_runtime_put_autosuspend(kdev);
}