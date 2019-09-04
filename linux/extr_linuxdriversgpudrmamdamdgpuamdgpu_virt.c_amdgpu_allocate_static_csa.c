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
struct TYPE_2__ {int /*<<< orphan*/  csa_vmid0_addr; int /*<<< orphan*/  csa_obj; } ;
struct amdgpu_device {TYPE_1__ virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_CSA_SIZE ; 
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int amdgpu_allocate_static_csa(struct amdgpu_device *adev)
{
	int r;
	void *ptr;

	r = amdgpu_bo_create_kernel(adev, AMDGPU_CSA_SIZE, PAGE_SIZE,
				AMDGPU_GEM_DOMAIN_VRAM, &adev->virt.csa_obj,
				&adev->virt.csa_vmid0_addr, &ptr);
	if (r)
		return r;

	memset(ptr, 0, AMDGPU_CSA_SIZE);
	return 0;
}