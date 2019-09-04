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
struct cpufreq_policy {unsigned int max; unsigned int min; int /*<<< orphan*/  cpu; } ;
struct cpufreq_freqs {unsigned int old; unsigned int new; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  cpufreq_freq_transition_begin (struct cpufreq_policy*,struct cpufreq_freqs*) ; 
 int /*<<< orphan*/  cpufreq_freq_transition_end (struct cpufreq_policy*,struct cpufreq_freqs*,int /*<<< orphan*/ ) ; 
 int fid ; 
 unsigned int nforce2_get (int /*<<< orphan*/ ) ; 
 scalar_t__ nforce2_set_fsb (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,...) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 

__attribute__((used)) static int nforce2_target(struct cpufreq_policy *policy,
			  unsigned int target_freq, unsigned int relation)
{
/*        unsigned long         flags; */
	struct cpufreq_freqs freqs;
	unsigned int target_fsb;

	if ((target_freq > policy->max) || (target_freq < policy->min))
		return -EINVAL;

	target_fsb = target_freq / (fid * 100);

	freqs.old = nforce2_get(policy->cpu);
	freqs.new = target_fsb * fid * 100;

	if (freqs.old == freqs.new)
		return 0;

	pr_debug("Old CPU frequency %d kHz, new %d kHz\n",
	       freqs.old, freqs.new);

	cpufreq_freq_transition_begin(policy, &freqs);

	/* Disable IRQs */
	/* local_irq_save(flags); */

	if (nforce2_set_fsb(target_fsb) < 0)
		pr_err("Changing FSB to %d failed\n", target_fsb);
	else
		pr_debug("Changed FSB successfully to %d\n",
			target_fsb);

	/* Enable IRQs */
	/* local_irq_restore(flags); */

	cpufreq_freq_transition_end(policy, &freqs, 0);

	return 0;
}