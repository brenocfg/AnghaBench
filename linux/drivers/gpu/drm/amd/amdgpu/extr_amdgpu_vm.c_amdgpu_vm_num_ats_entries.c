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
struct TYPE_2__ {int /*<<< orphan*/  root_level; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 unsigned int AMDGPU_GMC_HOLE_START ; 
 unsigned int AMDGPU_GPU_PAGE_SHIFT ; 
 unsigned int amdgpu_vm_level_shift (struct amdgpu_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned amdgpu_vm_num_ats_entries(struct amdgpu_device *adev)
{
	unsigned shift;

	shift = amdgpu_vm_level_shift(adev, adev->vm_manager.root_level);
	return AMDGPU_GMC_HOLE_START >> (shift + AMDGPU_GPU_PAGE_SHIFT);
}