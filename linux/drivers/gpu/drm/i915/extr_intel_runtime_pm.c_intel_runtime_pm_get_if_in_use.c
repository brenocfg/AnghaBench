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
struct intel_runtime_pm {int /*<<< orphan*/  kdev; } ;
typedef  int /*<<< orphan*/  intel_wakeref_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_runtime_pm_acquire (struct intel_runtime_pm*,int) ; 
 scalar_t__ pm_runtime_get_if_in_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  track_intel_runtime_pm_wakeref (struct intel_runtime_pm*) ; 

intel_wakeref_t intel_runtime_pm_get_if_in_use(struct intel_runtime_pm *rpm)
{
	if (IS_ENABLED(CONFIG_PM)) {
		/*
		 * In cases runtime PM is disabled by the RPM core and we get
		 * an -EINVAL return value we are not supposed to call this
		 * function, since the power state is undefined. This applies
		 * atm to the late/early system suspend/resume handlers.
		 */
		if (pm_runtime_get_if_in_use(rpm->kdev) <= 0)
			return 0;
	}

	intel_runtime_pm_acquire(rpm, true);

	return track_intel_runtime_pm_wakeref(rpm);
}