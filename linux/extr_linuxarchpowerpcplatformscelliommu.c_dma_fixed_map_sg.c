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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int (* map_sg ) (struct device*,struct scatterlist*,int,int,unsigned long) ;} ;

/* Variables and functions */
 unsigned long DMA_ATTR_WEAK_ORDERING ; 
 int /*<<< orphan*/  cell_get_iommu_table (struct device*) ; 
 int /*<<< orphan*/  device_to_mask (struct device*) ; 
 TYPE_1__ dma_nommu_ops ; 
 unsigned long iommu_fixed_is_weak ; 
 int ppc_iommu_map_sg (struct device*,int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ,int,unsigned long) ; 
 int stub1 (struct device*,struct scatterlist*,int,int,unsigned long) ; 

__attribute__((used)) static int dma_fixed_map_sg(struct device *dev, struct scatterlist *sg,
			   int nents, enum dma_data_direction direction,
			   unsigned long attrs)
{
	if (iommu_fixed_is_weak == (attrs & DMA_ATTR_WEAK_ORDERING))
		return dma_nommu_ops.map_sg(dev, sg, nents, direction, attrs);
	else
		return ppc_iommu_map_sg(dev, cell_get_iommu_table(dev), sg,
					nents, device_to_mask(dev),
					direction, attrs);
}