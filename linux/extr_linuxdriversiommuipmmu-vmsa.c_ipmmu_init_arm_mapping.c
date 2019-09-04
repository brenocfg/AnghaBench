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
struct ipmmu_vmsa_device {struct iommu_group* mapping; struct device* dev; } ;
struct iommu_group {int dummy; } ;
typedef  struct iommu_group dma_iommu_mapping ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct iommu_group*) ; 
 int PTR_ERR (struct iommu_group*) ; 
 int /*<<< orphan*/  SZ_1G ; 
 int /*<<< orphan*/  SZ_2G ; 
 int arm_iommu_attach_device (struct device*,struct iommu_group*) ; 
 struct iommu_group* arm_iommu_create_mapping (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_iommu_release_mapping (struct iommu_group*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int iommu_group_add_device (struct iommu_group*,struct device*) ; 
 struct iommu_group* iommu_group_alloc () ; 
 int /*<<< orphan*/  iommu_group_put (struct iommu_group*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 struct ipmmu_vmsa_device* to_ipmmu (struct device*) ; 

__attribute__((used)) static int ipmmu_init_arm_mapping(struct device *dev)
{
	struct ipmmu_vmsa_device *mmu = to_ipmmu(dev);
	struct iommu_group *group;
	int ret;

	/* Create a device group and add the device to it. */
	group = iommu_group_alloc();
	if (IS_ERR(group)) {
		dev_err(dev, "Failed to allocate IOMMU group\n");
		return PTR_ERR(group);
	}

	ret = iommu_group_add_device(group, dev);
	iommu_group_put(group);

	if (ret < 0) {
		dev_err(dev, "Failed to add device to IPMMU group\n");
		return ret;
	}

	/*
	 * Create the ARM mapping, used by the ARM DMA mapping core to allocate
	 * VAs. This will allocate a corresponding IOMMU domain.
	 *
	 * TODO:
	 * - Create one mapping per context (TLB).
	 * - Make the mapping size configurable ? We currently use a 2GB mapping
	 *   at a 1GB offset to ensure that NULL VAs will fault.
	 */
	if (!mmu->mapping) {
		struct dma_iommu_mapping *mapping;

		mapping = arm_iommu_create_mapping(&platform_bus_type,
						   SZ_1G, SZ_2G);
		if (IS_ERR(mapping)) {
			dev_err(mmu->dev, "failed to create ARM IOMMU mapping\n");
			ret = PTR_ERR(mapping);
			goto error;
		}

		mmu->mapping = mapping;
	}

	/* Attach the ARM VA mapping to the device. */
	ret = arm_iommu_attach_device(dev, mmu->mapping);
	if (ret < 0) {
		dev_err(dev, "Failed to attach device to VA mapping\n");
		goto error;
	}

	return 0;

error:
	iommu_group_remove_device(dev);
	if (mmu->mapping)
		arm_iommu_release_mapping(mmu->mapping);

	return ret;
}