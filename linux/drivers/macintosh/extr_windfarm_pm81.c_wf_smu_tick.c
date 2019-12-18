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

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 unsigned int FAILURE_OVERTEMP ; 
 scalar_t__ cpufreq_clamp ; 
 scalar_t__ fan_cpu_main ; 
 scalar_t__ fan_hd ; 
 scalar_t__ fan_system ; 
 int /*<<< orphan*/  wf_clear_overtemp () ; 
 int /*<<< orphan*/  wf_control_set_max (scalar_t__) ; 
 int /*<<< orphan*/  wf_control_set_min (scalar_t__) ; 
 int /*<<< orphan*/  wf_set_overtemp () ; 
 scalar_t__ wf_smu_cpu_fans ; 
 int /*<<< orphan*/  wf_smu_cpu_fans_tick (scalar_t__) ; 
 int /*<<< orphan*/  wf_smu_create_cpu_fans () ; 
 int /*<<< orphan*/  wf_smu_create_sys_fans () ; 
 unsigned int wf_smu_failure_state ; 
 int wf_smu_overtemp ; 
 int wf_smu_readjust ; 
 int wf_smu_skipping ; 
 int wf_smu_started ; 
 scalar_t__ wf_smu_sys_fans ; 
 int /*<<< orphan*/  wf_smu_sys_fans_tick (scalar_t__) ; 

__attribute__((used)) static void wf_smu_tick(void)
{
	unsigned int last_failure = wf_smu_failure_state;
	unsigned int new_failure;

	if (!wf_smu_started) {
		DBG("wf: creating control loops !\n");
		wf_smu_create_sys_fans();
		wf_smu_create_cpu_fans();
		wf_smu_started = true;
	}

	/* Skipping ticks */
	if (wf_smu_skipping && --wf_smu_skipping)
		return;

	wf_smu_failure_state = 0;
	if (wf_smu_sys_fans)
		wf_smu_sys_fans_tick(wf_smu_sys_fans);
	if (wf_smu_cpu_fans)
		wf_smu_cpu_fans_tick(wf_smu_cpu_fans);

	wf_smu_readjust = 0;
	new_failure = wf_smu_failure_state & ~last_failure;

	/* If entering failure mode, clamp cpufreq and ramp all
	 * fans to full speed.
	 */
	if (wf_smu_failure_state && !last_failure) {
		if (cpufreq_clamp)
			wf_control_set_max(cpufreq_clamp);
		if (fan_system)
			wf_control_set_max(fan_system);
		if (fan_cpu_main)
			wf_control_set_max(fan_cpu_main);
		if (fan_hd)
			wf_control_set_max(fan_hd);
	}

	/* If leaving failure mode, unclamp cpufreq and readjust
	 * all fans on next iteration
	 */
	if (!wf_smu_failure_state && last_failure) {
		if (cpufreq_clamp)
			wf_control_set_min(cpufreq_clamp);
		wf_smu_readjust = 1;
	}

	/* Overtemp condition detected, notify and start skipping a couple
	 * ticks to let the temperature go down
	 */
	if (new_failure & FAILURE_OVERTEMP) {
		wf_set_overtemp();
		wf_smu_skipping = 2;
		wf_smu_overtemp = true;
	}

	/* We only clear the overtemp condition if overtemp is cleared
	 * _and_ no other failure is present. Since a sensor error will
	 * clear the overtemp condition (can't measure temperature) at
	 * the control loop levels, but we don't want to keep it clear
	 * here in this case
	 */
	if (!wf_smu_failure_state && wf_smu_overtemp) {
		wf_clear_overtemp();
		wf_smu_overtemp = false;
	}
}