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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  scalar_t__ phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 scalar_t__ DMA_MAPPING_ERROR ; 
 scalar_t__ __iommu_dma_map (struct device*,scalar_t__,size_t,int) ; 
 int /*<<< orphan*/  arch_sync_dma_for_device (struct device*,scalar_t__,size_t,int) ; 
 int dev_is_dma_coherent (struct device*) ; 
 int dma_info_to_prot (int,int,unsigned long) ; 
 scalar_t__ page_to_phys (struct page*) ; 

__attribute__((used)) static dma_addr_t iommu_dma_map_page(struct device *dev, struct page *page,
		unsigned long offset, size_t size, enum dma_data_direction dir,
		unsigned long attrs)
{
	phys_addr_t phys = page_to_phys(page) + offset;
	bool coherent = dev_is_dma_coherent(dev);
	int prot = dma_info_to_prot(dir, coherent, attrs);
	dma_addr_t dma_handle;

	dma_handle =__iommu_dma_map(dev, phys, size, prot);
	if (!coherent && !(attrs & DMA_ATTR_SKIP_CPU_SYNC) &&
	    dma_handle != DMA_MAPPING_ERROR)
		arch_sync_dma_for_device(dev, phys, size, dir);
	return dma_handle;
}