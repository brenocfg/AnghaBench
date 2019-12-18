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
struct TYPE_2__ {int /*<<< orphan*/  vram_start; } ;
struct radeon_device {int flags; TYPE_1__ mc; } ;
struct r100_mc_save {int /*<<< orphan*/  CRTC2_GEN_CNTL; int /*<<< orphan*/  CRTC_GEN_CNTL; int /*<<< orphan*/  CRTC_EXT_CNTL; int /*<<< orphan*/  GENMO_WT; } ;

/* Variables and functions */
 int RADEON_SINGLE_CRTC ; 
 int /*<<< orphan*/  R_000050_CRTC_GEN_CNTL ; 
 int /*<<< orphan*/  R_000054_CRTC_EXT_CNTL ; 
 int /*<<< orphan*/  R_00023C_DISPLAY_BASE_ADDR ; 
 int /*<<< orphan*/  R_00033C_CRTC2_DISPLAY_BASE_ADDR ; 
 int /*<<< orphan*/  R_0003C2_GENMO_WT ; 
 int /*<<< orphan*/  R_0003F8_CRTC2_GEN_CNTL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void r100_mc_resume(struct radeon_device *rdev, struct r100_mc_save *save)
{
	/* Update base address for crtc */
	WREG32(R_00023C_DISPLAY_BASE_ADDR, rdev->mc.vram_start);
	if (!(rdev->flags & RADEON_SINGLE_CRTC)) {
		WREG32(R_00033C_CRTC2_DISPLAY_BASE_ADDR, rdev->mc.vram_start);
	}
	/* Restore CRTC registers */
	WREG8(R_0003C2_GENMO_WT, save->GENMO_WT);
	WREG32(R_000054_CRTC_EXT_CNTL, save->CRTC_EXT_CNTL);
	WREG32(R_000050_CRTC_GEN_CNTL, save->CRTC_GEN_CNTL);
	if (!(rdev->flags & RADEON_SINGLE_CRTC)) {
		WREG32(R_0003F8_CRTC2_GEN_CNTL, save->CRTC2_GEN_CNTL);
	}
}