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
struct tegra_smmu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMMU_TLB_FLUSH ; 
 int /*<<< orphan*/  SMMU_TLB_FLUSH_VA_MATCH_ALL ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void smmu_flush_tlb(struct tegra_smmu *smmu)
{
	smmu_writel(smmu, SMMU_TLB_FLUSH_VA_MATCH_ALL, SMMU_TLB_FLUSH);
}