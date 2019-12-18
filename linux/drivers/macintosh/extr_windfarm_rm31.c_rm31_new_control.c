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
 struct wf_control*** cpu_fans ; 
 struct wf_control* cpufreq_clamp ; 
 int have_all_controls ; 
 int nr_chips ; 
 struct wf_control* slots_fan ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void rm31_new_control(struct wf_control *ct)
{
	bool all_controls;

	if (!strcmp(ct->name, "cpu-fan-a-0"))
		cpu_fans[0][0] = ct;
	else if (!strcmp(ct->name, "cpu-fan-b-0"))
		cpu_fans[0][1] = ct;
	else if (!strcmp(ct->name, "cpu-fan-c-0"))
		cpu_fans[0][2] = ct;
	else if (!strcmp(ct->name, "cpu-fan-a-1"))
		cpu_fans[1][0] = ct;
	else if (!strcmp(ct->name, "cpu-fan-b-1"))
		cpu_fans[1][1] = ct;
	else if (!strcmp(ct->name, "cpu-fan-c-1"))
		cpu_fans[1][2] = ct;
	else if (!strcmp(ct->name, "backside-fan"))
		backside_fan = ct;
	else if (!strcmp(ct->name, "slots-fan"))
		slots_fan = ct;
	else if (!strcmp(ct->name, "cpufreq-clamp"))
		cpufreq_clamp = ct;

	all_controls =
		cpu_fans[0][0] &&
		cpu_fans[0][1] &&
		cpu_fans[0][2] &&
		backside_fan &&
		slots_fan;
	if (nr_chips > 1)
		all_controls &=
			cpu_fans[1][0] &&
			cpu_fans[1][1] &&
			cpu_fans[1][2];
	have_all_controls = all_controls;
}