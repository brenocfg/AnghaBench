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
typedef  int u32 ;
struct tegra_smmu {TYPE_1__* soc; } ;
struct TYPE_2__ {int num_asids; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMMU_TLB_FLUSH ; 
 int SMMU_TLB_FLUSH_ASID_MATCH ; 
 int SMMU_TLB_FLUSH_VA_MATCH_ALL ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smmu_flush_tlb_asid(struct tegra_smmu *smmu,
				       unsigned long asid)
{
	u32 value;

	if (smmu->soc->num_asids == 4)
		value = (asid & 0x3) << 29;
	else
		value = (asid & 0x7f) << 24;

	value |= SMMU_TLB_FLUSH_ASID_MATCH | SMMU_TLB_FLUSH_VA_MATCH_ALL;
	smmu_writel(smmu, value, SMMU_TLB_FLUSH);
}