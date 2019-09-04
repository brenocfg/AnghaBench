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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int qdep; } ;
struct iommu_dev_data {size_t devid; TYPE_1__ ats; } ;
struct iommu_cmd {int dummy; } ;
struct amd_iommu {int dummy; } ;

/* Variables and functions */
 struct amd_iommu** amd_iommu_rlookup_table ; 
 int /*<<< orphan*/  build_inv_iotlb_pages (struct iommu_cmd*,size_t,int,int /*<<< orphan*/ ,size_t) ; 
 int iommu_queue_command (struct amd_iommu*,struct iommu_cmd*) ; 

__attribute__((used)) static int device_flush_iotlb(struct iommu_dev_data *dev_data,
			      u64 address, size_t size)
{
	struct amd_iommu *iommu;
	struct iommu_cmd cmd;
	int qdep;

	qdep     = dev_data->ats.qdep;
	iommu    = amd_iommu_rlookup_table[dev_data->devid];

	build_inv_iotlb_pages(&cmd, dev_data->devid, qdep, address, size);

	return iommu_queue_command(iommu, &cmd);
}