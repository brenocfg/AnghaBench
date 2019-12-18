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
typedef  scalar_t__ u32 ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {int crtc_id; scalar_t__ crtc_offset; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int AVIVO_D1CURSOR_MODE_24BPP ; 
 int AVIVO_D1CURSOR_MODE_SHIFT ; 
 scalar_t__ AVIVO_D1CUR_CONTROL ; 
 int /*<<< orphan*/  EVERGREEN_CURSOR_24_8_PRE_MULT ; 
 int EVERGREEN_CURSOR_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVERGREEN_CURSOR_URGENT_1_2 ; 
 int EVERGREEN_CURSOR_URGENT_CONTROL (int /*<<< orphan*/ ) ; 
 scalar_t__ EVERGREEN_CUR_CONTROL ; 
 scalar_t__ RADEON_CRTC2_GEN_CNTL ; 
 int RADEON_CRTC_CUR_EN ; 
 scalar_t__ RADEON_CRTC_GEN_CNTL ; 
 int RREG32_IDX (scalar_t__) ; 
 int /*<<< orphan*/  WREG32_IDX (scalar_t__,int) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void radeon_hide_cursor(struct drm_crtc *crtc)
{
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct radeon_device *rdev = crtc->dev->dev_private;

	if (ASIC_IS_DCE4(rdev)) {
		WREG32_IDX(EVERGREEN_CUR_CONTROL + radeon_crtc->crtc_offset,
			   EVERGREEN_CURSOR_MODE(EVERGREEN_CURSOR_24_8_PRE_MULT) |
			   EVERGREEN_CURSOR_URGENT_CONTROL(EVERGREEN_CURSOR_URGENT_1_2));
	} else if (ASIC_IS_AVIVO(rdev)) {
		WREG32_IDX(AVIVO_D1CUR_CONTROL + radeon_crtc->crtc_offset,
			   (AVIVO_D1CURSOR_MODE_24BPP << AVIVO_D1CURSOR_MODE_SHIFT));
	} else {
		u32 reg;
		switch (radeon_crtc->crtc_id) {
		case 0:
			reg = RADEON_CRTC_GEN_CNTL;
			break;
		case 1:
			reg = RADEON_CRTC2_GEN_CNTL;
			break;
		default:
			return;
		}
		WREG32_IDX(reg, RREG32_IDX(reg) & ~RADEON_CRTC_CUR_EN);
	}
}