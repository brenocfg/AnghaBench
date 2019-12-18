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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int IOMMU_MMIO ; 
 int /*<<< orphan*/  __iommu_dma_map (struct device*,int /*<<< orphan*/ ,size_t,int) ; 
 int dma_info_to_prot (int,int,unsigned long) ; 

__attribute__((used)) static dma_addr_t iommu_dma_map_resource(struct device *dev, phys_addr_t phys,
		size_t size, enum dma_data_direction dir, unsigned long attrs)
{
	return __iommu_dma_map(dev, phys, size,
			dma_info_to_prot(dir, false, attrs) | IOMMU_MMIO);
}