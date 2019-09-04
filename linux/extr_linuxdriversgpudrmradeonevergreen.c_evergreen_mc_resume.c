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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ vram_start; } ;
struct radeon_device {int num_crtc; int usec_timeout; TYPE_1__ mc; } ;
struct evergreen_mc_save {int vga_hdp_control; int vga_render_control; scalar_t__* crtc_enabled; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE6 (struct radeon_device*) ; 
 int /*<<< orphan*/  ASIC_IS_NODCE (struct radeon_device*) ; 
 scalar_t__ BIF_FB_EN ; 
 int BLACKOUT_MODE_MASK ; 
 scalar_t__ EVERGREEN_CRTC_BLANK_CONTROL ; 
 int EVERGREEN_CRTC_BLANK_DATA_EN ; 
 scalar_t__ EVERGREEN_CRTC_CONTROL ; 
 int EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE ; 
 scalar_t__ EVERGREEN_CRTC_UPDATE_LOCK ; 
 scalar_t__ EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS ; 
 scalar_t__ EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS ; 
 scalar_t__ EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH ; 
 int EVERGREEN_GRPH_SURFACE_UPDATE_PENDING ; 
 scalar_t__ EVERGREEN_GRPH_UPDATE ; 
 int EVERGREEN_GRPH_UPDATE_LOCK ; 
 scalar_t__ EVERGREEN_MASTER_UPDATE_LOCK ; 
 scalar_t__ EVERGREEN_MASTER_UPDATE_MODE ; 
 scalar_t__ EVERGREEN_VGA_MEMORY_BASE_ADDRESS ; 
 scalar_t__ EVERGREEN_VGA_MEMORY_BASE_ADDRESS_HIGH ; 
 int FB_READ_EN ; 
 int FB_WRITE_EN ; 
 scalar_t__ MC_SHARED_BLACKOUT_CNTL ; 
 int RREG32 (scalar_t__) ; 
 scalar_t__ VGA_HDP_CONTROL ; 
 scalar_t__ VGA_RENDER_CONTROL ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 scalar_t__* crtc_offsets ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int radeon_get_vblank_counter (struct radeon_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int upper_32_bits (scalar_t__) ; 

void evergreen_mc_resume(struct radeon_device *rdev, struct evergreen_mc_save *save)
{
	u32 tmp, frame_count;
	int i, j;

	/* update crtc base addresses */
	for (i = 0; i < rdev->num_crtc; i++) {
		WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS_HIGH + crtc_offsets[i],
		       upper_32_bits(rdev->mc.vram_start));
		WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS_HIGH + crtc_offsets[i],
		       upper_32_bits(rdev->mc.vram_start));
		WREG32(EVERGREEN_GRPH_PRIMARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
		WREG32(EVERGREEN_GRPH_SECONDARY_SURFACE_ADDRESS + crtc_offsets[i],
		       (u32)rdev->mc.vram_start);
	}

	if (!ASIC_IS_NODCE(rdev)) {
		WREG32(EVERGREEN_VGA_MEMORY_BASE_ADDRESS_HIGH, upper_32_bits(rdev->mc.vram_start));
		WREG32(EVERGREEN_VGA_MEMORY_BASE_ADDRESS, (u32)rdev->mc.vram_start);
	}

	/* unlock regs and wait for update */
	for (i = 0; i < rdev->num_crtc; i++) {
		if (save->crtc_enabled[i]) {
			tmp = RREG32(EVERGREEN_MASTER_UPDATE_MODE + crtc_offsets[i]);
			if ((tmp & 0x7) != 0) {
				tmp &= ~0x7;
				WREG32(EVERGREEN_MASTER_UPDATE_MODE + crtc_offsets[i], tmp);
			}
			tmp = RREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i]);
			if (tmp & EVERGREEN_GRPH_UPDATE_LOCK) {
				tmp &= ~EVERGREEN_GRPH_UPDATE_LOCK;
				WREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i], tmp);
			}
			tmp = RREG32(EVERGREEN_MASTER_UPDATE_LOCK + crtc_offsets[i]);
			if (tmp & 1) {
				tmp &= ~1;
				WREG32(EVERGREEN_MASTER_UPDATE_LOCK + crtc_offsets[i], tmp);
			}
			for (j = 0; j < rdev->usec_timeout; j++) {
				tmp = RREG32(EVERGREEN_GRPH_UPDATE + crtc_offsets[i]);
				if ((tmp & EVERGREEN_GRPH_SURFACE_UPDATE_PENDING) == 0)
					break;
				udelay(1);
			}
		}
	}

	/* unblackout the MC */
	tmp = RREG32(MC_SHARED_BLACKOUT_CNTL);
	tmp &= ~BLACKOUT_MODE_MASK;
	WREG32(MC_SHARED_BLACKOUT_CNTL, tmp);
	/* allow CPU access */
	WREG32(BIF_FB_EN, FB_READ_EN | FB_WRITE_EN);

	for (i = 0; i < rdev->num_crtc; i++) {
		if (save->crtc_enabled[i]) {
			if (ASIC_IS_DCE6(rdev)) {
				tmp = RREG32(EVERGREEN_CRTC_BLANK_CONTROL + crtc_offsets[i]);
				tmp &= ~EVERGREEN_CRTC_BLANK_DATA_EN;
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				WREG32(EVERGREEN_CRTC_BLANK_CONTROL + crtc_offsets[i], tmp);
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			} else {
				tmp = RREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i]);
				tmp &= ~EVERGREEN_CRTC_DISP_READ_REQUEST_DISABLE;
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 1);
				WREG32(EVERGREEN_CRTC_CONTROL + crtc_offsets[i], tmp);
				WREG32(EVERGREEN_CRTC_UPDATE_LOCK + crtc_offsets[i], 0);
			}
			/* wait for the next frame */
			frame_count = radeon_get_vblank_counter(rdev, i);
			for (j = 0; j < rdev->usec_timeout; j++) {
				if (radeon_get_vblank_counter(rdev, i) != frame_count)
					break;
				udelay(1);
			}
		}
	}
	if (!ASIC_IS_NODCE(rdev)) {
		/* Unlock vga access */
		WREG32(VGA_HDP_CONTROL, save->vga_hdp_control);
		mdelay(1);
		WREG32(VGA_RENDER_CONTROL, save->vga_render_control);
	}
}