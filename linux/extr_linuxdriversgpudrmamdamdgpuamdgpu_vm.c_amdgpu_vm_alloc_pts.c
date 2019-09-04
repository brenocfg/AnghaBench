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
typedef  int uint64_t ;
struct amdgpu_vm {int /*<<< orphan*/  root; scalar_t__ pte_support_ats; } ;
struct TYPE_2__ {int max_pfn; int /*<<< orphan*/  root_level; } ;
struct amdgpu_device {TYPE_1__ vm_manager; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_MASK ; 
 int AMDGPU_GPU_PAGE_SIZE ; 
 int AMDGPU_VA_HOLE_START ; 
 int EINVAL ; 
 int amdgpu_vm_alloc_levels (struct amdgpu_device*,struct amdgpu_vm*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 

int amdgpu_vm_alloc_pts(struct amdgpu_device *adev,
			struct amdgpu_vm *vm,
			uint64_t saddr, uint64_t size)
{
	uint64_t eaddr;
	bool ats = false;

	/* validate the parameters */
	if (saddr & AMDGPU_GPU_PAGE_MASK || size & AMDGPU_GPU_PAGE_MASK)
		return -EINVAL;

	eaddr = saddr + size - 1;

	if (vm->pte_support_ats)
		ats = saddr < AMDGPU_VA_HOLE_START;

	saddr /= AMDGPU_GPU_PAGE_SIZE;
	eaddr /= AMDGPU_GPU_PAGE_SIZE;

	if (eaddr >= adev->vm_manager.max_pfn) {
		dev_err(adev->dev, "va above limit (0x%08llX >= 0x%08llX)\n",
			eaddr, adev->vm_manager.max_pfn);
		return -EINVAL;
	}

	return amdgpu_vm_alloc_levels(adev, vm, &vm->root, saddr, eaddr,
				      adev->vm_manager.root_level, ats);
}