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
struct radeon_device {scalar_t__ family; } ;
struct radeon_crtc {int crtc_offset; int cursor_addr; int crtc_id; int legacy_display_base_addr; scalar_t__ cursor_out_of_bounds; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int AVIVO_D1CURSOR_EN ; 
 int AVIVO_D1CURSOR_MODE_24BPP ; 
 int AVIVO_D1CURSOR_MODE_SHIFT ; 
 int AVIVO_D1CUR_CONTROL ; 
 scalar_t__ AVIVO_D1CUR_SURFACE_ADDRESS ; 
 scalar_t__ CHIP_RV770 ; 
 int /*<<< orphan*/  EVERGREEN_CURSOR_24_8_PRE_MULT ; 
 int EVERGREEN_CURSOR_EN ; 
 int EVERGREEN_CURSOR_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVERGREEN_CURSOR_URGENT_1_2 ; 
 int EVERGREEN_CURSOR_URGENT_CONTROL (int /*<<< orphan*/ ) ; 
 int EVERGREEN_CUR_CONTROL ; 
 scalar_t__ EVERGREEN_CUR_SURFACE_ADDRESS ; 
 scalar_t__ EVERGREEN_CUR_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D1CUR_SURFACE_ADDRESS_HIGH ; 
 scalar_t__ R700_D2CUR_SURFACE_ADDRESS_HIGH ; 
 int RADEON_CRTC2_GEN_CNTL ; 
 int RADEON_CRTC_CUR_EN ; 
 int RADEON_CRTC_CUR_MODE_24BPP ; 
 int RADEON_CRTC_CUR_MODE_MASK ; 
 int RADEON_CRTC_CUR_MODE_SHIFT ; 
 int RADEON_CRTC_GEN_CNTL ; 
 scalar_t__ RADEON_CUR_OFFSET ; 
 scalar_t__ RADEON_MM_DATA ; 
 scalar_t__ RADEON_MM_INDEX ; 
 int /*<<< orphan*/  WREG32 (scalar_t__,int) ; 
 int /*<<< orphan*/  WREG32_P (scalar_t__,int,int) ; 
 int lower_32_bits (int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 int upper_32_bits (int) ; 

__attribute__((used)) static void radeon_show_cursor(struct drm_crtc *crtc)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct radeon_device *rdev = crtc->dev->dev_private;

	if (radeon_crtc->cursor_out_of_bounds)
		return;

	if (ASIC_IS_DCE4(rdev)) {
		WREG32(EVERGREEN_CUR_SURFACE_ADDRESS_HIGH + radeon_crtc->crtc_offset,
		       upper_32_bits(radeon_crtc->cursor_addr));
		WREG32(EVERGREEN_CUR_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
		       lower_32_bits(radeon_crtc->cursor_addr));
		WREG32(RADEON_MM_INDEX, EVERGREEN_CUR_CONTROL + radeon_crtc->crtc_offset);
		WREG32(RADEON_MM_DATA, EVERGREEN_CURSOR_EN |
		       EVERGREEN_CURSOR_MODE(EVERGREEN_CURSOR_24_8_PRE_MULT) |
		       EVERGREEN_CURSOR_URGENT_CONTROL(EVERGREEN_CURSOR_URGENT_1_2));
	} else if (ASIC_IS_AVIVO(rdev)) {
		if (rdev->family >= CHIP_RV770) {
			if (radeon_crtc->crtc_id)
				WREG32(R700_D2CUR_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(radeon_crtc->cursor_addr));
			else
				WREG32(R700_D1CUR_SURFACE_ADDRESS_HIGH,
				       upper_32_bits(radeon_crtc->cursor_addr));
		}

		WREG32(AVIVO_D1CUR_SURFACE_ADDRESS + radeon_crtc->crtc_offset,
		       lower_32_bits(radeon_crtc->cursor_addr));
		WREG32(RADEON_MM_INDEX, AVIVO_D1CUR_CONTROL + radeon_crtc->crtc_offset);
		WREG32(RADEON_MM_DATA, AVIVO_D1CURSOR_EN |
		       (AVIVO_D1CURSOR_MODE_24BPP << AVIVO_D1CURSOR_MODE_SHIFT));
	} else {
		/* offset is from DISP(2)_BASE_ADDRESS */
		WREG32(RADEON_CUR_OFFSET + radeon_crtc->crtc_offset,
		       radeon_crtc->cursor_addr - radeon_crtc->legacy_display_base_addr);

		switch (radeon_crtc->crtc_id) {
		case 0:
			WREG32(RADEON_MM_INDEX, RADEON_CRTC_GEN_CNTL);
			break;
		case 1:
			WREG32(RADEON_MM_INDEX, RADEON_CRTC2_GEN_CNTL);
			break;
		default:
			return;
		}

		WREG32_P(RADEON_MM_DATA, (RADEON_CRTC_CUR_EN |
					  (RADEON_CRTC_CUR_MODE_24BPP << RADEON_CRTC_CUR_MODE_SHIFT)),
			 ~(RADEON_CRTC_CUR_EN | RADEON_CRTC_CUR_MODE_MASK));
	}
}