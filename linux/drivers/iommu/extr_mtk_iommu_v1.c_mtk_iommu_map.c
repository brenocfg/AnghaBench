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
struct mtk_iommu_domain {int* pgt_va; int /*<<< orphan*/  data; int /*<<< orphan*/  pgtlock; } ;
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int EEXIST ; 
 int F_DESC_NONSEC ; 
 int F_DESC_VALID ; 
 size_t MT2701_IOMMU_PAGE_SHIFT ; 
 scalar_t__ MT2701_IOMMU_PAGE_SIZE ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mtk_iommu_tlb_flush_range (int /*<<< orphan*/ ,unsigned long,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mtk_iommu_domain* to_mtk_domain (struct iommu_domain*) ; 

__attribute__((used)) static int mtk_iommu_map(struct iommu_domain *domain, unsigned long iova,
			 phys_addr_t paddr, size_t size, int prot)
{
	struct mtk_iommu_domain *dom = to_mtk_domain(domain);
	unsigned int page_num = size >> MT2701_IOMMU_PAGE_SHIFT;
	unsigned long flags;
	unsigned int i;
	u32 *pgt_base_iova = dom->pgt_va + (iova  >> MT2701_IOMMU_PAGE_SHIFT);
	u32 pabase = (u32)paddr;
	int map_size = 0;

	spin_lock_irqsave(&dom->pgtlock, flags);
	for (i = 0; i < page_num; i++) {
		if (pgt_base_iova[i]) {
			memset(pgt_base_iova, 0, i * sizeof(u32));
			break;
		}
		pgt_base_iova[i] = pabase | F_DESC_VALID | F_DESC_NONSEC;
		pabase += MT2701_IOMMU_PAGE_SIZE;
		map_size += MT2701_IOMMU_PAGE_SIZE;
	}

	spin_unlock_irqrestore(&dom->pgtlock, flags);

	mtk_iommu_tlb_flush_range(dom->data, iova, size);

	return map_size == size ? 0 : -EEXIST;
}