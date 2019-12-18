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
struct dmar_domain {int /*<<< orphan*/  domain; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 size_t ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTD_PAGE_SIZE ; 
 scalar_t__ WARN_ON (int) ; 
 struct dmar_domain* find_domain (struct device*) ; 
 int /*<<< orphan*/  intel_iommu_iova_to_phys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_unmap (struct device*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ is_swiotlb_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swiotlb_tbl_unmap_single (struct device*,int /*<<< orphan*/ ,size_t,size_t,int,unsigned long) ; 
 int /*<<< orphan*/  trace_bounce_unmap_single (struct device*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
bounce_unmap_single(struct device *dev, dma_addr_t dev_addr, size_t size,
		    enum dma_data_direction dir, unsigned long attrs)
{
	size_t aligned_size = ALIGN(size, VTD_PAGE_SIZE);
	struct dmar_domain *domain;
	phys_addr_t tlb_addr;

	domain = find_domain(dev);
	if (WARN_ON(!domain))
		return;

	tlb_addr = intel_iommu_iova_to_phys(&domain->domain, dev_addr);
	if (WARN_ON(!tlb_addr))
		return;

	intel_unmap(dev, dev_addr, size);
	if (is_swiotlb_buffer(tlb_addr))
		swiotlb_tbl_unmap_single(dev, tlb_addr, size,
					 aligned_size, dir, attrs);

	trace_bounce_unmap_single(dev, dev_addr, size);
}