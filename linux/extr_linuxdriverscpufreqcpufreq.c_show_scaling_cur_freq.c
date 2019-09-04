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
struct cpufreq_policy {unsigned int cur; int /*<<< orphan*/  cpu; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {unsigned int (* get ) (int /*<<< orphan*/ ) ;scalar_t__ setpolicy; } ;

/* Variables and functions */
 unsigned int arch_freq_get_on_cpu (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpufreq_driver ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int) ; 
 unsigned int stub1 (int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t show_scaling_cur_freq(struct cpufreq_policy *policy, char *buf)
{
	ssize_t ret;
	unsigned int freq;

	freq = arch_freq_get_on_cpu(policy->cpu);
	if (freq)
		ret = sprintf(buf, "%u\n", freq);
	else if (cpufreq_driver && cpufreq_driver->setpolicy &&
			cpufreq_driver->get)
		ret = sprintf(buf, "%u\n", cpufreq_driver->get(policy->cpu));
	else
		ret = sprintf(buf, "%u\n", policy->cur);
	return ret;
}