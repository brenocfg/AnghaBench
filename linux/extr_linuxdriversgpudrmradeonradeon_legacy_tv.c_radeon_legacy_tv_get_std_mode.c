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
typedef  int uint16_t ;
struct radeon_tv_mode_constants {int dummy; } ;
struct radeon_pll {int reference_freq; } ;
struct radeon_encoder_tv_dac {scalar_t__ tv_std; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct radeon_encoder {TYPE_1__ base; struct radeon_encoder_tv_dac* enc_priv; } ;
struct TYPE_4__ {struct radeon_pll p1pll; struct radeon_pll p2pll; } ;
struct radeon_device {TYPE_2__ clock; } ;
struct radeon_crtc {int crtc_id; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ TV_STD_NTSC ; 
 scalar_t__ TV_STD_NTSC_J ; 
 scalar_t__ TV_STD_PAL_M ; 
 struct radeon_tv_mode_constants* available_tv_modes ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct radeon_tv_mode_constants *radeon_legacy_tv_get_std_mode(struct radeon_encoder *radeon_encoder,
									    uint16_t *pll_ref_freq)
{
	struct drm_device *dev = radeon_encoder->base.dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc;
	struct radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	const struct radeon_tv_mode_constants *const_ptr;
	struct radeon_pll *pll;

	radeon_crtc = to_radeon_crtc(radeon_encoder->base.crtc);
	if (radeon_crtc->crtc_id == 1)
		pll = &rdev->clock.p2pll;
	else
		pll = &rdev->clock.p1pll;

	if (pll_ref_freq)
		*pll_ref_freq = pll->reference_freq;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M) {
		if (pll->reference_freq == 2700)
			const_ptr = &available_tv_modes[0];
		else
			const_ptr = &available_tv_modes[2];
	} else {
		if (pll->reference_freq == 2700)
			const_ptr = &available_tv_modes[1];
		else
			const_ptr = &available_tv_modes[3];
	}
	return const_ptr;
}