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
struct TYPE_2__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  robj; } ;
struct amdgpu_device {TYPE_1__ vram_scratch; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_DOMAIN_VRAM ; 
 int /*<<< orphan*/  AMDGPU_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int amdgpu_bo_create_kernel (struct amdgpu_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static int amdgpu_device_vram_scratch_init(struct amdgpu_device *adev)
{
	return amdgpu_bo_create_kernel(adev, AMDGPU_GPU_PAGE_SIZE,
				       PAGE_SIZE, AMDGPU_GEM_DOMAIN_VRAM,
				       &adev->vram_scratch.robj,
				       &adev->vram_scratch.gpu_addr,
				       (void **)&adev->vram_scratch.ptr);
}