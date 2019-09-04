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
typedef  int u64 ;
struct msi_msg {unsigned int address_hi; int address_lo; unsigned int data; } ;
struct iommu_domain {struct iommu_dma_cookie* iova_cookie; } ;
struct iommu_dma_msi_page {int /*<<< orphan*/  iova; } ;
struct iommu_dma_cookie {int /*<<< orphan*/  msi_lock; } ;
struct device {int dummy; } ;
typedef  int phys_addr_t ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int cookie_msi_granule (struct iommu_dma_cookie*) ; 
 struct iommu_dma_msi_page* iommu_dma_get_msi_page (struct device*,int,struct iommu_domain*) ; 
 struct iommu_domain* iommu_get_domain_for_dev (struct device*) ; 
 int /*<<< orphan*/  irq_get_msi_desc (int) ; 
 scalar_t__ lower_32_bits (int /*<<< orphan*/ ) ; 
 struct device* msi_desc_to_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned int upper_32_bits (int /*<<< orphan*/ ) ; 

void iommu_dma_map_msi_msg(int irq, struct msi_msg *msg)
{
	struct device *dev = msi_desc_to_dev(irq_get_msi_desc(irq));
	struct iommu_domain *domain = iommu_get_domain_for_dev(dev);
	struct iommu_dma_cookie *cookie;
	struct iommu_dma_msi_page *msi_page;
	phys_addr_t msi_addr = (u64)msg->address_hi << 32 | msg->address_lo;
	unsigned long flags;

	if (!domain || !domain->iova_cookie)
		return;

	cookie = domain->iova_cookie;

	/*
	 * We disable IRQs to rule out a possible inversion against
	 * irq_desc_lock if, say, someone tries to retarget the affinity
	 * of an MSI from within an IPI handler.
	 */
	spin_lock_irqsave(&cookie->msi_lock, flags);
	msi_page = iommu_dma_get_msi_page(dev, msi_addr, domain);
	spin_unlock_irqrestore(&cookie->msi_lock, flags);

	if (WARN_ON(!msi_page)) {
		/*
		 * We're called from a void callback, so the best we can do is
		 * 'fail' by filling the message with obviously bogus values.
		 * Since we got this far due to an IOMMU being present, it's
		 * not like the existing address would have worked anyway...
		 */
		msg->address_hi = ~0U;
		msg->address_lo = ~0U;
		msg->data = ~0U;
	} else {
		msg->address_hi = upper_32_bits(msi_page->iova);
		msg->address_lo &= cookie_msi_granule(cookie) - 1;
		msg->address_lo += lower_32_bits(msi_page->iova);
	}
}