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
struct wf_control {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct wf_control* cpufreq_clamp ; 
 struct wf_control* fan_cpu_main ; 
 struct wf_control* fan_cpu_second ; 
 struct wf_control* fan_cpu_third ; 
 struct wf_control* fan_hd ; 
 struct wf_control* fan_slots ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wf_get_control (struct wf_control*) ; 
 int wf_smu_all_controls_ok ; 

__attribute__((used)) static void wf_smu_new_control(struct wf_control *ct)
{
	if (wf_smu_all_controls_ok)
		return;

	if (fan_cpu_main == NULL && !strcmp(ct->name, "cpu-rear-fan-0")) {
		if (wf_get_control(ct) == 0)
			fan_cpu_main = ct;
	}

	if (fan_cpu_second == NULL && !strcmp(ct->name, "cpu-rear-fan-1")) {
		if (wf_get_control(ct) == 0)
			fan_cpu_second = ct;
	}

	if (fan_cpu_third == NULL && !strcmp(ct->name, "cpu-front-fan-0")) {
		if (wf_get_control(ct) == 0)
			fan_cpu_third = ct;
	}

	if (cpufreq_clamp == NULL && !strcmp(ct->name, "cpufreq-clamp")) {
		if (wf_get_control(ct) == 0)
			cpufreq_clamp = ct;
	}

	if (fan_hd == NULL && !strcmp(ct->name, "drive-bay-fan")) {
		if (wf_get_control(ct) == 0)
			fan_hd = ct;
	}

	if (fan_slots == NULL && !strcmp(ct->name, "slots-fan")) {
		if (wf_get_control(ct) == 0)
			fan_slots = ct;
	}

	if (fan_cpu_main && (fan_cpu_second || fan_cpu_third) && fan_hd &&
	    fan_slots && cpufreq_clamp)
		wf_smu_all_controls_ok = 1;
}