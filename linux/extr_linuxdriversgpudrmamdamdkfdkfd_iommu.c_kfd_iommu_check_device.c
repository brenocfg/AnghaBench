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
struct kfd_dev {int /*<<< orphan*/  pdev; TYPE_1__* device_info; } ;
struct amd_iommu_device_info {int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  needs_iommu_device; } ;

/* Variables and functions */
 int ENODEV ; 
 int amd_iommu_device_info (int /*<<< orphan*/ ,struct amd_iommu_device_info*) ; 
 int required_iommu_flags ; 

int kfd_iommu_check_device(struct kfd_dev *kfd)
{
	struct amd_iommu_device_info iommu_info;
	int err;

	if (!kfd->device_info->needs_iommu_device)
		return -ENODEV;

	iommu_info.flags = 0;
	err = amd_iommu_device_info(kfd->pdev, &iommu_info);
	if (err)
		return err;

	if ((iommu_info.flags & required_iommu_flags) != required_iommu_flags)
		return -ENODEV;

	return 0;
}