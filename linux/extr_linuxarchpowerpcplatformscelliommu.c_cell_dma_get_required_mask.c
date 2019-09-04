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
typedef  int /*<<< orphan*/  u64 ;
struct dma_map_ops {int /*<<< orphan*/  (* get_required_mask ) (struct device*) ;} ;
struct device {int /*<<< orphan*/  dma_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 scalar_t__ OF_BAD_ADDR ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,struct dma_map_ops const*) ; 
 scalar_t__ cell_iommu_get_fixed_address (struct device*) ; 
 struct dma_map_ops* get_dma_ops (struct device*) ; 
 int /*<<< orphan*/  iommu_fixed_disabled ; 
 int /*<<< orphan*/  stub1 (struct device*) ; 

__attribute__((used)) static u64 cell_dma_get_required_mask(struct device *dev)
{
	const struct dma_map_ops *dma_ops;

	if (!dev->dma_mask)
		return 0;

	if (!iommu_fixed_disabled &&
			cell_iommu_get_fixed_address(dev) != OF_BAD_ADDR)
		return DMA_BIT_MASK(64);

	dma_ops = get_dma_ops(dev);
	if (dma_ops->get_required_mask)
		return dma_ops->get_required_mask(dev);

	WARN_ONCE(1, "no get_required_mask in %p ops", dma_ops);

	return DMA_BIT_MASK(64);
}