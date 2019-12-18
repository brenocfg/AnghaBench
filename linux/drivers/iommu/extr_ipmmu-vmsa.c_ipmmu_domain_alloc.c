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
struct iommu_domain {int dummy; } ;

/* Variables and functions */
#define  IOMMU_DOMAIN_DMA 129 
#define  IOMMU_DOMAIN_UNMANAGED 128 
 struct iommu_domain* __ipmmu_domain_alloc (unsigned int) ; 
 int /*<<< orphan*/  iommu_get_dma_cookie (struct iommu_domain*) ; 
 int /*<<< orphan*/  kfree (struct iommu_domain*) ; 

__attribute__((used)) static struct iommu_domain *ipmmu_domain_alloc(unsigned type)
{
	struct iommu_domain *io_domain = NULL;

	switch (type) {
	case IOMMU_DOMAIN_UNMANAGED:
		io_domain = __ipmmu_domain_alloc(type);
		break;

	case IOMMU_DOMAIN_DMA:
		io_domain = __ipmmu_domain_alloc(type);
		if (io_domain && iommu_get_dma_cookie(io_domain)) {
			kfree(io_domain);
			io_domain = NULL;
		}
		break;
	}

	return io_domain;
}