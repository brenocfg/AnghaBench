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
struct radeon_device {int dummy; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {struct radeon_device* dev_private; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 int R200_FP2_DVO_RATE_SEL_SDR ; 
 int R200_FP2_SOURCE_SEL_TRANS_UNIT ; 
 int RADEON_CRTC2_DISP_REQ_EN_B ; 
 int RADEON_CRTC2_EN ; 
 int /*<<< orphan*/  RADEON_CRTC2_GEN_CNTL ; 
 int /*<<< orphan*/  RADEON_CRTC2_H_SYNC_STRT_WID ; 
 int /*<<< orphan*/  RADEON_CRTC2_H_TOTAL_DISP ; 
 int /*<<< orphan*/  RADEON_CRTC2_V_SYNC_STRT_WID ; 
 int /*<<< orphan*/  RADEON_CRTC2_V_TOTAL_DISP ; 
 int RADEON_DISP_DAC_SOURCE_RMX ; 
 int /*<<< orphan*/  RADEON_DISP_LIN_TRANS_GRPH_A ; 
 int /*<<< orphan*/  RADEON_DISP_LIN_TRANS_GRPH_B ; 
 int /*<<< orphan*/  RADEON_DISP_LIN_TRANS_GRPH_C ; 
 int /*<<< orphan*/  RADEON_DISP_LIN_TRANS_GRPH_D ; 
 int /*<<< orphan*/  RADEON_DISP_LIN_TRANS_GRPH_E ; 
 int /*<<< orphan*/  RADEON_DISP_LIN_TRANS_GRPH_F ; 
 int /*<<< orphan*/  RADEON_DISP_OUTPUT_CNTL ; 
 int RADEON_DISP_TRANS_MATRIX_GRAPHICS ; 
 int RADEON_FP2_DVO_EN ; 
 int /*<<< orphan*/  RADEON_FP2_GEN_CNTL ; 
 int RADEON_FP2_ON ; 
 int RADEON_FP2_PANEL_FORMAT ; 
 int RADEON_GPIO_A_0 ; 
 int /*<<< orphan*/  RADEON_GPIO_MONID ; 
 int RADEON_GPIO_Y_0 ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drm_can_sleep () ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static bool radeon_legacy_ext_dac_detect(struct drm_encoder *encoder,
					 struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	uint32_t gpio_monid, fp2_gen_cntl, disp_output_cntl, crtc2_gen_cntl;
	uint32_t disp_lin_trans_grph_a, disp_lin_trans_grph_b, disp_lin_trans_grph_c;
	uint32_t disp_lin_trans_grph_d, disp_lin_trans_grph_e, disp_lin_trans_grph_f;
	uint32_t tmp, crtc2_h_total_disp, crtc2_v_total_disp;
	uint32_t crtc2_h_sync_strt_wid, crtc2_v_sync_strt_wid;
	bool found = false;
	int i;

	/* save the regs we need */
	gpio_monid = RREG32(RADEON_GPIO_MONID);
	fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);
	disp_output_cntl = RREG32(RADEON_DISP_OUTPUT_CNTL);
	crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
	disp_lin_trans_grph_a = RREG32(RADEON_DISP_LIN_TRANS_GRPH_A);
	disp_lin_trans_grph_b = RREG32(RADEON_DISP_LIN_TRANS_GRPH_B);
	disp_lin_trans_grph_c = RREG32(RADEON_DISP_LIN_TRANS_GRPH_C);
	disp_lin_trans_grph_d = RREG32(RADEON_DISP_LIN_TRANS_GRPH_D);
	disp_lin_trans_grph_e = RREG32(RADEON_DISP_LIN_TRANS_GRPH_E);
	disp_lin_trans_grph_f = RREG32(RADEON_DISP_LIN_TRANS_GRPH_F);
	crtc2_h_total_disp = RREG32(RADEON_CRTC2_H_TOTAL_DISP);
	crtc2_v_total_disp = RREG32(RADEON_CRTC2_V_TOTAL_DISP);
	crtc2_h_sync_strt_wid = RREG32(RADEON_CRTC2_H_SYNC_STRT_WID);
	crtc2_v_sync_strt_wid = RREG32(RADEON_CRTC2_V_SYNC_STRT_WID);

	tmp = RREG32(RADEON_GPIO_MONID);
	tmp &= ~RADEON_GPIO_A_0;
	WREG32(RADEON_GPIO_MONID, tmp);

	WREG32(RADEON_FP2_GEN_CNTL, (RADEON_FP2_ON |
				     RADEON_FP2_PANEL_FORMAT |
				     R200_FP2_SOURCE_SEL_TRANS_UNIT |
				     RADEON_FP2_DVO_EN |
				     R200_FP2_DVO_RATE_SEL_SDR));

	WREG32(RADEON_DISP_OUTPUT_CNTL, (RADEON_DISP_DAC_SOURCE_RMX |
					 RADEON_DISP_TRANS_MATRIX_GRAPHICS));

	WREG32(RADEON_CRTC2_GEN_CNTL, (RADEON_CRTC2_EN |
				       RADEON_CRTC2_DISP_REQ_EN_B));

	WREG32(RADEON_DISP_LIN_TRANS_GRPH_A, 0x00000000);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_B, 0x000003f0);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_C, 0x00000000);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_D, 0x000003f0);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_E, 0x00000000);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_F, 0x000003f0);

	WREG32(RADEON_CRTC2_H_TOTAL_DISP, 0x01000008);
	WREG32(RADEON_CRTC2_H_SYNC_STRT_WID, 0x00000800);
	WREG32(RADEON_CRTC2_V_TOTAL_DISP, 0x00080001);
	WREG32(RADEON_CRTC2_V_SYNC_STRT_WID, 0x00000080);

	for (i = 0; i < 200; i++) {
		tmp = RREG32(RADEON_GPIO_MONID);
		if (tmp & RADEON_GPIO_Y_0)
			found = true;

		if (found)
			break;

		if (!drm_can_sleep())
			mdelay(1);
		else
			msleep(1);
	}

	/* restore the regs we used */
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_A, disp_lin_trans_grph_a);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_B, disp_lin_trans_grph_b);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_C, disp_lin_trans_grph_c);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_D, disp_lin_trans_grph_d);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_E, disp_lin_trans_grph_e);
	WREG32(RADEON_DISP_LIN_TRANS_GRPH_F, disp_lin_trans_grph_f);
	WREG32(RADEON_CRTC2_H_TOTAL_DISP, crtc2_h_total_disp);
	WREG32(RADEON_CRTC2_V_TOTAL_DISP, crtc2_v_total_disp);
	WREG32(RADEON_CRTC2_H_SYNC_STRT_WID, crtc2_h_sync_strt_wid);
	WREG32(RADEON_CRTC2_V_SYNC_STRT_WID, crtc2_v_sync_strt_wid);
	WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
	WREG32(RADEON_DISP_OUTPUT_CNTL, disp_output_cntl);
	WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);
	WREG32(RADEON_GPIO_MONID, gpio_monid);

	return found;
}