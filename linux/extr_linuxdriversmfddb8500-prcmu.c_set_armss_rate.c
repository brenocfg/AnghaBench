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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_100_OPP ; 
 int /*<<< orphan*/  ARM_50_OPP ; 
 int /*<<< orphan*/  ARM_EXTCLK ; 
 int /*<<< orphan*/  ARM_MAX_OPP ; 
 int ARRAY_SIZE (unsigned long*) ; 
 int EINVAL ; 
 unsigned long* armss_freqs ; 
 int db8500_prcmu_set_arm_opp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_armss_rate(unsigned long rate)
{
	unsigned long freq;
	u8 opps[] = { ARM_EXTCLK, ARM_50_OPP, ARM_100_OPP, ARM_MAX_OPP };
	int i;

	/* Find the corresponding arm opp from the cpufreq table. */
	for (i = 0; i < ARRAY_SIZE(armss_freqs); i++) {
		freq = armss_freqs[i];
		if (rate == freq)
			break;
	}

	if (rate != freq)
		return -EINVAL;

	/* Set the new arm opp. */
	pr_debug("SET ARM OPP 0x%02x\n", opps[i]);
	return db8500_prcmu_set_arm_opp(opps[i]);
}