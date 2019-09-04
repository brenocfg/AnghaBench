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
 int CPUFREQ_HIGH ; 
 scalar_t__ pfunc_cpu0_volt_high ; 
 scalar_t__ pfunc_cpu0_volt_low ; 
 scalar_t__ pfunc_cpu1_volt_high ; 
 scalar_t__ pfunc_cpu1_volt_low ; 
 int /*<<< orphan*/  pmf_call_one (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void g5_pfunc_switch_volt(int speed_mode)
{
	if (speed_mode == CPUFREQ_HIGH) {
		if (pfunc_cpu0_volt_high)
			pmf_call_one(pfunc_cpu0_volt_high, NULL);
		if (pfunc_cpu1_volt_high)
			pmf_call_one(pfunc_cpu1_volt_high, NULL);
	} else {
		if (pfunc_cpu0_volt_low)
			pmf_call_one(pfunc_cpu0_volt_low, NULL);
		if (pfunc_cpu1_volt_low)
			pmf_call_one(pfunc_cpu1_volt_low, NULL);
	}
	usleep_range(10000, 10000); /* should be faster , to fix */
}