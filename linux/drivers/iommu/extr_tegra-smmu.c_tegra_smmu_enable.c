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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_smmu_swgroup {int /*<<< orphan*/  reg; } ;
struct tegra_smmu {TYPE_1__* soc; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  bit; } ;
struct tegra_mc_client {unsigned int swgroup; TYPE_2__ smmu; } ;
struct TYPE_3__ {unsigned int num_clients; struct tegra_mc_client* clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMMU_ASID_ENABLE ; 
 int /*<<< orphan*/  SMMU_ASID_MASK ; 
 int /*<<< orphan*/  SMMU_ASID_VALUE (unsigned int) ; 
 int /*<<< orphan*/  smmu_readl (struct tegra_smmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_smmu_swgroup* tegra_smmu_find_swgroup (struct tegra_smmu*,unsigned int) ; 

__attribute__((used)) static void tegra_smmu_enable(struct tegra_smmu *smmu, unsigned int swgroup,
			      unsigned int asid)
{
	const struct tegra_smmu_swgroup *group;
	unsigned int i;
	u32 value;

	for (i = 0; i < smmu->soc->num_clients; i++) {
		const struct tegra_mc_client *client = &smmu->soc->clients[i];

		if (client->swgroup != swgroup)
			continue;

		value = smmu_readl(smmu, client->smmu.reg);
		value |= BIT(client->smmu.bit);
		smmu_writel(smmu, value, client->smmu.reg);
	}

	group = tegra_smmu_find_swgroup(smmu, swgroup);
	if (group) {
		value = smmu_readl(smmu, group->reg);
		value &= ~SMMU_ASID_MASK;
		value |= SMMU_ASID_VALUE(asid);
		value |= SMMU_ASID_ENABLE;
		smmu_writel(smmu, value, group->reg);
	}
}