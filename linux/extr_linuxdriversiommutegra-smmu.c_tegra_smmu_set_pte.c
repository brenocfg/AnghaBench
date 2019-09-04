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
struct tegra_smmu_as {int /*<<< orphan*/  id; struct tegra_smmu* smmu; } ;
struct tegra_smmu {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_sync_single_range_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int,int /*<<< orphan*/ ) ; 
 unsigned long offset_in_page (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smmu_flush (struct tegra_smmu*) ; 
 int /*<<< orphan*/  smmu_flush_ptc (struct tegra_smmu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  smmu_flush_tlb_group (struct tegra_smmu*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void tegra_smmu_set_pte(struct tegra_smmu_as *as, unsigned long iova,
			       u32 *pte, dma_addr_t pte_dma, u32 val)
{
	struct tegra_smmu *smmu = as->smmu;
	unsigned long offset = offset_in_page(pte);

	*pte = val;

	dma_sync_single_range_for_device(smmu->dev, pte_dma, offset,
					 4, DMA_TO_DEVICE);
	smmu_flush_ptc(smmu, pte_dma, offset);
	smmu_flush_tlb_group(smmu, as->id, iova);
	smmu_flush(smmu);
}