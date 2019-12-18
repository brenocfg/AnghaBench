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
struct iommu_iotlb_gather {int dummy; } ;
struct iommu_domain {struct iommu_dma_cookie* iova_cookie; } ;
struct iommu_dma_cookie {int /*<<< orphan*/  fq_domain; struct iova_domain iovad; } ;
struct device {int dummy; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iommu_dma_free_iova (struct iommu_dma_cookie*,size_t,size_t) ; 
 struct iommu_domain* iommu_get_dma_domain (struct device*) ; 
 int /*<<< orphan*/  iommu_iotlb_gather_init (struct iommu_iotlb_gather*) ; 
 int /*<<< orphan*/  iommu_tlb_sync (struct iommu_domain*,struct iommu_iotlb_gather*) ; 
 size_t iommu_unmap_fast (struct iommu_domain*,size_t,size_t,struct iommu_iotlb_gather*) ; 
 size_t iova_align (struct iova_domain*,size_t) ; 
 size_t iova_offset (struct iova_domain*,size_t) ; 

__attribute__((used)) static void __iommu_dma_unmap(struct device *dev, dma_addr_t dma_addr,
		size_t size)
{
	struct iommu_domain *domain = iommu_get_dma_domain(dev);
	struct iommu_dma_cookie *cookie = domain->iova_cookie;
	struct iova_domain *iovad = &cookie->iovad;
	size_t iova_off = iova_offset(iovad, dma_addr);
	struct iommu_iotlb_gather iotlb_gather;
	size_t unmapped;

	dma_addr -= iova_off;
	size = iova_align(iovad, size + iova_off);
	iommu_iotlb_gather_init(&iotlb_gather);

	unmapped = iommu_unmap_fast(domain, dma_addr, size, &iotlb_gather);
	WARN_ON(unmapped != size);

	if (!cookie->fq_domain)
		iommu_tlb_sync(domain, &iotlb_gather);
	iommu_dma_free_iova(cookie, dma_addr, size);
}