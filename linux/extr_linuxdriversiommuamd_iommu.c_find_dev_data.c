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
typedef  size_t u16 ;
struct iommu_dev_data {int defer_attach; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 struct iommu_dev_data* alloc_dev_data (size_t) ; 
 struct amd_iommu** amd_iommu_rlookup_table ; 
 struct iommu_dev_data* search_dev_data (size_t) ; 
 scalar_t__ translation_pre_enabled (struct amd_iommu*) ; 

__attribute__((used)) static struct iommu_dev_data *find_dev_data(u16 devid)
{
	struct iommu_dev_data *dev_data;
	struct amd_iommu *iommu = amd_iommu_rlookup_table[devid];

	dev_data = search_dev_data(devid);

	if (dev_data == NULL) {
		dev_data = alloc_dev_data(devid);
		if (!dev_data)
			return NULL;

		if (translation_pre_enabled(iommu))
			dev_data->defer_attach = true;
	}

	return dev_data;
}