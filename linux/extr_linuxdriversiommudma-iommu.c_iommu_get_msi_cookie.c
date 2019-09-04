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
struct iommu_domain {scalar_t__ type; struct iommu_dma_cookie* iova_cookie; } ;
struct iommu_dma_cookie {int /*<<< orphan*/  msi_iova; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IOMMU_DMA_MSI_COOKIE ; 
 scalar_t__ IOMMU_DOMAIN_UNMANAGED ; 
 struct iommu_dma_cookie* cookie_alloc (int /*<<< orphan*/ ) ; 

int iommu_get_msi_cookie(struct iommu_domain *domain, dma_addr_t base)
{
	struct iommu_dma_cookie *cookie;

	if (domain->type != IOMMU_DOMAIN_UNMANAGED)
		return -EINVAL;

	if (domain->iova_cookie)
		return -EEXIST;

	cookie = cookie_alloc(IOMMU_DMA_MSI_COOKIE);
	if (!cookie)
		return -ENOMEM;

	cookie->msi_iova = base;
	domain->iova_cookie = cookie;
	return 0;
}