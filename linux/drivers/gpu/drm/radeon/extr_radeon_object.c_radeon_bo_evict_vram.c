#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int igp_sideport_enabled; } ;
struct radeon_device {int flags; TYPE_2__ mman; TYPE_1__ mc; } ;

/* Variables and functions */
 int RADEON_IS_IGP ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int ttm_bo_evict_mm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int radeon_bo_evict_vram(struct radeon_device *rdev)
{
	/* late 2.6.33 fix IGP hibernate - we need pm ops to do this correct */
#ifndef CONFIG_HIBERNATION
	if (rdev->flags & RADEON_IS_IGP) {
		if (rdev->mc.igp_sideport_enabled == false)
			/* Useless to evict on IGP chips */
			return 0;
	}
#endif
	return ttm_bo_evict_mm(&rdev->mman.bdev, TTM_PL_VRAM);
}