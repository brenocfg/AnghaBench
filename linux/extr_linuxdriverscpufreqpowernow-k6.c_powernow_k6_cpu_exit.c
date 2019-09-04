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
struct cpufreq_policy {int /*<<< orphan*/  cur; } ;
struct cpufreq_freqs {scalar_t__ new; scalar_t__ flags; int /*<<< orphan*/  old; } ;
struct TYPE_2__ {scalar_t__ frequency; scalar_t__ driver_data; } ;

/* Variables and functions */
 scalar_t__ CPUFREQ_TABLE_END ; 
 TYPE_1__* clock_ratio ; 
 int /*<<< orphan*/  cpufreq_freq_transition_begin (struct cpufreq_policy*,struct cpufreq_freqs*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_end (struct cpufreq_policy*,struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 scalar_t__ max_multiplier ; 
 int /*<<< orphan*/  powernow_k6_target (struct cpufreq_policy*,unsigned int) ; 

__attribute__((used)) static int powernow_k6_cpu_exit(struct cpufreq_policy *policy)
{
	unsigned int i;

	for (i = 0; (clock_ratio[i].frequency != CPUFREQ_TABLE_END); i++) {
		if (clock_ratio[i].driver_data == max_multiplier) {
			struct cpufreq_freqs freqs;

			freqs.old = policy->cur;
			freqs.new = clock_ratio[i].frequency;
			freqs.flags = 0;

			cpufreq_freq_transition_begin(policy, &freqs);
			powernow_k6_target(policy, i);
			cpufreq_freq_transition_end(policy, &freqs, 0);
			break;
		}
	}
	return 0;
}