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
struct msi_msg {int address_lo; int /*<<< orphan*/  address_hi; } ;
struct msi_desc {int dummy; } ;
struct iommu_domain {int /*<<< orphan*/  iova_cookie; } ;
struct iommu_dma_msi_page {int /*<<< orphan*/  iova; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int cookie_msi_granule (int /*<<< orphan*/ ) ; 
 struct iommu_domain* iommu_get_domain_for_dev (struct device*) ; 
 scalar_t__ lower_32_bits (int /*<<< orphan*/ ) ; 
 struct iommu_dma_msi_page* msi_desc_get_iommu_cookie (struct msi_desc*) ; 
 struct device* msi_desc_to_dev (struct msi_desc*) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

void iommu_dma_compose_msi_msg(struct msi_desc *desc,
			       struct msi_msg *msg)
{
	struct device *dev = msi_desc_to_dev(desc);
	const struct iommu_domain *domain = iommu_get_domain_for_dev(dev);
	const struct iommu_dma_msi_page *msi_page;

	msi_page = msi_desc_get_iommu_cookie(desc);

	if (!domain || !domain->iova_cookie || WARN_ON(!msi_page))
		return;

	msg->address_hi = upper_32_bits(msi_page->iova);
	msg->address_lo &= cookie_msi_granule(domain->iova_cookie) - 1;
	msg->address_lo += lower_32_bits(msi_page->iova);
}