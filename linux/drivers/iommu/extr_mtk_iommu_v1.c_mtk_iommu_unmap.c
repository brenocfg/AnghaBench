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
struct mtk_iommu_domain {int /*<<< orphan*/  data; int /*<<< orphan*/  pgtlock; int /*<<< orphan*/ * pgt_va; } ;
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {int dummy; } ;

/* Variables and functions */
 unsigned long MT2701_IOMMU_PAGE_SHIFT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mtk_iommu_tlb_flush_range (int /*<<< orphan*/ ,unsigned long,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_iommu_domain* to_mtk_domain (struct iommu_domain*) ; 

__attribute__((used)) static size_t mtk_iommu_unmap(struct iommu_domain *domain,
			      unsigned long iova, size_t size,
			      struct iommu_iotlb_gather *gather)
{
	struct mtk_iommu_domain *dom = to_mtk_domain(domain);
	unsigned long flags;
	u32 *pgt_base_iova = dom->pgt_va + (iova  >> MT2701_IOMMU_PAGE_SHIFT);
	unsigned int page_num = size >> MT2701_IOMMU_PAGE_SHIFT;

	spin_lock_irqsave(&dom->pgtlock, flags);
	memset(pgt_base_iova, 0, page_num * sizeof(u32));
	spin_unlock_irqrestore(&dom->pgtlock, flags);

	mtk_iommu_tlb_flush_range(dom->data, iova, size);

	return size;
}