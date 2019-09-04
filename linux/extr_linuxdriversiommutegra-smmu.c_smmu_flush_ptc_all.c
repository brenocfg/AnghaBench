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
 int /*<<< orphan*/  SMMU_PTC_FLUSH ; 
 int /*<<< orphan*/  SMMU_PTC_FLUSH_TYPE_ALL ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smmu_flush_ptc_all(struct tegra_smmu *smmu)
{
	smmu_writel(smmu, SMMU_PTC_FLUSH_TYPE_ALL, SMMU_PTC_FLUSH);
}