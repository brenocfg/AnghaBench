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
typedef  size_t dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iommu_dma_free_iova (struct iommu_dma_cookie*,size_t,size_t) ; 
 size_t iommu_unmap (struct iommu_domain*,size_t,size_t) ; 
 size_t iova_align (struct iova_domain*,size_t) ; 
 size_t iova_offset (struct iova_domain*,size_t) ; 

__attribute__((used)) static void __iommu_dma_unmap(struct iommu_domain *domain, dma_addr_t dma_addr,
		size_t size)
{
	struct iommu_dma_cookie *cookie = domain->iova_cookie;
	struct iova_domain *iovad = &cookie->iovad;
	size_t iova_off = iova_offset(iovad, dma_addr);

	dma_addr -= iova_off;
	size = iova_align(iovad, size + iova_off);

	WARN_ON(iommu_unmap(domain, dma_addr, size) != size);
	iommu_dma_free_iova(cookie, dma_addr, size);
}