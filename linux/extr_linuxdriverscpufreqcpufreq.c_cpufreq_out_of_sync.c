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
struct cpufreq_policy {int /*<<< orphan*/  cur; } ;
struct cpufreq_freqs {unsigned int new; int /*<<< orphan*/  old; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpufreq_freq_transition_begin (struct cpufreq_policy*,struct cpufreq_freqs*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_end (struct cpufreq_policy*,struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void cpufreq_out_of_sync(struct cpufreq_policy *policy,
				unsigned int new_freq)
{
	struct cpufreq_freqs freqs;

	pr_debug("Warning: CPU frequency out of sync: cpufreq and timing core thinks of %u, is %u kHz\n",
		 policy->cur, new_freq);

	freqs.old = policy->cur;
	freqs.new = new_freq;

	cpufreq_freq_transition_begin(policy, &freqs);
	cpufreq_freq_transition_end(policy, &freqs, 0);
}