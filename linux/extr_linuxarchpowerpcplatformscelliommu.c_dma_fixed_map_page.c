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
struct page {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* map_page ) (struct device*,struct page*,unsigned long,size_t,int,unsigned long) ;} ;

/* Variables and functions */
 unsigned long DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  cell_get_iommu_table (struct device*) ; 
 int /*<<< orphan*/  device_to_mask (struct device*) ; 
 TYPE_1__ dma_nommu_ops ; 
 unsigned long iommu_fixed_is_weak ; 
 int /*<<< orphan*/  iommu_map_page (struct device*,int /*<<< orphan*/ ,struct page*,unsigned long,size_t,int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct device*,struct page*,unsigned long,size_t,int,unsigned long) ; 

__attribute__((used)) static dma_addr_t dma_fixed_map_page(struct device *dev, struct page *page,
				     unsigned long offset, size_t size,
				     enum dma_data_direction direction,
				     unsigned long attrs)
{
	if (iommu_fixed_is_weak == (attrs & DMA_ATTR_WEAK_ORDERING))
		return dma_nommu_ops.map_page(dev, page, offset, size,
					       direction, attrs);
	else
		return iommu_map_page(dev, cell_get_iommu_table(dev), page,
				      offset, size, device_to_mask(dev),
				      direction, attrs);
}