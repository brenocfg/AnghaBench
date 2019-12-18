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
struct iova_domain {int dummy; } ;
struct iommu_domain {struct iommu_dma_cookie* iova_cookie; } ;
struct iommu_dma_cookie {struct iova_domain iovad; } ;
struct device {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA_MAPPING_ERROR ; 
 int /*<<< orphan*/  dma_get_mask (struct device*) ; 
 scalar_t__ iommu_dma_alloc_iova (struct iommu_domain*,size_t,int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  iommu_dma_free_iova (struct iommu_dma_cookie*,scalar_t__,size_t) ; 
 struct iommu_domain* iommu_get_dma_domain (struct device*) ; 
 scalar_t__ iommu_map (struct iommu_domain*,scalar_t__,scalar_t__,size_t,int) ; 
 size_t iova_align (struct iova_domain*,size_t) ; 
 size_t iova_offset (struct iova_domain*,scalar_t__) ; 

__attribute__((used)) static dma_addr_t __iommu_dma_map(struct device *dev, phys_addr_t phys,
		size_t size, int prot)
{
	struct iommu_domain *domain = iommu_get_dma_domain(dev);
	struct iommu_dma_cookie *cookie = domain->iova_cookie;
	struct iova_domain *iovad = &cookie->iovad;
	size_t iova_off = iova_offset(iovad, phys);
	dma_addr_t iova;

	size = iova_align(iovad, size + iova_off);

	iova = iommu_dma_alloc_iova(domain, size, dma_get_mask(dev), dev);
	if (!iova)
		return DMA_MAPPING_ERROR;

	if (iommu_map(domain, iova, phys - iova_off, size, prot)) {
		iommu_dma_free_iova(cookie, iova, size);
		return DMA_MAPPING_ERROR;
	}
	return iova + iova_off;
}