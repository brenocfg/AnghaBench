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
struct TYPE_2__ {int gtt_start; int gtt_end; int vram_start; int vram_end; int /*<<< orphan*/  agp_base; } ;
struct radeon_device {int flags; TYPE_1__ mc; int /*<<< orphan*/  dev; } ;
struct r100_mc_save {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int RADEON_IS_AGP ; 
 int /*<<< orphan*/  R_000148_MC_FB_LOCATION ; 
 int /*<<< orphan*/  R_00014C_MC_AGP_LOCATION ; 
 int /*<<< orphan*/  R_00015C_AGP_BASE_2 ; 
 int /*<<< orphan*/  R_000170_AGP_BASE ; 
 int S_000148_MC_FB_START (int) ; 
 int S_000148_MC_FB_TOP (int) ; 
 int S_00014C_MC_AGP_START (int) ; 
 int S_00014C_MC_AGP_TOP (int) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int lower_32_bits (int /*<<< orphan*/ ) ; 
 int r100_debugfs_mc_info_init (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_mc_resume (struct radeon_device*,struct r100_mc_save*) ; 
 int /*<<< orphan*/  r100_mc_stop (struct radeon_device*,struct r100_mc_save*) ; 
 scalar_t__ r300_mc_wait_for_idle (struct radeon_device*) ; 
 int upper_32_bits (int /*<<< orphan*/ ) ; 

void r300_mc_program(struct radeon_device *rdev)
{
	struct r100_mc_save save;
	int r;

	r = r100_debugfs_mc_info_init(rdev);
	if (r) {
		dev_err(rdev->dev, "Failed to create r100_mc debugfs file.\n");
	}

	/* Stops all mc clients */
	r100_mc_stop(rdev, &save);
	if (rdev->flags & RADEON_IS_AGP) {
		WREG32(R_00014C_MC_AGP_LOCATION,
			S_00014C_MC_AGP_START(rdev->mc.gtt_start >> 16) |
			S_00014C_MC_AGP_TOP(rdev->mc.gtt_end >> 16));
		WREG32(R_000170_AGP_BASE, lower_32_bits(rdev->mc.agp_base));
		WREG32(R_00015C_AGP_BASE_2,
			upper_32_bits(rdev->mc.agp_base) & 0xff);
	} else {
		WREG32(R_00014C_MC_AGP_LOCATION, 0x0FFFFFFF);
		WREG32(R_000170_AGP_BASE, 0);
		WREG32(R_00015C_AGP_BASE_2, 0);
	}
	/* Wait for mc idle */
	if (r300_mc_wait_for_idle(rdev))
		DRM_INFO("Failed to wait MC idle before programming MC.\n");
	/* Program MC, should be a 32bits limited address space */
	WREG32(R_000148_MC_FB_LOCATION,
		S_000148_MC_FB_START(rdev->mc.vram_start >> 16) |
		S_000148_MC_FB_TOP(rdev->mc.vram_end >> 16));
	r100_mc_resume(rdev, &save);
}