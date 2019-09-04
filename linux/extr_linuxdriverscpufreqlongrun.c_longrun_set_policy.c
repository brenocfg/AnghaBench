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
struct cpufreq_policy {scalar_t__ min; scalar_t__ max; int policy; } ;

/* Variables and functions */
#define  CPUFREQ_POLICY_PERFORMANCE 129 
#define  CPUFREQ_POLICY_POWERSAVE 128 
 int EINVAL ; 
 int /*<<< orphan*/  MSR_TMTA_LONGRUN_CTRL ; 
 int /*<<< orphan*/  MSR_TMTA_LONGRUN_FLAGS ; 
 scalar_t__ longrun_high_freq ; 
 scalar_t__ longrun_low_freq ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int longrun_set_policy(struct cpufreq_policy *policy)
{
	u32 msr_lo, msr_hi;
	u32 pctg_lo, pctg_hi;

	if (!policy)
		return -EINVAL;

	if (longrun_high_freq <= longrun_low_freq) {
		/* Assume degenerate Longrun table */
		pctg_lo = pctg_hi = 100;
	} else {
		pctg_lo = (policy->min - longrun_low_freq) /
			((longrun_high_freq - longrun_low_freq) / 100);
		pctg_hi = (policy->max - longrun_low_freq) /
			((longrun_high_freq - longrun_low_freq) / 100);
	}

	if (pctg_hi > 100)
		pctg_hi = 100;
	if (pctg_lo > pctg_hi)
		pctg_lo = pctg_hi;

	/* performance or economy mode */
	rdmsr(MSR_TMTA_LONGRUN_FLAGS, msr_lo, msr_hi);
	msr_lo &= 0xFFFFFFFE;
	switch (policy->policy) {
	case CPUFREQ_POLICY_PERFORMANCE:
		msr_lo |= 0x00000001;
		break;
	case CPUFREQ_POLICY_POWERSAVE:
		break;
	}
	wrmsr(MSR_TMTA_LONGRUN_FLAGS, msr_lo, msr_hi);

	/* lower and upper boundary */
	rdmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);
	msr_lo &= 0xFFFFFF80;
	msr_hi &= 0xFFFFFF80;
	msr_lo |= pctg_lo;
	msr_hi |= pctg_hi;
	wrmsr(MSR_TMTA_LONGRUN_CTRL, msr_lo, msr_hi);

	return 0;
}