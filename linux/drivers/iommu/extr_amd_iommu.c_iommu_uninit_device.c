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
struct iommu_dev_data {scalar_t__ domain; } ;
struct device {int /*<<< orphan*/ * dma_ops; } ;
struct amd_iommu {int /*<<< orphan*/  iommu; } ;

/* Variables and functions */
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  detach_device (struct device*) ; 
 int get_device_id (struct device*) ; 
 int /*<<< orphan*/  iommu_device_unlink (int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  iommu_group_remove_device (struct device*) ; 
 struct iommu_dev_data* search_dev_data (int) ; 

__attribute__((used)) static void iommu_uninit_device(struct device *dev)
{
	struct iommu_dev_data *dev_data;
	struct amd_iommu *iommu;
	int devid;

	devid = get_device_id(dev);
	if (devid < 0)
		return;

	iommu = amd_iommu_rlookup_table[devid];

	dev_data = search_dev_data(devid);
	if (!dev_data)
		return;

	if (dev_data->domain)
		detach_device(dev);

	iommu_device_unlink(&iommu->iommu, dev);

	iommu_group_remove_device(dev);

	/* Remove dma-ops */
	dev->dma_ops = NULL;

	/*
	 * We keep dev_data around for unplugged devices and reuse it when the
	 * device is re-plugged - not doing so would introduce a ton of races.
	 */
}