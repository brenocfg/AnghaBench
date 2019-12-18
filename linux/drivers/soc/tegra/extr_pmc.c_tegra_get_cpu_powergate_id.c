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
struct tegra_pmc {TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int num_cpu_powergates; int* cpu_powergates; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int tegra_get_cpu_powergate_id(struct tegra_pmc *pmc,
				      unsigned int cpuid)
{
	if (pmc->soc && cpuid < pmc->soc->num_cpu_powergates)
		return pmc->soc->cpu_powergates[cpuid];

	return -EINVAL;
}