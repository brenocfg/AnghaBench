#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct private_data {int /*<<< orphan*/  cpu_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_freq; } ;
struct cpufreq_policy {TYPE_2__ cpuinfo; int /*<<< orphan*/  related_cpus; TYPE_1__* freq_table; struct private_data* driver_data; } ;
struct TYPE_3__ {unsigned long frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  arch_set_freq_scale (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int dev_pm_opp_set_rate (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int set_target(struct cpufreq_policy *policy, unsigned int index)
{
	struct private_data *priv = policy->driver_data;
	unsigned long freq = policy->freq_table[index].frequency;
	int ret;

	ret = dev_pm_opp_set_rate(priv->cpu_dev, freq * 1000);

	if (!ret) {
		arch_set_freq_scale(policy->related_cpus, freq,
				    policy->cpuinfo.max_freq);
	}

	return ret;
}