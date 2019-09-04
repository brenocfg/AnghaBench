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
struct radeon_encoder_primary_dac {int ps2_pdac_adj; } ;
struct radeon_encoder {scalar_t__ enc_priv; } ;
struct radeon_device {scalar_t__ family; scalar_t__ is_atom_bios; } ;
struct radeon_crtc {scalar_t__ crtc_id; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 scalar_t__ CHIP_R200 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int RADEON_DAC2_DAC_CLK_SEL ; 
 int RADEON_DAC_8BIT_EN ; 
 int RADEON_DAC_BLANKING ; 
 int /*<<< orphan*/  RADEON_DAC_CNTL ; 
 int /*<<< orphan*/  RADEON_DAC_CNTL2 ; 
 int /*<<< orphan*/  RADEON_DAC_MACRO_CNTL ; 
 int RADEON_DAC_MASK_ALL ; 
 int RADEON_DAC_PDWN_B ; 
 int RADEON_DAC_PDWN_G ; 
 int RADEON_DAC_PDWN_R ; 
 int RADEON_DAC_RANGE_CNTL ; 
 int RADEON_DAC_VGA_ADR_EN ; 
 int RADEON_DISP_DAC_SOURCE_CRTC2 ; 
 int RADEON_DISP_DAC_SOURCE_MASK ; 
 int /*<<< orphan*/  RADEON_DISP_OUTPUT_CNTL ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_P (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  radeon_atombios_encoder_crtc_scratch_regs (struct drm_encoder*,scalar_t__) ; 
 int /*<<< orphan*/  radeon_combios_encoder_crtc_scratch_regs (struct drm_encoder*,scalar_t__) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void radeon_legacy_primary_dac_mode_set(struct drm_encoder *encoder,
					       struct drm_display_mode *mode,
					       struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(encoder->crtc);
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	uint32_t disp_output_cntl, dac_cntl, dac2_cntl, dac_macro_cntl;

	DRM_DEBUG_KMS("\n");

	if (radeon_crtc->crtc_id == 0) {
		if (rdev->family == CHIP_R200 || ASIC_IS_R300(rdev)) {
			disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL) &
				~(RADEON_DISP_DAC_SOURCE_MASK);
			WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
		} else {
			dac2_cntl = RREG32(RADEON_DAC_CNTL2)  & ~(RADEON_DAC2_DAC_CLK_SEL);
			WREG32(RADEON_DAC_CNTL2, dac2_cntl);
		}
	} else {
		if (rdev->family == CHIP_R200 || ASIC_IS_R300(rdev)) {
			disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL) &
				~(RADEON_DISP_DAC_SOURCE_MASK);
			disp_output_cntl |= RADEON_DISP_DAC_SOURCE_CRTC2;
			WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
		} else {
			dac2_cntl = RREG32(RADEON_DAC_CNTL2) | RADEON_DAC2_DAC_CLK_SEL;
			WREG32(RADEON_DAC_CNTL2, dac2_cntl);
		}
	}

	dac_cntl = (RADEON_DAC_MASK_ALL |
		    RADEON_DAC_VGA_ADR_EN |
		    /* TODO 6-bits */
		    RADEON_DAC_8BIT_EN);

	WREG32_P(RADEON_DAC_CNTL,
		       dac_cntl,
		       RADEON_DAC_RANGE_CNTL |
		       RADEON_DAC_BLANKING);

	if (radeon_encoder->enc_priv) {
		struct radeon_encoder_primary_dac *p_dac = (struct radeon_encoder_primary_dac *)radeon_encoder->enc_priv;
		dac_macro_cntl = p_dac->ps2_pdac_adj;
	} else
		dac_macro_cntl = RREG32(RADEON_DAC_MACRO_CNTL);
	dac_macro_cntl |= RADEON_DAC_PDWN_R | RADEON_DAC_PDWN_G | RADEON_DAC_PDWN_B;
	WREG32(RADEON_DAC_MACRO_CNTL, dac_macro_cntl);

	if (rdev->is_atom_bios)
		radeon_atombios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
	else
		radeon_combios_encoder_crtc_scratch_regs(encoder, radeon_crtc->crtc_id);
}