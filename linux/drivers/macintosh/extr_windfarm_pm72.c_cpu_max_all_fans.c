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
 scalar_t__* cpu_front_fans ; 
 scalar_t__* cpu_pumps ; 
 scalar_t__* cpu_rear_fans ; 
 scalar_t__ cpufreq_clamp ; 
 int nr_chips ; 
 int /*<<< orphan*/  wf_control_set_max (scalar_t__) ; 

__attribute__((used)) static void cpu_max_all_fans(void)
{
	int i;

	/* We max all CPU fans in case of a sensor error. We also do the
	 * cpufreq clamping now, even if it's supposedly done later by the
	 * generic code anyway, we do it earlier here to react faster
	 */
	if (cpufreq_clamp)
		wf_control_set_max(cpufreq_clamp);
	for (i = 0; i < nr_chips; i++) {
		if (cpu_front_fans[i])
			wf_control_set_max(cpu_front_fans[i]);
		if (cpu_rear_fans[i])
			wf_control_set_max(cpu_rear_fans[i]);
		if (cpu_pumps[i])
			wf_control_set_max(cpu_pumps[i]);
	}
}