#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mtk_iommu_domain {int /*<<< orphan*/  pgtlock; TYPE_1__* iop; } ;
struct iommu_domain {int dummy; } ;
typedef  int phys_addr_t ;
struct TYPE_2__ {int (* map ) (TYPE_1__*,unsigned long,int,size_t,int) ;} ;

/* Variables and functions */
 int DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (TYPE_1__*,unsigned long,int,size_t,int) ; 
 struct mtk_iommu_domain* to_mtk_domain (struct iommu_domain*) ; 

__attribute__((used)) static int mtk_iommu_map(struct iommu_domain *domain, unsigned long iova,
			 phys_addr_t paddr, size_t size, int prot)
{
	struct mtk_iommu_domain *dom = to_mtk_domain(domain);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&dom->pgtlock, flags);
	ret = dom->iop->map(dom->iop, iova, paddr & DMA_BIT_MASK(32),
			    size, prot);
	spin_unlock_irqrestore(&dom->pgtlock, flags);

	return ret;
}