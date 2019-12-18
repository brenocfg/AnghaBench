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
 int /*<<< orphan*/  amdgpu_bo_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gem_force_release (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vm_manager_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  gmc_v10_0_gart_fini (struct amdgpu_device*) ; 

__attribute__((used)) static int gmc_v10_0_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_vm_manager_fini(adev);
	gmc_v10_0_gart_fini(adev);
	amdgpu_gem_force_release(adev);
	amdgpu_bo_fini(adev);

	return 0;
}