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
struct rk_iommu_domain {int /*<<< orphan*/  dt_lock; } ;
typedef  size_t phys_addr_t ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 int EADDRINUSE ; 
 size_t SPAGE_SIZE ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int*,size_t*,size_t*,int) ; 
 int /*<<< orphan*/  rk_iommu_unmap_iova (struct rk_iommu_domain*,int /*<<< orphan*/ *,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rk_iommu_zap_iova_first_last (struct rk_iommu_domain*,unsigned int,size_t) ; 
 int /*<<< orphan*/  rk_mk_pte (size_t,int) ; 
 scalar_t__ rk_pte_is_page_valid (int /*<<< orphan*/ ) ; 
 size_t rk_pte_page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_table_flush (struct rk_iommu_domain*,unsigned int,unsigned int) ; 

__attribute__((used)) static int rk_iommu_map_iova(struct rk_iommu_domain *rk_domain, u32 *pte_addr,
			     dma_addr_t pte_dma, dma_addr_t iova,
			     phys_addr_t paddr, size_t size, int prot)
{
	unsigned int pte_count;
	unsigned int pte_total = size / SPAGE_SIZE;
	phys_addr_t page_phys;

	assert_spin_locked(&rk_domain->dt_lock);

	for (pte_count = 0; pte_count < pte_total; pte_count++) {
		u32 pte = pte_addr[pte_count];

		if (rk_pte_is_page_valid(pte))
			goto unwind;

		pte_addr[pte_count] = rk_mk_pte(paddr, prot);

		paddr += SPAGE_SIZE;
	}

	rk_table_flush(rk_domain, pte_dma, pte_total);

	/*
	 * Zap the first and last iova to evict from iotlb any previously
	 * mapped cachelines holding stale values for its dte and pte.
	 * We only zap the first and last iova, since only they could have
	 * dte or pte shared with an existing mapping.
	 */
	rk_iommu_zap_iova_first_last(rk_domain, iova, size);

	return 0;
unwind:
	/* Unmap the range of iovas that we just mapped */
	rk_iommu_unmap_iova(rk_domain, pte_addr, pte_dma,
			    pte_count * SPAGE_SIZE);

	iova += pte_count * SPAGE_SIZE;
	page_phys = rk_pte_page_address(pte_addr[pte_count]);
	pr_err("iova: %pad already mapped to %pa cannot remap to phys: %pa prot: %#x\n",
	       &iova, &page_phys, &paddr, prot);

	return -EADDRINUSE;
}