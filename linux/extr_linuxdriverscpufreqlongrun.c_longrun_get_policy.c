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
typedef  int u32 ;
struct cpufreq_policy {scalar_t__ cpu; scalar_t__ max; scalar_t__ min; int /*<<< orphan*/  policy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPUFREQ_POLICY_PERFORMANCE ; 
 int /*<<< orphan*/  CPUFREQ_POLICY_POWERSAVE ; 
 int /*<<< orphan*/  MSR_TMTA_LONGRUN_CTRL ; 
 int /*<<< orphan*/  MSR_TMTA_LONGRUN_FLAGS ; 
 scalar_t__ longrun_high_freq ; 
 scalar_t__ longrun_low_freq ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void longrun_get_policy(struct cpufreq_policy *policy)
{
	u32 msr_lo, msr_hi;

	rdmsr(MSR_TMTA_LONGRUN_FLAGS, msr_lo, msr_hi);
	pr_debug("longrun flags are %x - %x\n", msr_lo, msr_hi);
	if (msr_lo & 0x01)
		policy->policy = CPUFREQ_POLICY_PERFORMANCE;
	else
		policy->policy = CPUFREQ_POLICY_POWERSAVE;

	rdmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);
	pr_debug("longrun ctrl is %x - %x\n", msr_lo, msr_hi);
	msr_lo &= 0x0000007F;
	msr_hi &= 0x0000007F;

	if (longrun_high_freq <= longrun_low_freq) {
		/* Assume degenerate Longrun table */
		policy->min = policy->max = longrun_high_freq;
	} else {
		policy->min = longrun_low_freq + msr_lo *
			((longrun_high_freq - longrun_low_freq) / 100);
		policy->max = longrun_low_freq + msr_hi *
			((longrun_high_freq - longrun_low_freq) / 100);
	}
	policy->cpu = 0;
}