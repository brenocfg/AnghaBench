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
struct tegra_smmu_as {struct page** pts; int /*<<< orphan*/  pd; struct tegra_smmu* smmu; } ;
struct tegra_smmu {int /*<<< orphan*/  dev; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SMMU_MK_PDE (int /*<<< orphan*/ ,int) ; 
 int SMMU_PDE_ATTR ; 
 int SMMU_PDE_NEXT ; 
 int /*<<< orphan*/  SMMU_SIZE_PT ; 
 int __GFP_DMA ; 
 int __GFP_ZERO ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int iova_pd_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_dma_addr_valid (struct tegra_smmu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_pde_to_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tegra_smmu_pte_offset (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_smmu_set_pde (struct tegra_smmu_as*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 *as_get_pte(struct tegra_smmu_as *as, dma_addr_t iova,
		       dma_addr_t *dmap)
{
	unsigned int pde = iova_pd_index(iova);
	struct tegra_smmu *smmu = as->smmu;

	if (!as->pts[pde]) {
		struct page *page;
		dma_addr_t dma;

		page = alloc_page(GFP_KERNEL | __GFP_DMA | __GFP_ZERO);
		if (!page)
			return NULL;

		dma = dma_map_page(smmu->dev, page, 0, SMMU_SIZE_PT,
				   DMA_TO_DEVICE);
		if (dma_mapping_error(smmu->dev, dma)) {
			__free_page(page);
			return NULL;
		}

		if (!smmu_dma_addr_valid(smmu, dma)) {
			dma_unmap_page(smmu->dev, dma, SMMU_SIZE_PT,
				       DMA_TO_DEVICE);
			__free_page(page);
			return NULL;
		}

		as->pts[pde] = page;

		tegra_smmu_set_pde(as, iova, SMMU_MK_PDE(dma, SMMU_PDE_ATTR |
							      SMMU_PDE_NEXT));

		*dmap = dma;
	} else {
		u32 *pd = page_address(as->pd);

		*dmap = smmu_pde_to_dma(pd[pde]);
	}

	return tegra_smmu_pte_offset(as->pts[pde], iova);
}