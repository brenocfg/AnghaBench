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
struct isp_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void isp_detach_iommu(struct isp_device *isp)
{
#ifdef CONFIG_ARM_DMA_USE_IOMMU
	arm_iommu_detach_device(isp->dev);
	arm_iommu_release_mapping(isp->mapping);
	isp->mapping = NULL;
#endif
}