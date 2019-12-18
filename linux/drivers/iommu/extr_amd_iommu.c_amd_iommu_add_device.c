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
struct iommu_domain {scalar_t__ type; } ;
struct iommu_dev_data {int passthrough; scalar_t__ iommu_v2; } ;
struct device {int /*<<< orphan*/ * dma_ops; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOTSUPP ; 
 scalar_t__ IOMMU_DOMAIN_IDENTITY ; 
 int /*<<< orphan*/  amd_iommu_dma_ops ; 
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  check_device (struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct iommu_dev_data* get_dev_data (struct device*) ; 
 int get_device_id (struct device*) ; 
 int /*<<< orphan*/  init_iommu_group (struct device*) ; 
 int /*<<< orphan*/  iommu_completion_wait (struct amd_iommu*) ; 
 struct iommu_domain* iommu_get_domain_for_dev (struct device*) ; 
 int /*<<< orphan*/  iommu_ignore_device (struct device*) ; 
 int iommu_init_device (struct device*) ; 
 int /*<<< orphan*/  iommu_request_dm_for_dev (struct device*) ; 

__attribute__((used)) static int amd_iommu_add_device(struct device *dev)
{
	struct iommu_dev_data *dev_data;
	struct iommu_domain *domain;
	struct amd_iommu *iommu;
	int ret, devid;

	if (!check_device(dev) || get_dev_data(dev))
		return 0;

	devid = get_device_id(dev);
	if (devid < 0)
		return devid;

	iommu = amd_iommu_rlookup_table[devid];

	ret = iommu_init_device(dev);
	if (ret) {
		if (ret != -ENOTSUPP)
			dev_err(dev, "Failed to initialize - trying to proceed anyway\n");

		iommu_ignore_device(dev);
		dev->dma_ops = NULL;
		goto out;
	}
	init_iommu_group(dev);

	dev_data = get_dev_data(dev);

	BUG_ON(!dev_data);

	if (dev_data->iommu_v2)
		iommu_request_dm_for_dev(dev);

	/* Domains are initialized for this device - have a look what we ended up with */
	domain = iommu_get_domain_for_dev(dev);
	if (domain->type == IOMMU_DOMAIN_IDENTITY)
		dev_data->passthrough = true;
	else
		dev->dma_ops = &amd_iommu_dma_ops;

out:
	iommu_completion_wait(iommu);

	return 0;
}