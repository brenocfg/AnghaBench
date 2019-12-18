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
typedef  size_t u32 ;
struct rk_iommu_domain {size_t* dt; int /*<<< orphan*/  dt_lock; } ;
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (size_t*) ; 
 int PTR_ERR (size_t*) ; 
 size_t* rk_dte_get_page_table (struct rk_iommu_domain*,scalar_t__) ; 
 scalar_t__ rk_dte_pt_address (size_t) ; 
 int rk_iommu_map_iova (struct rk_iommu_domain*,size_t*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,size_t,int) ; 
 size_t rk_iova_dte_index (scalar_t__) ; 
 size_t rk_iova_pte_index (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rk_iommu_domain* to_rk_domain (struct iommu_domain*) ; 

__attribute__((used)) static int rk_iommu_map(struct iommu_domain *domain, unsigned long _iova,
			phys_addr_t paddr, size_t size, int prot)
{
	struct rk_iommu_domain *rk_domain = to_rk_domain(domain);
	unsigned long flags;
	dma_addr_t pte_dma, iova = (dma_addr_t)_iova;
	u32 *page_table, *pte_addr;
	u32 dte_index, pte_index;
	int ret;

	spin_lock_irqsave(&rk_domain->dt_lock, flags);

	/*
	 * pgsize_bitmap specifies iova sizes that fit in one page table
	 * (1024 4-KiB pages = 4 MiB).
	 * So, size will always be 4096 <= size <= 4194304.
	 * Since iommu_map() guarantees that both iova and size will be
	 * aligned, we will always only be mapping from a single dte here.
	 */
	page_table = rk_dte_get_page_table(rk_domain, iova);
	if (IS_ERR(page_table)) {
		spin_unlock_irqrestore(&rk_domain->dt_lock, flags);
		return PTR_ERR(page_table);
	}

	dte_index = rk_domain->dt[rk_iova_dte_index(iova)];
	pte_index = rk_iova_pte_index(iova);
	pte_addr = &page_table[pte_index];
	pte_dma = rk_dte_pt_address(dte_index) + pte_index * sizeof(u32);
	ret = rk_iommu_map_iova(rk_domain, pte_addr, pte_dma, iova,
				paddr, size, prot);

	spin_unlock_irqrestore(&rk_domain->dt_lock, flags);

	return ret;
}