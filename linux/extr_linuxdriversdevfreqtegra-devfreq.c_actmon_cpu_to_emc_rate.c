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
struct tegra_devfreq {scalar_t__ max_freq; } ;
struct tegra_actmon_emc_ratio {unsigned long cpu_freq; scalar_t__ emc_freq; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct tegra_actmon_emc_ratio*) ; 
 struct tegra_actmon_emc_ratio* actmon_emc_ratios ; 

__attribute__((used)) static unsigned long actmon_cpu_to_emc_rate(struct tegra_devfreq *tegra,
					    unsigned long cpu_freq)
{
	unsigned int i;
	struct tegra_actmon_emc_ratio *ratio = actmon_emc_ratios;

	for (i = 0; i < ARRAY_SIZE(actmon_emc_ratios); i++, ratio++) {
		if (cpu_freq >= ratio->cpu_freq) {
			if (ratio->emc_freq >= tegra->max_freq)
				return tegra->max_freq;
			else
				return ratio->emc_freq;
		}
	}

	return 0;
}