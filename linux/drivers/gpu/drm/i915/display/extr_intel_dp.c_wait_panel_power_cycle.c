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
struct intel_dp {scalar_t__ panel_power_cycle_delay; int /*<<< orphan*/  panel_power_off_time; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  IDLE_CYCLE_MASK ; 
 int /*<<< orphan*/  IDLE_CYCLE_VALUE ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  ktime_get_boottime () ; 
 scalar_t__ ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_panel_status (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_remaining_ms_from_jiffies (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void wait_panel_power_cycle(struct intel_dp *intel_dp)
{
	ktime_t panel_power_on_time;
	s64 panel_power_off_duration;

	DRM_DEBUG_KMS("Wait for panel power cycle\n");

	/* take the difference of currrent time and panel power off time
	 * and then make panel wait for t11_t12 if needed. */
	panel_power_on_time = ktime_get_boottime();
	panel_power_off_duration = ktime_ms_delta(panel_power_on_time, intel_dp->panel_power_off_time);

	/* When we disable the VDD override bit last we have to do the manual
	 * wait. */
	if (panel_power_off_duration < (s64)intel_dp->panel_power_cycle_delay)
		wait_remaining_ms_from_jiffies(jiffies,
				       intel_dp->panel_power_cycle_delay - panel_power_off_duration);

	wait_panel_status(intel_dp, IDLE_CYCLE_MASK, IDLE_CYCLE_VALUE);
}