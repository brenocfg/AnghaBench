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
struct tegra_smmu_as {int /*<<< orphan*/  pd; struct page** pts; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned int iova_pd_index (unsigned long) ; 
 int /*<<< orphan*/ * page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smmu_pde_to_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tegra_smmu_pte_offset (struct page*,unsigned long) ; 

__attribute__((used)) static u32 *tegra_smmu_pte_lookup(struct tegra_smmu_as *as, unsigned long iova,
				  dma_addr_t *dmap)
{
	unsigned int pd_index = iova_pd_index(iova);
	struct page *pt_page;
	u32 *pd;

	pt_page = as->pts[pd_index];
	if (!pt_page)
		return NULL;

	pd = page_address(as->pd);
	*dmap = smmu_pde_to_dma(pd[pd_index]);

	return tegra_smmu_pte_offset(pt_page, iova);
}