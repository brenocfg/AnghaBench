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
struct amdgpu_device {int /*<<< orphan*/  stolen_vga_memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  amdgpu_bo_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_bo_free_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amdgpu_gart_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gart_table_vram_free (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_gem_force_release (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_vm_manager_fini (struct amdgpu_device*) ; 

__attribute__((used)) static int gmc_v9_0_sw_fini(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	amdgpu_gem_force_release(adev);
	amdgpu_vm_manager_fini(adev);

	/*
	* TODO:
	* Currently there is a bug where some memory client outside
	* of the driver writes to first 8M of VRAM on S3 resume,
	* this overrides GART which by default gets placed in first 8M and
	* causes VM_FAULTS once GTT is accessed.
	* Keep the stolen memory reservation until the while this is not solved.
	* Also check code in gmc_v9_0_get_vbios_fb_size and gmc_v9_0_late_init
	*/
	amdgpu_bo_free_kernel(&adev->stolen_vga_memory, NULL, NULL);

	amdgpu_gart_table_vram_free(adev);
	amdgpu_bo_fini(adev);
	amdgpu_gart_fini(adev);

	return 0;
}