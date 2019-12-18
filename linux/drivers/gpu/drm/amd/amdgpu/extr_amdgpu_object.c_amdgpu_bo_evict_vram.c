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
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_device {int flags; TYPE_1__ mman; } ;

/* Variables and functions */
 int AMD_IS_APU ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int ttm_bo_evict_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int amdgpu_bo_evict_vram(struct amdgpu_device *adev)
{
	/* late 2.6.33 fix IGP hibernate - we need pm ops to do this correct */
#ifndef CONFIG_HIBERNATION
	if (adev->flags & AMD_IS_APU) {
		/* Useless to evict on IGP chips */
		return 0;
	}
#endif
	return ttm_bo_evict_mm(&adev->mman.bdev, TTM_PL_VRAM);
}