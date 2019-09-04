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
struct TYPE_2__ {int /*<<< orphan*/  dma_ops_setup; } ;
struct device {TYPE_1__ archdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  arm_teardown_iommu_dma_ops (struct device*) ; 
 int /*<<< orphan*/  set_dma_ops (struct device*,int /*<<< orphan*/ *) ; 

void arch_teardown_dma_ops(struct device *dev)
{
	if (!dev->archdata.dma_ops_setup)
		return;

	arm_teardown_iommu_dma_ops(dev);
	/* Let arch_setup_dma_ops() start again from scratch upon re-probe */
	set_dma_ops(dev, NULL);
}