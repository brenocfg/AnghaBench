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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 unsigned long DMA_ATTR_SKIP_CPU_SYNC ; 
 int /*<<< orphan*/  __dma_map_area (int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  dma_to_phys (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_device_dma_coherent (struct device*) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swiotlb_map_page (struct device*,struct page*,unsigned long,size_t,int,unsigned long) ; 

__attribute__((used)) static dma_addr_t __swiotlb_map_page(struct device *dev, struct page *page,
				     unsigned long offset, size_t size,
				     enum dma_data_direction dir,
				     unsigned long attrs)
{
	dma_addr_t dev_addr;

	dev_addr = swiotlb_map_page(dev, page, offset, size, dir, attrs);
	if (!is_device_dma_coherent(dev) &&
	    (attrs & DMA_ATTR_SKIP_CPU_SYNC) == 0)
		__dma_map_area(phys_to_virt(dma_to_phys(dev, dev_addr)), size, dir);

	return dev_addr;
}