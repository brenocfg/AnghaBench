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
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ enabled; } ;
struct iommu_dev_data {size_t devid; scalar_t__ alias; TYPE_1__ ats; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int device_flush_iotlb (struct iommu_dev_data*,int /*<<< orphan*/ ,unsigned long) ; 
 int iommu_flush_dte (struct amd_iommu*,scalar_t__) ; 

__attribute__((used)) static int device_flush_dte(struct iommu_dev_data *dev_data)
{
	struct amd_iommu *iommu;
	u16 alias;
	int ret;

	iommu = amd_iommu_rlookup_table[dev_data->devid];
	alias = dev_data->alias;

	ret = iommu_flush_dte(iommu, dev_data->devid);
	if (!ret && alias != dev_data->devid)
		ret = iommu_flush_dte(iommu, alias);
	if (ret)
		return ret;

	if (dev_data->ats.enabled)
		ret = device_flush_iotlb(dev_data, 0, ~0UL);

	return ret;
}