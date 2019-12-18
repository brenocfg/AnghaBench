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
struct TYPE_2__ {int max_pfn; } ;
struct amdgpu_device {TYPE_1__ vm_manager; } ;

/* Variables and functions */
 int AMDGPU_GPU_PAGE_SHIFT ; 
 scalar_t__ AMDGPU_VA_RESERVED_SIZE ; 
 int amdgpu_gmc_sign_extend (int) ; 

uint64_t amdgpu_csa_vaddr(struct amdgpu_device *adev)
{
	uint64_t addr = adev->vm_manager.max_pfn << AMDGPU_GPU_PAGE_SHIFT;

	addr -= AMDGPU_VA_RESERVED_SIZE;
	addr = amdgpu_gmc_sign_extend(addr);

	return addr;
}