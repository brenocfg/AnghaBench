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
struct kfd_local_mem_info {scalar_t__ local_mem_size_private; scalar_t__ local_mem_size_public; } ;
struct kfd_dev {int /*<<< orphan*/  kgd; TYPE_1__* device_info; } ;
struct TYPE_2__ {scalar_t__ needs_iommu_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_amdkfd_get_local_mem_info (int /*<<< orphan*/ ,struct kfd_local_mem_info*) ; 
 scalar_t__ debug_largebar ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

bool kfd_dev_is_large_bar(struct kfd_dev *dev)
{
	struct kfd_local_mem_info mem_info;

	if (debug_largebar) {
		pr_debug("Simulate large-bar allocation on non large-bar machine\n");
		return true;
	}

	if (dev->device_info->needs_iommu_device)
		return false;

	amdgpu_amdkfd_get_local_mem_info(dev->kgd, &mem_info);
	if (mem_info.local_mem_size_private == 0 &&
			mem_info.local_mem_size_public > 0)
		return true;
	return false;
}