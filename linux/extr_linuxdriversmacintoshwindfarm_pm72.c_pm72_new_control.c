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
 struct wf_control* backside_fan ; 
 struct wf_control** cpu_front_fans ; 
 int cpu_pid_combined ; 
 struct wf_control** cpu_pumps ; 
 struct wf_control** cpu_rear_fans ; 
 struct wf_control* cpufreq_clamp ; 
 struct wf_control* drives_fan ; 
 int have_all_controls ; 
 int nr_chips ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 struct wf_control* slots_fan ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void pm72_new_control(struct wf_control *ct)
{
	bool all_controls;
	bool had_pump = cpu_pumps[0] || cpu_pumps[1];

	if (!strcmp(ct->name, "cpu-front-fan-0"))
		cpu_front_fans[0] = ct;
	else if (!strcmp(ct->name, "cpu-front-fan-1"))
		cpu_front_fans[1] = ct;
	else if (!strcmp(ct->name, "cpu-rear-fan-0"))
		cpu_rear_fans[0] = ct;
	else if (!strcmp(ct->name, "cpu-rear-fan-1"))
		cpu_rear_fans[1] = ct;
	else if (!strcmp(ct->name, "cpu-pump-0"))
		cpu_pumps[0] = ct;
	else if (!strcmp(ct->name, "cpu-pump-1"))
		cpu_pumps[1] = ct;
	else if (!strcmp(ct->name, "backside-fan"))
		backside_fan = ct;
	else if (!strcmp(ct->name, "slots-fan"))
		slots_fan = ct;
	else if (!strcmp(ct->name, "drive-bay-fan"))
		drives_fan = ct;
	else if (!strcmp(ct->name, "cpufreq-clamp"))
		cpufreq_clamp = ct;

	all_controls =
		cpu_front_fans[0] &&
		cpu_rear_fans[0] &&
		backside_fan &&
		slots_fan &&
		drives_fan;
	if (nr_chips > 1)
		all_controls &=
			cpu_front_fans[1] &&
			cpu_rear_fans[1];
	have_all_controls = all_controls;

	if ((cpu_pumps[0] || cpu_pumps[1]) && !had_pump) {
		pr_info("wf_pm72: Liquid cooling pump(s) detected,"
			" using new algorithm !\n");
		cpu_pid_combined = true;
	}
}