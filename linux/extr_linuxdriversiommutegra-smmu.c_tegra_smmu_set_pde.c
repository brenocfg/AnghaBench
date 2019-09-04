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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_smmu_as {int /*<<< orphan*/  id; int /*<<< orphan*/  pd_dma; int /*<<< orphan*/  pd; struct tegra_smmu* smmu; } ;
struct tegra_smmu {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 unsigned int iova_pd_index (unsigned long) ; 
 int /*<<< orphan*/ * page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_flush (struct tegra_smmu*) ; 
 int /*<<< orphan*/  smmu_flush_ptc (struct tegra_smmu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  smmu_flush_tlb_section (struct tegra_smmu*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void tegra_smmu_set_pde(struct tegra_smmu_as *as, unsigned long iova,
			       u32 value)
{
	unsigned int pd_index = iova_pd_index(iova);
	struct tegra_smmu *smmu = as->smmu;
	u32 *pd = page_address(as->pd);
	unsigned long offset = pd_index * sizeof(*pd);

	/* Set the page directory entry first */
	pd[pd_index] = value;

	/* The flush the page directory entry from caches */
	dma_sync_single_range_for_device(smmu->dev, as->pd_dma, offset,
					 sizeof(*pd), DMA_TO_DEVICE);

	/* And flush the iommu */
	smmu_flush_ptc(smmu, as->pd_dma, offset);
	smmu_flush_tlb_section(smmu, as->id, iova);
	smmu_flush(smmu);
}