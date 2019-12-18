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
struct TYPE_3__ {scalar_t__ project; } ;
struct TYPE_4__ {TYPE_1__ version; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 scalar_t__ PRCMU_FW_PROJECT_U8520 ; 
 unsigned long* db8500_armss_freqs ; 
 unsigned long* db8520_armss_freqs ; 
 TYPE_2__ fw_info ; 

__attribute__((used)) static long round_armss_rate(unsigned long rate)
{
	unsigned long freq = 0;
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
		if (rate <= freq)
			break;
	}

	/* Return the last valid value, even if a match was not found. */
	return freq;
}