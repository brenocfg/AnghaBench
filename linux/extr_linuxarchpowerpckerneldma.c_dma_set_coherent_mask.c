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
struct device {int /*<<< orphan*/  coherent_dma_mask; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dma_iommu_dma_supported (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_nommu_ops ; 
 int /*<<< orphan*/  dma_supported (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_dma_ops (struct device*) ; 
 int /*<<< orphan*/ * get_iommu_table_base (struct device*) ; 

int dma_set_coherent_mask(struct device *dev, u64 mask)
{
	if (!dma_supported(dev, mask)) {
		/*
		 * We need to special case the direct DMA ops which can
		 * support a fallback for coherent allocations. There
		 * is no dma_op->set_coherent_mask() so we have to do
		 * things the hard way:
		 */
		if (get_dma_ops(dev) != &dma_nommu_ops ||
		    get_iommu_table_base(dev) == NULL ||
		    !dma_iommu_dma_supported(dev, mask))
			return -EIO;
	}
	dev->coherent_dma_mask = mask;
	return 0;
}