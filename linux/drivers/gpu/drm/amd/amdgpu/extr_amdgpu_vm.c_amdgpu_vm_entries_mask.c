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
typedef  int uint32_t ;
struct TYPE_2__ {unsigned int root_level; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 unsigned int AMDGPU_VM_PTB ; 
 int AMDGPU_VM_PTE_COUNT (struct amdgpu_device*) ; 

__attribute__((used)) static uint32_t amdgpu_vm_entries_mask(struct amdgpu_device *adev,
				       unsigned int level)
{
	if (level <= adev->vm_manager.root_level)
		return 0xffffffff;
	else if (level != AMDGPU_VM_PTB)
		return 0x1ff;
	else
		return AMDGPU_VM_PTE_COUNT(adev) - 1;
}