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
struct TYPE_3__ {int /*<<< orphan*/  visible_vram_size; } ;
struct radeon_device {TYPE_2__* ring; TYPE_1__ mc; } ;
struct TYPE_4__ {int ready; } ;

/* Variables and functions */
 int /*<<< orphan*/  RADEON_CP_CSQ_CNTL ; 
 int /*<<< orphan*/  RADEON_CP_CSQ_MODE ; 
 size_t RADEON_RING_TYPE_GFX_INDEX ; 
 int /*<<< orphan*/  R_000770_SCRATCH_UMSK ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ r100_gui_wait_for_idle (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_ttm_set_active_vram_size (struct radeon_device*,int /*<<< orphan*/ ) ; 

void r100_cp_disable(struct radeon_device *rdev)
{
	/* Disable ring */
	radeon_ttm_set_active_vram_size(rdev, rdev->mc.visible_vram_size);
	rdev->ring[RADEON_RING_TYPE_GFX_INDEX].ready = false;
	WREG32(RADEON_CP_CSQ_MODE, 0);
	WREG32(RADEON_CP_CSQ_CNTL, 0);
	WREG32(R_000770_SCRATCH_UMSK, 0);
	if (r100_gui_wait_for_idle(rdev)) {
		pr_warn("Failed to wait GUI idle while programming pipes. Bad things might happen.\n");
	}
}