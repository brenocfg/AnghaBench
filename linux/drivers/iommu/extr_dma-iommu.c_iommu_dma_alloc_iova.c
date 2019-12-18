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
struct iova_domain {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  aperture_end; scalar_t__ force_aperture; } ;
struct iommu_domain {TYPE_1__ geometry; struct iommu_dma_cookie* iova_cookie; } ;
struct iommu_dma_cookie {scalar_t__ type; unsigned long msi_iova; struct iova_domain iovad; } ;
struct device {int bus_dma_mask; } ;
typedef  unsigned long dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_BIT_MASK (int) ; 
 scalar_t__ IOMMU_DMA_MSI_COOKIE ; 
 int IOVA_RANGE_CACHE_MAX_SIZE ; 
 unsigned long alloc_iova_fast (struct iova_domain*,unsigned long,unsigned long,int) ; 
 scalar_t__ dev_is_pci (struct device*) ; 
 unsigned long iova_shift (struct iova_domain*) ; 
 unsigned long min (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long roundup_pow_of_two (unsigned long) ; 

__attribute__((used)) static dma_addr_t iommu_dma_alloc_iova(struct iommu_domain *domain,
		size_t size, dma_addr_t dma_limit, struct device *dev)
{
	struct iommu_dma_cookie *cookie = domain->iova_cookie;
	struct iova_domain *iovad = &cookie->iovad;
	unsigned long shift, iova_len, iova = 0;

	if (cookie->type == IOMMU_DMA_MSI_COOKIE) {
		cookie->msi_iova += size;
		return cookie->msi_iova - size;
	}

	shift = iova_shift(iovad);
	iova_len = size >> shift;
	/*
	 * Freeing non-power-of-two-sized allocations back into the IOVA caches
	 * will come back to bite us badly, so we have to waste a bit of space
	 * rounding up anything cacheable to make sure that can't happen. The
	 * order of the unadjusted size will still match upon freeing.
	 */
	if (iova_len < (1 << (IOVA_RANGE_CACHE_MAX_SIZE - 1)))
		iova_len = roundup_pow_of_two(iova_len);

	if (dev->bus_dma_mask)
		dma_limit &= dev->bus_dma_mask;

	if (domain->geometry.force_aperture)
		dma_limit = min(dma_limit, domain->geometry.aperture_end);

	/* Try to get PCI devices a SAC address */
	if (dma_limit > DMA_BIT_MASK(32) && dev_is_pci(dev))
		iova = alloc_iova_fast(iovad, iova_len,
				       DMA_BIT_MASK(32) >> shift, false);

	if (!iova)
		iova = alloc_iova_fast(iovad, iova_len, dma_limit >> shift,
				       true);

	return (dma_addr_t)iova << shift;
}