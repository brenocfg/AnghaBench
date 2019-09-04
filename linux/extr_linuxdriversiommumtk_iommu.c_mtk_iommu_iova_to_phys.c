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
struct mtk_iommu_data {scalar_t__ enable_4GB; } ;
struct iommu_domain {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* iova_to_phys ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int) ; 
 struct mtk_iommu_data* mtk_iommu_get_m4u_data () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct mtk_iommu_domain* to_mtk_domain (struct iommu_domain*) ; 

__attribute__((used)) static phys_addr_t mtk_iommu_iova_to_phys(struct iommu_domain *domain,
					  dma_addr_t iova)
{
	struct mtk_iommu_domain *dom = to_mtk_domain(domain);
	struct mtk_iommu_data *data = mtk_iommu_get_m4u_data();
	unsigned long flags;
	phys_addr_t pa;

	spin_lock_irqsave(&dom->pgtlock, flags);
	pa = dom->iop->iova_to_phys(dom->iop, iova);
	spin_unlock_irqrestore(&dom->pgtlock, flags);

	if (data->enable_4GB)
		pa |= BIT_ULL(32);

	return pa;
}