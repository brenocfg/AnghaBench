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
typedef  int u32 ;
struct tegra_smmu_as {scalar_t__ use_count; int id; int /*<<< orphan*/  pd_dma; struct tegra_smmu* smmu; int /*<<< orphan*/  attr; int /*<<< orphan*/  pd; } ;
struct tegra_smmu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SMMU_PTB_ASID ; 
 int /*<<< orphan*/  SMMU_PTB_DATA ; 
 int SMMU_PTB_DATA_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMMU_SIZE_PD ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_dma_addr_valid (struct tegra_smmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_flush (struct tegra_smmu*) ; 
 int /*<<< orphan*/  smmu_flush_ptc (struct tegra_smmu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_flush_tlb_asid (struct tegra_smmu*,int) ; 
 int /*<<< orphan*/  smmu_writel (struct tegra_smmu*,int,int /*<<< orphan*/ ) ; 
 int tegra_smmu_alloc_asid (struct tegra_smmu*,int*) ; 

__attribute__((used)) static int tegra_smmu_as_prepare(struct tegra_smmu *smmu,
				 struct tegra_smmu_as *as)
{
	u32 value;
	int err;

	if (as->use_count > 0) {
		as->use_count++;
		return 0;
	}

	as->pd_dma = dma_map_page(smmu->dev, as->pd, 0, SMMU_SIZE_PD,
				  DMA_TO_DEVICE);
	if (dma_mapping_error(smmu->dev, as->pd_dma))
		return -ENOMEM;

	/* We can't handle 64-bit DMA addresses */
	if (!smmu_dma_addr_valid(smmu, as->pd_dma)) {
		err = -ENOMEM;
		goto err_unmap;
	}

	err = tegra_smmu_alloc_asid(smmu, &as->id);
	if (err < 0)
		goto err_unmap;

	smmu_flush_ptc(smmu, as->pd_dma, 0);
	smmu_flush_tlb_asid(smmu, as->id);

	smmu_writel(smmu, as->id & 0x7f, SMMU_PTB_ASID);
	value = SMMU_PTB_DATA_VALUE(as->pd_dma, as->attr);
	smmu_writel(smmu, value, SMMU_PTB_DATA);
	smmu_flush(smmu);

	as->smmu = smmu;
	as->use_count++;

	return 0;

err_unmap:
	dma_unmap_page(smmu->dev, as->pd_dma, SMMU_SIZE_PD, DMA_TO_DEVICE);
	return err;
}