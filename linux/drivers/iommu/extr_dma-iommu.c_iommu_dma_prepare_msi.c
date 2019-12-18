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
struct msi_desc {int /*<<< orphan*/ * iommu_cookie; } ;
struct iommu_domain {struct iommu_dma_cookie* iova_cookie; } ;
struct iommu_dma_msi_page {int dummy; } ;
struct iommu_dma_cookie {int /*<<< orphan*/  msi_lock; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct iommu_dma_msi_page* iommu_dma_get_msi_page (struct device*,int /*<<< orphan*/ ,struct iommu_domain*) ; 
 struct iommu_domain* iommu_get_domain_for_dev (struct device*) ; 
 int /*<<< orphan*/  msi_desc_set_iommu_cookie (struct msi_desc*,struct iommu_dma_msi_page*) ; 
 struct device* msi_desc_to_dev (struct msi_desc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int iommu_dma_prepare_msi(struct msi_desc *desc, phys_addr_t msi_addr)
{
	struct device *dev = msi_desc_to_dev(desc);
	struct iommu_domain *domain = iommu_get_domain_for_dev(dev);
	struct iommu_dma_cookie *cookie;
	struct iommu_dma_msi_page *msi_page;
	unsigned long flags;

	if (!domain || !domain->iova_cookie) {
		desc->iommu_cookie = NULL;
		return 0;
	}

	cookie = domain->iova_cookie;

	/*
	 * We disable IRQs to rule out a possible inversion against
	 * irq_desc_lock if, say, someone tries to retarget the affinity
	 * of an MSI from within an IPI handler.
	 */
	spin_lock_irqsave(&cookie->msi_lock, flags);
	msi_page = iommu_dma_get_msi_page(dev, msi_addr, domain);
	spin_unlock_irqrestore(&cookie->msi_lock, flags);

	msi_desc_set_iommu_cookie(desc, msi_page);

	if (!msi_page)
		return -ENOMEM;
	return 0;
}