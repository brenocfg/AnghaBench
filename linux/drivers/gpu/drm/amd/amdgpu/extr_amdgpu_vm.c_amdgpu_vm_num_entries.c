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
struct TYPE_2__ {unsigned int root_level; int /*<<< orphan*/  max_pfn; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 unsigned int AMDGPU_VM_PTB ; 
 int AMDGPU_VM_PTE_COUNT (struct amdgpu_device*) ; 
 unsigned int amdgpu_vm_level_shift (struct amdgpu_device*,unsigned int) ; 
 unsigned int round_up (int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static unsigned amdgpu_vm_num_entries(struct amdgpu_device *adev,
				      unsigned level)
{
	unsigned shift = amdgpu_vm_level_shift(adev,
					       adev->vm_manager.root_level);

	if (level == adev->vm_manager.root_level)
		/* For the root directory */
		return round_up(adev->vm_manager.max_pfn, 1ULL << shift) >> shift;
	else if (level != AMDGPU_VM_PTB)
		/* Everything in between */
		return 512;
	else
		/* For the page tables on the leaves */
		return AMDGPU_VM_PTE_COUNT(adev);
}