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
struct iommu_ops {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dma_direct_ops ; 
 int /*<<< orphan*/  dma_noncoherent_ops ; 
 scalar_t__ ioc_enable ; 
 scalar_t__ is_isa_arcv2 () ; 
 int /*<<< orphan*/  set_dma_ops (struct device*,int /*<<< orphan*/ *) ; 

void arch_setup_dma_ops(struct device *dev, u64 dma_base, u64 size,
			const struct iommu_ops *iommu, bool coherent)
{
	/*
	 * IOC hardware snoops all DMA traffic keeping the caches consistent
	 * with memory - eliding need for any explicit cache maintenance of
	 * DMA buffers - so we can use dma_direct cache ops.
	 */
	if (is_isa_arcv2() && ioc_enable && coherent) {
		set_dma_ops(dev, &dma_direct_ops);
		dev_info(dev, "use dma_direct_ops cache ops\n");
	} else {
		set_dma_ops(dev, &dma_noncoherent_ops);
		dev_info(dev, "use dma_noncoherent_ops cache ops\n");
	}
}