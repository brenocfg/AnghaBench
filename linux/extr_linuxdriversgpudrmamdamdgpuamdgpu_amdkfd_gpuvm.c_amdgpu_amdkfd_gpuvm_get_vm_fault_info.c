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
struct kgd_dev {int dummy; } ;
struct kfd_vm_fault_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vm_fault_info_updated; struct kfd_vm_fault_info* vm_fault_info; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

int amdgpu_amdkfd_gpuvm_get_vm_fault_info(struct kgd_dev *kgd,
					      struct kfd_vm_fault_info *mem)
{
	struct amdgpu_device *adev;

	adev = (struct amdgpu_device *)kgd;
	if (atomic_read(&adev->gmc.vm_fault_info_updated) == 1) {
		*mem = *adev->gmc.vm_fault_info;
		mb();
		atomic_set(&adev->gmc.vm_fault_info_updated, 0);
	}
	return 0;
}