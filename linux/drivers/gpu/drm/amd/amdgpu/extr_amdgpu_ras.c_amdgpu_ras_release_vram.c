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
struct amdgpu_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_free_kernel (struct amdgpu_bo**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int amdgpu_ras_release_vram(struct amdgpu_device *adev,
		struct amdgpu_bo **bo_ptr)
{
	/* no need to free it actually. */
	amdgpu_bo_free_kernel(bo_ptr, NULL, NULL);
	return 0;
}