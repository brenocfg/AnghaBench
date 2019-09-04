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
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_ALIGN (int) ; 
 int amdgpu_vm_num_entries (struct amdgpu_device*,unsigned int) ; 

__attribute__((used)) static unsigned amdgpu_vm_bo_size(struct amdgpu_device *adev, unsigned level)
{
	return AMDGPU_GPU_PAGE_ALIGN(amdgpu_vm_num_entries(adev, level) * 8);
}