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
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/  max_freq; } ;
struct cpufreq_policy {size_t cpu; TYPE_1__ cpuinfo; int /*<<< orphan*/  related_cpus; } ;
struct TYPE_4__ {unsigned int frequency; } ;

/* Variables and functions */
 size_t A15_CLUSTER ; 
 size_t A7_CLUSTER ; 
 int /*<<< orphan*/  arch_set_freq_scale (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int bL_cpufreq_set_rate (size_t,size_t,size_t,unsigned int) ; 
 unsigned int clk_big_min ; 
 unsigned int clk_little_max ; 
 size_t cpu_to_cluster (size_t) ; 
 TYPE_2__** freq_table ; 
 scalar_t__ is_bL_switching_enabled () ; 
 size_t per_cpu (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  physical_cluster ; 

__attribute__((used)) static int bL_cpufreq_set_target(struct cpufreq_policy *policy,
		unsigned int index)
{
	u32 cpu = policy->cpu, cur_cluster, new_cluster, actual_cluster;
	unsigned int freqs_new;
	int ret;

	cur_cluster = cpu_to_cluster(cpu);
	new_cluster = actual_cluster = per_cpu(physical_cluster, cpu);

	freqs_new = freq_table[cur_cluster][index].frequency;

	if (is_bL_switching_enabled()) {
		if ((actual_cluster == A15_CLUSTER) &&
				(freqs_new < clk_big_min)) {
			new_cluster = A7_CLUSTER;
		} else if ((actual_cluster == A7_CLUSTER) &&
				(freqs_new > clk_little_max)) {
			new_cluster = A15_CLUSTER;
		}
	}

	ret = bL_cpufreq_set_rate(cpu, actual_cluster, new_cluster, freqs_new);

	if (!ret) {
		arch_set_freq_scale(policy->related_cpus, freqs_new,
				    policy->cpuinfo.max_freq);
	}

	return ret;
}