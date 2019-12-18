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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {void* csa_cpu_addr; } ;
struct amdgpu_device {TYPE_1__ virt; } ;
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_bo**,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int amdgpu_allocate_static_csa(struct amdgpu_device *adev, struct amdgpu_bo **bo,
				u32 domain, uint32_t size)
{
	int r;
	void *ptr;

	r = amdgpu_bo_create_kernel(adev, size, PAGE_SIZE,
				domain, bo,
				NULL, &ptr);
	if (!*bo)
		return -ENOMEM;

	memset(ptr, 0, size);
	adev->virt.csa_cpu_addr = ptr;
	return 0;
}