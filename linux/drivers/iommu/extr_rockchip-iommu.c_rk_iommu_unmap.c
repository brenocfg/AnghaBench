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
struct rk_iommu_domain {int /*<<< orphan*/  dt_lock; int /*<<< orphan*/ * dt; } ;
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ phys_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  rk_dte_is_pt_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ rk_dte_pt_address (int /*<<< orphan*/ ) ; 
 size_t rk_iommu_unmap_iova (struct rk_iommu_domain*,int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  rk_iommu_zap_iova (struct rk_iommu_domain*,scalar_t__,size_t) ; 
 size_t rk_iova_dte_index (scalar_t__) ; 
 int rk_iova_pte_index (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rk_iommu_domain* to_rk_domain (struct iommu_domain*) ; 

__attribute__((used)) static size_t rk_iommu_unmap(struct iommu_domain *domain, unsigned long _iova,
			     size_t size, struct iommu_iotlb_gather *gather)
{
	struct rk_iommu_domain *rk_domain = to_rk_domain(domain);
	unsigned long flags;
	dma_addr_t pte_dma, iova = (dma_addr_t)_iova;
	phys_addr_t pt_phys;
	u32 dte;
	u32 *pte_addr;
	size_t unmap_size;

	spin_lock_irqsave(&rk_domain->dt_lock, flags);

	/*
	 * pgsize_bitmap specifies iova sizes that fit in one page table
	 * (1024 4-KiB pages = 4 MiB).
	 * So, size will always be 4096 <= size <= 4194304.
	 * Since iommu_unmap() guarantees that both iova and size will be
	 * aligned, we will always only be unmapping from a single dte here.
	 */
	dte = rk_domain->dt[rk_iova_dte_index(iova)];
	/* Just return 0 if iova is unmapped */
	if (!rk_dte_is_pt_valid(dte)) {
		spin_unlock_irqrestore(&rk_domain->dt_lock, flags);
		return 0;
	}

	pt_phys = rk_dte_pt_address(dte);
	pte_addr = (u32 *)phys_to_virt(pt_phys) + rk_iova_pte_index(iova);
	pte_dma = pt_phys + rk_iova_pte_index(iova) * sizeof(u32);
	unmap_size = rk_iommu_unmap_iova(rk_domain, pte_addr, pte_dma, size);

	spin_unlock_irqrestore(&rk_domain->dt_lock, flags);

	/* Shootdown iotlb entries for iova range that was just unmapped */
	rk_iommu_zap_iova(rk_domain, iova, unmap_size);

	return unmap_size;
}