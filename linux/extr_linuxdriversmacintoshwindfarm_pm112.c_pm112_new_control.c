#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wf_control {TYPE_1__* ops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int (* get_max ) (struct wf_control*) ;} ;

/* Variables and functions */
 int CPU_FANS_REQD ; 
 int FIRST_PUMP ; 
 int LAST_PUMP ; 
 int NR_CPU_FANS ; 
 struct wf_control* backside_fan ; 
 char** cpu_fan_names ; 
 int* cpu_fan_scale ; 
 struct wf_control** cpu_fans ; 
 struct wf_control* cpufreq_clamp ; 
 struct wf_control* drive_bay_fan ; 
 int have_all_controls ; 
 struct wf_control* slots_fan ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int stub1 (struct wf_control*) ; 
 int stub2 (struct wf_control*) ; 
 scalar_t__ wf_get_control (struct wf_control*) ; 

__attribute__((used)) static void pm112_new_control(struct wf_control *ct)
{
	int i, max_exhaust;

	if (cpufreq_clamp == NULL && !strcmp(ct->name, "cpufreq-clamp")) {
		if (wf_get_control(ct) == 0)
			cpufreq_clamp = ct;
	}

	for (i = 0; i < NR_CPU_FANS; ++i) {
		if (!strcmp(ct->name, cpu_fan_names[i])) {
			if (cpu_fans[i] == NULL && wf_get_control(ct) == 0)
				cpu_fans[i] = ct;
			break;
		}
	}
	if (i >= NR_CPU_FANS) {
		/* not a CPU fan, try the others */
		if (!strcmp(ct->name, "backside-fan")) {
			if (backside_fan == NULL && wf_get_control(ct) == 0)
				backside_fan = ct;
		} else if (!strcmp(ct->name, "slots-fan")) {
			if (slots_fan == NULL && wf_get_control(ct) == 0)
				slots_fan = ct;
		} else if (!strcmp(ct->name, "drive-bay-fan")) {
			if (drive_bay_fan == NULL && wf_get_control(ct) == 0)
				drive_bay_fan = ct;
		}
		return;
	}

	for (i = 0; i < CPU_FANS_REQD; ++i)
		if (cpu_fans[i] == NULL)
			return;

	/* work out pump scaling factors */
	max_exhaust = cpu_fans[0]->ops->get_max(cpu_fans[0]);
	for (i = FIRST_PUMP; i <= LAST_PUMP; ++i)
		if ((ct = cpu_fans[i]) != NULL)
			cpu_fan_scale[i] =
				ct->ops->get_max(ct) * 100 / max_exhaust;

	have_all_controls = 1;
}