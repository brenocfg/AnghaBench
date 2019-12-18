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
struct TYPE_2__ {int initialized; int /*<<< orphan*/  bdev; int /*<<< orphan*/ * aper_base_kaddr; } ;
struct amdgpu_device {TYPE_1__ mman; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_PL_GDS ; 
 int /*<<< orphan*/  AMDGPU_PL_GWS ; 
 int /*<<< orphan*/  AMDGPU_PL_OA ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int /*<<< orphan*/  TTM_PL_TT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  amdgpu_ttm_debugfs_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  amdgpu_ttm_fw_reserve_vram_fini (struct amdgpu_device*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ttm_bo_clean_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_bo_device_release (int /*<<< orphan*/ *) ; 

void amdgpu_ttm_fini(struct amdgpu_device *adev)
{
	if (!adev->mman.initialized)
		return;

	amdgpu_ttm_debugfs_fini(adev);
	amdgpu_ttm_fw_reserve_vram_fini(adev);
	if (adev->mman.aper_base_kaddr)
		iounmap(adev->mman.aper_base_kaddr);
	adev->mman.aper_base_kaddr = NULL;

	ttm_bo_clean_mm(&adev->mman.bdev, TTM_PL_VRAM);
	ttm_bo_clean_mm(&adev->mman.bdev, TTM_PL_TT);
	ttm_bo_clean_mm(&adev->mman.bdev, AMDGPU_PL_GDS);
	ttm_bo_clean_mm(&adev->mman.bdev, AMDGPU_PL_GWS);
	ttm_bo_clean_mm(&adev->mman.bdev, AMDGPU_PL_OA);
	ttm_bo_device_release(&adev->mman.bdev);
	adev->mman.initialized = false;
	DRM_INFO("amdgpu: ttm finalized\n");
}