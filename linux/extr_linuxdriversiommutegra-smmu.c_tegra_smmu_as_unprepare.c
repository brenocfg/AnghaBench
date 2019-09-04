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
struct tegra_smmu_as {scalar_t__ use_count; int /*<<< orphan*/ * smmu; int /*<<< orphan*/  pd_dma; int /*<<< orphan*/  id; } ;
struct tegra_smmu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SMMU_SIZE_PD ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_smmu_free_asid (struct tegra_smmu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra_smmu_as_unprepare(struct tegra_smmu *smmu,
				    struct tegra_smmu_as *as)
{
	if (--as->use_count > 0)
		return;

	tegra_smmu_free_asid(smmu, as->id);

	dma_unmap_page(smmu->dev, as->pd_dma, SMMU_SIZE_PD, DMA_TO_DEVICE);

	as->smmu = NULL;
}