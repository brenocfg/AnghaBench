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
struct intel_dp {void* last_backlight_off; void* last_power_on; int /*<<< orphan*/  panel_power_off_time; } ;

/* Variables and functions */
 void* jiffies ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 

__attribute__((used)) static void intel_dp_init_panel_power_timestamps(struct intel_dp *intel_dp)
{
	intel_dp->panel_power_off_time = ktime_get_boottime();
	intel_dp->last_power_on = jiffies;
	intel_dp->last_backlight_off = jiffies;
}