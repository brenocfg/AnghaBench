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

/* Variables and functions */
 int ARRAY_SIZE (unsigned long*) ; 
 unsigned long* armss_freqs ; 

__attribute__((used)) static long round_armss_rate(unsigned long rate)
{
	unsigned long freq = 0;
	int i;

	/* Find the corresponding arm opp from the cpufreq table. */
	for (i = 0; i < ARRAY_SIZE(armss_freqs); i++) {
		freq = armss_freqs[i];
		if (rate <= freq)
			break;
	}

	/* Return the last valid value, even if a match was not found. */
	return freq;
}