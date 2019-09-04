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
typedef  int uint32_t ;
struct radeon_encoder_int_tmds {TYPE_1__* tmds_pll; } ;
struct radeon_encoder {scalar_t__ rmx_type; scalar_t__ enc_priv; } ;
struct radeon_device {scalar_t__ family; scalar_t__ is_atom_bios; } ;
struct radeon_crtc {scalar_t__ crtc_id; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct TYPE_2__ {scalar_t__ freq; int value; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 scalar_t__ CHIP_R100 ; 
 scalar_t__ CHIP_R200 ; 
 scalar_t__ CHIP_RV280 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int R200_FP_SOURCE_SEL_CRTC1 ; 
 int R200_FP_SOURCE_SEL_CRTC2 ; 
 int R200_FP_SOURCE_SEL_MASK ; 
 int R200_FP_SOURCE_SEL_RMX ; 
 int RADEON_FP_CRTC_DONT_SHADOW_HEND ; 
 int RADEON_FP_CRTC_DONT_SHADOW_VPAR ; 
 int RADEON_FP_CRTC_LOCK_8DOT ; 
 int RADEON_FP_CRTC_USE_SHADOW_VEND ; 
 int RADEON_FP_CRT_SYNC_ALT ; 
 int RADEON_FP_CRT_SYNC_SEL ; 
 int RADEON_FP_DFP_SYNC_SEL ; 
 int RADEON_FP_FPON ; 
 int /*<<< orphan*/  RADEON_FP_GEN_CNTL ; 
 int RADEON_FP_PANEL_FORMAT ; 
 int RADEON_FP_RMX_HVSYNC_CONTROL_EN ; 
 int RADEON_FP_SEL_CRTC2 ; 
 int RADEON_FP_TMDS_EN ; 
 int RADEON_FP_USE_SHADOW_EN ; 
 int /*<<< orphan*/  RADEON_TMDS_PLL_CNTL ; 
 int /*<<< orphan*/  RADEON_TMDS_TRANSMITTER_CNTL ; 
 int RADEON_TMDS_TRANSMITTER_PLLEN ; 
 int RADEON_TMDS_TRANSMITTER_PLLRST ; 
 scalar_t__ RMX_OFF ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_atombios_encoder_crtc_scratch_regs (struct drm_encoder*,scalar_t__) ; 
 int /*<<< orphan*/  radeon_combios_encoder_crtc_scratch_regs (struct drm_encoder*,scalar_t__) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_legacy_tmds_int_mode_set(struct drm_encoder *encoder,
					    struct drm_display_mode *mode,
					    struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t tmp, tmds_pll_cntl, tmds_transmitter_cntl, fp_gen_cntl;
	int i;

	DRM_DEBUG_KMS("\n");

	tmp = tmds_pll_cntl = RREG32(RADEON_TMDS_PLL_CNTL);
	tmp &= 0xfffff;
	if (rdev->family == CHIP_RV280) {
		/* bit 22 of TMDS_PLL_CNTL is read-back inverted */
		tmp ^= (1 << 22);
		tmds_pll_cntl ^= (1 << 22);
	}

	if (radeon_encoder->enc_priv) {
		struct radeon_encoder_int_tmds *tmds = (struct radeon_encoder_int_tmds *)radeon_encoder->enc_priv;

		for (i = 0; i < 4; i++) {
			if (tmds->tmds_pll[i].freq == 0)
				break;
			if ((uint32_t)(mode->clock / 10) < tmds->tmds_pll[i].freq) {
				tmp = tmds->tmds_pll[i].value ;
				break;
			}
		}
	}

	if (ASIC_IS_R300(rdev) || (rdev->family == CHIP_RV280)) {
		if (tmp & 0xfff00000)
			tmds_pll_cntl = tmp;
		else {
			tmds_pll_cntl &= 0xfff00000;
			tmds_pll_cntl |= tmp;
		}
	} else
		tmds_pll_cntl = tmp;

	tmds_transmitter_cntl = RREG32(RADEON_TMDS_TRANSMITTER_CNTL) &
		~(RADEON_TMDS_TRANSMITTER_PLLRST);

	if (rdev->family == CHIP_R200 ||
	    rdev->family == CHIP_R100 ||
	    ASIC_IS_R300(rdev))
		tmds_transmitter_cntl &= ~(RADEON_TMDS_TRANSMITTER_PLLEN);
	else /* RV chips got this bit reversed */
		tmds_transmitter_cntl |= RADEON_TMDS_TRANSMITTER_PLLEN;

	fp_gen_cntl = (RREG32(RADEON_FP_GEN_CNTL) |
		      (RADEON_FP_CRTC_DONT_SHADOW_VPAR |
		       RADEON_FP_CRTC_DONT_SHADOW_HEND));

	fp_gen_cntl &= ~(RADEON_FP_FPON | RADEON_FP_TMDS_EN);

	fp_gen_cntl &= ~(RADEON_FP_RMX_HVSYNC_CONTROL_EN |
			 RADEON_FP_DFP_SYNC_SEL |
			 RADEON_FP_CRT_SYNC_SEL |
			 RADEON_FP_CRTC_LOCK_8DOT |
			 RADEON_FP_USE_SHADOW_EN |
			 RADEON_FP_CRTC_USE_SHADOW_VEND |
			 RADEON_FP_CRT_SYNC_ALT);

	if (1) /*  FIXME rgbBits == 8 */
		fp_gen_cntl |= RADEON_FP_PANEL_FORMAT;  /* 24 bit format */
	else
		fp_gen_cntl &= ~RADEON_FP_PANEL_FORMAT;/* 18 bit format */

	if (radeon_crtc->crtc_id == 0) {
		if (ASIC_IS_R300(rdev) || rdev->family == CHIP_R200) {
			fp_gen_cntl &= ~R200_FP_SOURCE_SEL_MASK;
			if (radeon_encoder->rmx_type != RMX_OFF)
				fp_gen_cntl |= R200_FP_SOURCE_SEL_RMX;
			else
				fp_gen_cntl |= R200_FP_SOURCE_SEL_CRTC1;
		} else
			fp_gen_cntl &= ~RADEON_FP_SEL_CRTC2;
	} else {
		if (ASIC_IS_R300(rdev) || rdev->family == CHIP_R200) {
			fp_gen_cntl &= ~R200_FP_SOURCE_SEL_MASK;
			fp_gen_cntl |= R200_FP_SOURCE_SEL_CRTC2;
		} else
			fp_gen_cntl |= RADEON_FP_SEL_CRTC2;
	}

	WREG32(RADEON_TMDS_PLL_CNTL, tmds_pll_cntl);
	WREG32(RADEON_TMDS_TRANSMITTER_CNTL, tmds_transmitter_cntl);
	WREG32(RADEON_FP_GEN_CNTL, fp_gen_cntl);

	if (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	else
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
}