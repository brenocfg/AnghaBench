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
struct cpufreq_policy {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;
struct TYPE_2__ {unsigned int (* fast_switch ) (struct cpufreq_policy*,unsigned int) ;} ;

/* Variables and functions */
 unsigned int clamp_val (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* cpufreq_driver ; 
 unsigned int stub1 (struct cpufreq_policy*,unsigned int) ; 

unsigned int cpufreq_driver_fast_switch(struct cpufreq_policy *policy,
					unsigned int target_freq)
{
	target_freq = clamp_val(target_freq, policy->min, policy->max);

	return cpufreq_driver->fast_switch(policy, target_freq);
}