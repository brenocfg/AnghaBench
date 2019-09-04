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
struct TYPE_2__ {int /*<<< orphan*/ * fw; int /*<<< orphan*/  vm_fault_info; } ;
struct amdgpu_device {TYPE_1__ gmc; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gart_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gart_table_vram_free (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gem_force_release (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vm_manager_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gmc_v7_0_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_gem_force_release(adev);
	amdgpu_vm_manager_fini(adev);
	kfree(adev->gmc.vm_fault_info);
	amdgpu_gart_table_vram_free(adev);
	amdgpu_bo_fini(adev);
	amdgpu_gart_fini(adev);
	release_firmware(adev->gmc.fw);
	adev->gmc.fw = NULL;

	return 0;
}