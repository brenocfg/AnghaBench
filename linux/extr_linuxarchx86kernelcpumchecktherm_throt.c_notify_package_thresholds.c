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
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  PACKAGE_LEVEL ; 
 int THERM_LOG_THRESHOLD0 ; 
 int THERM_LOG_THRESHOLD1 ; 
 int /*<<< orphan*/  platform_thermal_package_notify (int) ; 
 scalar_t__ platform_thermal_package_rate_control () ; 
 scalar_t__ thresh_event_valid (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void notify_package_thresholds(__u64 msr_val)
{
	bool notify_thres_0 = false;
	bool notify_thres_1 = false;

	if (!platform_thermal_package_notify)
		return;

	/* lower threshold check */
	if (msr_val & THERM_LOG_THRESHOLD0)
		notify_thres_0 = true;
	/* higher threshold check */
	if (msr_val & THERM_LOG_THRESHOLD1)
		notify_thres_1 = true;

	if (!notify_thres_0 && !notify_thres_1)
		return;

	if (platform_thermal_package_rate_control &&
		platform_thermal_package_rate_control()) {
		/* Rate control is implemented in callback */
		platform_thermal_package_notify(msr_val);
		return;
	}

	/* lower threshold reached */
	if (notify_thres_0 && thresh_event_valid(PACKAGE_LEVEL, 0))
		platform_thermal_package_notify(msr_val);
	/* higher threshold reached */
	if (notify_thres_1 && thresh_event_valid(PACKAGE_LEVEL, 1))
		platform_thermal_package_notify(msr_val);
}