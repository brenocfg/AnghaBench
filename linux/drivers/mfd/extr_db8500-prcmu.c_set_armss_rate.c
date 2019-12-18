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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ project; } ;
struct TYPE_4__ {TYPE_1__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_100_OPP ; 
 int /*<<< orphan*/  ARM_50_OPP ; 
 int /*<<< orphan*/  ARM_EXTCLK ; 
 int /*<<< orphan*/  ARM_MAX_OPP ; 
 int ARRAY_SIZE (unsigned long*) ; 
 int EINVAL ; 
 scalar_t__ PRCMU_FW_PROJECT_U8520 ; 
 unsigned long* db8500_armss_freqs ; 
 int db8500_prcmu_set_arm_opp (int /*<<< orphan*/ ) ; 
 unsigned long* db8520_armss_freqs ; 
 TYPE_2__ fw_info ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_armss_rate(unsigned long rate)
{
	unsigned long freq;
	u8 opps[] = { ARM_EXTCLK, ARM_50_OPP, ARM_100_OPP, ARM_MAX_OPP };
	const unsigned long *freqs;
	int nfreqs;
	int i;

	if (fw_info.version.project == PRCMU_FW_PROJECT_U8520) {
		freqs = db8520_armss_freqs;
		nfreqs = ARRAY_SIZE(db8520_armss_freqs);
	} else {
		freqs = db8500_armss_freqs;
		nfreqs = ARRAY_SIZE(db8500_armss_freqs);
	}

	/* Find the corresponding arm opp from the cpufreq table. */
	for (i = 0; i < nfreqs; i++) {
		freq = freqs[i];
		if (rate == freq)
			break;
	}

	if (rate != freq)
		return -EINVAL;

	/* Set the new arm opp. */
	pr_debug("SET ARM OPP 0x%02x\n", opps[i]);
	return db8500_prcmu_set_arm_opp(opps[i]);
}