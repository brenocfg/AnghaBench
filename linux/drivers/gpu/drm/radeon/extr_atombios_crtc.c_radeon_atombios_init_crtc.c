#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct radeon_device {int dummy; } ;
struct radeon_crtc {int crtc_id; int /*<<< orphan*/  base; int /*<<< orphan*/ * connector; int /*<<< orphan*/ * encoder; scalar_t__ adjusted_clock; int /*<<< orphan*/  pll_id; scalar_t__ crtc_offset; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_DCE4 (struct radeon_device*) ; 
 int /*<<< orphan*/  ATOM_PPLL_INVALID ; 
 scalar_t__ AVIVO_D1CRTC_H_TOTAL ; 
 scalar_t__ AVIVO_D2CRTC_H_TOTAL ; 
 scalar_t__ EVERGREEN_CRTC0_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC1_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC2_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC3_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC4_REGISTER_OFFSET ; 
 scalar_t__ EVERGREEN_CRTC5_REGISTER_OFFSET ; 
 int /*<<< orphan*/  atombios_helper_funcs ; 
 int /*<<< orphan*/  drm_crtc_helper_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void radeon_atombios_init_crtc(struct drm_device *dev,
			       struct radeon_crtc *radeon_crtc)
{
	struct radeon_device *rdev = dev->dev_private;

	if (ASIC_IS_DCE4(rdev)) {
		switch (radeon_crtc->crtc_id) {
		case 0:
		default:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC0_REGISTER_OFFSET;
			break;
		case 1:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC1_REGISTER_OFFSET;
			break;
		case 2:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC2_REGISTER_OFFSET;
			break;
		case 3:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC3_REGISTER_OFFSET;
			break;
		case 4:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC4_REGISTER_OFFSET;
			break;
		case 5:
			radeon_crtc->crtc_offset = EVERGREEN_CRTC5_REGISTER_OFFSET;
			break;
		}
	} else {
		if (radeon_crtc->crtc_id == 1)
			radeon_crtc->crtc_offset =
				AVIVO_D2CRTC_H_TOTAL - AVIVO_D1CRTC_H_TOTAL;
		else
			radeon_crtc->crtc_offset = 0;
	}
	radeon_crtc->pll_id = ATOM_PPLL_INVALID;
	radeon_crtc->adjusted_clock = 0;
	radeon_crtc->encoder = NULL;
	radeon_crtc->connector = NULL;
	drm_crtc_helper_add(&radeon_crtc->base, &atombios_helper_funcs);
}