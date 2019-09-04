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
typedef  scalar_t__ u32 ;
struct tegra_smmu_as {int dummy; } ;
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int SMMU_PTE_ATTR ; 
 int __phys_to_pfn (int /*<<< orphan*/ ) ; 
 scalar_t__* as_get_pte (struct tegra_smmu_as*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tegra_smmu_pte_get_use (struct tegra_smmu_as*,unsigned long) ; 
 int /*<<< orphan*/  tegra_smmu_set_pte (struct tegra_smmu_as*,unsigned long,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct tegra_smmu_as* to_smmu_as (struct iommu_domain*) ; 

__attribute__((used)) static int tegra_smmu_map(struct iommu_domain *domain, unsigned long iova,
			  phys_addr_t paddr, size_t size, int prot)
{
	struct tegra_smmu_as *as = to_smmu_as(domain);
	dma_addr_t pte_dma;
	u32 *pte;

	pte = as_get_pte(as, iova, &pte_dma);
	if (!pte)
		return -ENOMEM;

	/* If we aren't overwriting a pre-existing entry, increment use */
	if (*pte == 0)
		tegra_smmu_pte_get_use(as, iova);

	tegra_smmu_set_pte(as, iova, pte, pte_dma,
			   __phys_to_pfn(paddr) | SMMU_PTE_ATTR);

	return 0;
}