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
typedef  int uint32_t ;
struct radeon_encoder_lvds {int lvds_gen_cntl; int panel_digon_delay; int panel_blon_delay; } ;
struct radeon_encoder {scalar_t__ rmx_type; scalar_t__ enc_priv; int /*<<< orphan*/  pixel_clock; } ;
struct radeon_device {scalar_t__ family; scalar_t__ is_atom_bios; } ;
struct radeon_crtc {scalar_t__ crtc_id; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int /*<<< orphan*/  clock; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 scalar_t__ CHIP_RV410 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  PANEL_ENCODER_ACTION_ENABLE ; 
 int R300_LVDS_SRC_SEL_CRTC2 ; 
 int R300_LVDS_SRC_SEL_MASK ; 
 int R300_LVDS_SRC_SEL_RMX ; 
 int /*<<< orphan*/  RADEON_CLOCK_CNTL_INDEX ; 
 int RADEON_LVDS_BLON ; 
 int RADEON_LVDS_DISPLAY_DIS ; 
 int RADEON_LVDS_EN ; 
 int /*<<< orphan*/  RADEON_LVDS_GEN_CNTL ; 
 int RADEON_LVDS_ON ; 
 int /*<<< orphan*/  RADEON_LVDS_PLL_CNTL ; 
 int RADEON_LVDS_PLL_EN ; 
 int RADEON_LVDS_PWRSEQ_DELAY1_SHIFT ; 
 int RADEON_LVDS_PWRSEQ_DELAY2_SHIFT ; 
 int RADEON_LVDS_RST_FM ; 
 int RADEON_LVDS_SEL_CRTC2 ; 
 int /*<<< orphan*/  RADEON_LVDS_SS_GEN_CNTL ; 
 scalar_t__ RMX_OFF ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atombios_digital_setup (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_atombios_encoder_crtc_scratch_regs (struct drm_encoder*,scalar_t__) ; 
 int /*<<< orphan*/  radeon_combios_encoder_crtc_scratch_regs (struct drm_encoder*,scalar_t__) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_legacy_lvds_mode_set(struct drm_encoder *encoder,
					struct drm_display_mode *mode,
					struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t lvds_pll_cntl, lvds_gen_cntl, lvds_ss_gen_cntl;

	DRM_DEBUG_KMS("\n");

	lvds_pll_cntl = RREG32(RADEON_LVDS_PLL_CNTL);
	lvds_pll_cntl &= ~RADEON_LVDS_PLL_EN;

	lvds_ss_gen_cntl = RREG32(RADEON_LVDS_SS_GEN_CNTL);
	if (rdev->is_atom_bios) {
		/* LVDS_GEN_CNTL parameters are computed in LVDSEncoderControl
		 * need to call that on resume to set up the reg properly.
		 */
		radeon_encoder->pixel_clock = adjusted_mode->clock;
		atombios_digital_setup(encoder, PANEL_ENCODER_ACTION_ENABLE);
		lvds_gen_cntl = RREG32(RADEON_LVDS_GEN_CNTL);
	} else {
		struct radeon_encoder_lvds *lvds = (struct radeon_encoder_lvds *)radeon_encoder->enc_priv;
		if (lvds) {
			DRM_DEBUG_KMS("bios LVDS_GEN_CNTL: 0x%x\n", lvds->lvds_gen_cntl);
			lvds_gen_cntl = lvds->lvds_gen_cntl;
			lvds_ss_gen_cntl &= ~((0xf << RADEON_LVDS_PWRSEQ_DELAY1_SHIFT) |
					      (0xf << RADEON_LVDS_PWRSEQ_DELAY2_SHIFT));
			lvds_ss_gen_cntl |= ((lvds->panel_digon_delay << RADEON_LVDS_PWRSEQ_DELAY1_SHIFT) |
					     (lvds->panel_blon_delay << RADEON_LVDS_PWRSEQ_DELAY2_SHIFT));
		} else
			lvds_gen_cntl = RREG32(RADEON_LVDS_GEN_CNTL);
	}
	lvds_gen_cntl |= RADEON_LVDS_DISPLAY_DIS;
	lvds_gen_cntl &= ~(RADEON_LVDS_ON |
			   RADEON_LVDS_BLON |
			   RADEON_LVDS_EN |
			   RADEON_LVDS_RST_FM);

	if (ASIC_IS_R300(rdev))
		lvds_pll_cntl &= ~(R300_LVDS_SRC_SEL_MASK);

	if (radeon_crtc->crtc_id == 0) {
		if (ASIC_IS_R300(rdev)) {
			if (radeon_encoder->rmx_type != RMX_OFF)
				lvds_pll_cntl |= R300_LVDS_SRC_SEL_RMX;
		} else
			lvds_gen_cntl &= ~RADEON_LVDS_SEL_CRTC2;
	} else {
		if (ASIC_IS_R300(rdev))
			lvds_pll_cntl |= R300_LVDS_SRC_SEL_CRTC2;
		else
			lvds_gen_cntl |= RADEON_LVDS_SEL_CRTC2;
	}

	WREG32(RADEON_LVDS_GEN_CNTL, lvds_gen_cntl);
	WREG32(RADEON_LVDS_PLL_CNTL, lvds_pll_cntl);
	WREG32(RADEON_LVDS_SS_GEN_CNTL, lvds_ss_gen_cntl);

	if (rdev->family == CHIP_RV410)
		WREG32(RADEON_CLOCK_CNTL_INDEX, 0);

	if (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	else
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
}