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
struct tegra_smmu_group_soc {unsigned int num_swgroups; unsigned int* swgroups; } ;
struct tegra_smmu {TYPE_1__* soc; } ;
struct TYPE_2__ {unsigned int num_groups; struct tegra_smmu_group_soc const* groups; } ;

/* Variables and functions */

__attribute__((used)) static const struct tegra_smmu_group_soc *
tegra_smmu_find_group(struct tegra_smmu *smmu, unsigned int swgroup)
{
	unsigned int i, j;

	for (i = 0; i < smmu->soc->num_groups; i++)
		for (j = 0; j < smmu->soc->groups[i].num_swgroups; j++)
			if (smmu->soc->groups[i].swgroups[j] == swgroup)
				return &smmu->soc->groups[i];

	return NULL;
}