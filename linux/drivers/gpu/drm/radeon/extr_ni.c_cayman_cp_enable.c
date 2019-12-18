#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  visible_vram_size; } ;
struct radeon_device {TYPE_4__* ring; TYPE_3__ mc; TYPE_2__* asic; } ;
struct TYPE_8__ {int ready; } ;
struct TYPE_5__ {size_t copy_ring_index; } ;
struct TYPE_6__ {TYPE_1__ copy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ME_CNTL ; 
 int CP_ME_HALT ; 
 int CP_PFP_HALT ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  SCRATCH_UMSK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cayman_cp_enable(struct radeon_device *rdev, bool enable)
{
	if (enable)
		WREG32(CP_ME_CNTL, 0);
	else {
		if (rdev->asic->copy.copy_ring_index == RADEON_RING_TYPE_GFX_INDEX)
			radeon_ttm_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
		WREG32(CP_ME_CNTL, (CP_ME_HALT | CP_PFP_HALT));
		WREG32(SCRATCH_UMSK, 0);
		rdev->ring[RADEON_RING_TYPE_GFX_INDEX].ready = false;
	}
}