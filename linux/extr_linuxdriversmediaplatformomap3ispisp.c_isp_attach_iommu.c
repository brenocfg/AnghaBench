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
 int ENODEV ; 

__attribute__((used)) static int isp_attach_iommu(struct isp_device *isp)
{
#ifdef CONFIG_ARM_DMA_USE_IOMMU
	struct dma_iommu_mapping *mapping;
	int ret;

	/*
	 * Create the ARM mapping, used by the ARM DMA mapping core to allocate
	 * VAs. This will allocate a corresponding IOMMU domain.
	 */
	mapping = arm_iommu_create_mapping(&platform_bus_type, SZ_1G, SZ_2G);
	if (IS_ERR(mapping)) {
		dev_err(isp->dev, "failed to create ARM IOMMU mapping\n");
		return PTR_ERR(mapping);
	}

	isp->mapping = mapping;

	/* Attach the ARM VA mapping to the device. */
	ret = arm_iommu_attach_device(isp->dev, mapping);
	if (ret < 0) {
		dev_err(isp->dev, "failed to attach device to VA mapping\n");
		goto error;
	}

	return 0;

error:
	arm_iommu_release_mapping(isp->mapping);
	isp->mapping = NULL;
	return ret;
#else
	return -ENODEV;
#endif
}