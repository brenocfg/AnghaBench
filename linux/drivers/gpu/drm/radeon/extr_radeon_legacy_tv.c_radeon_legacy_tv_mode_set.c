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
typedef  int uint16_t ;
struct radeon_tv_mode_constants {int ver_total; int hor_resolution; int hor_total; int hor_start; int ver_resolution; } ;
struct TYPE_2__ {int timing_cntl; int tv_uv_adr; int* h_code_timing; int* v_code_timing; } ;
struct radeon_encoder_tv_dac {scalar_t__ tv_std; int ntsc_tvdac_adj; int pal_tvdac_adj; TYPE_1__ tv; } ;
struct radeon_encoder {struct radeon_encoder_tv_dac* enc_priv; } ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {int crtc_id; scalar_t__ rmx_type; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_display_mode {int dummy; } ;
struct drm_device {struct radeon_device* dev_private; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  ASIC_IS_R300 (struct radeon_device*) ; 
 int FRAC_BITS ; 
 int MAX_H_CODE_TIMING_LEN ; 
 int MAX_V_CODE_TIMING_LEN ; 
 int NTSC_TV_LINES_PER_FRAME ; 
 int NTSC_TV_PLL_M_14 ; 
 int NTSC_TV_PLL_M_27 ; 
 int NTSC_TV_PLL_N_14 ; 
 int NTSC_TV_PLL_N_27 ; 
 int NTSC_TV_PLL_P_14 ; 
 int NTSC_TV_PLL_P_27 ; 
 int NTSC_TV_VFTOTAL ; 
 int PAL_TV_LINES_PER_FRAME ; 
 int PAL_TV_PLL_M_14 ; 
 int PAL_TV_PLL_M_27 ; 
 int PAL_TV_PLL_N_14 ; 
 int PAL_TV_PLL_N_27 ; 
 int PAL_TV_PLL_P_14 ; 
 int PAL_TV_PLL_P_27 ; 
 int PAL_TV_VFTOTAL ; 
 int RADEON_ALT_PHASE_EN ; 
 int RADEON_BLANK_LEVEL_SHIFT ; 
 int RADEON_CMP_BLU_EN ; 
 int RADEON_CRT_ASYNC_RST ; 
 int RADEON_CRT_FIFO_CE_EN ; 
 int RADEON_CY_FILT_BLEND_SHIFT ; 
 int RADEON_C_GRN_EN ; 
 int RADEON_DAC_DITHER_EN ; 
 int RADEON_DITHER_MODE ; 
 int RADEON_FIFORAM_FFMACRO_READ_MARGIN_SHIFT ; 
 int RADEON_RESTART_FIELD ; 
 int RADEON_RESTART_PHASE_FIX ; 
 int RADEON_RGB_ATTEN_SEL (int) ; 
 int RADEON_RGB_ATTEN_VAL (int) ; 
 int RADEON_RGB_DITHER_EN ; 
 int RADEON_RGB_SRC_SEL_CRTC1 ; 
 int RADEON_RGB_SRC_SEL_CRTC2 ; 
 int RADEON_RGB_SRC_SEL_RMX ; 
 int RADEON_SET_UP_LEVEL_SHIFT ; 
 int RADEON_SLEW_RATE_LIMIT ; 
 int RADEON_SYNC_PUB ; 
 int RADEON_SYNC_TIP_LEVEL ; 
 int RADEON_TVCLK_ALWAYS_ONb ; 
 int RADEON_TVCLK_SRC_SEL_TVPLL ; 
 int RADEON_TVOUT_SCALE_EN ; 
 int RADEON_TVPCP_MASK ; 
 int RADEON_TVPCP_SHIFT ; 
 int RADEON_TVPDC_MASK ; 
 int RADEON_TVPDC_SHIFT ; 
 int RADEON_TVPLL_RESET ; 
 int RADEON_TVPLL_SLEEP ; 
 int RADEON_TVPLL_TEST_DIS ; 
 int RADEON_TVPVG_MASK ; 
 int RADEON_TVPVG_SHIFT ; 
 int RADEON_TV_ASYNC_RST ; 
 int /*<<< orphan*/  RADEON_TV_CRC_CNTL ; 
 int RADEON_TV_DAC_BDACPD ; 
 int RADEON_TV_DAC_BGSLEEP ; 
 int /*<<< orphan*/  RADEON_TV_DAC_CNTL ; 
 int RADEON_TV_DAC_GDACPD ; 
 int RADEON_TV_DAC_NBLANK ; 
 int RADEON_TV_DAC_NHOLD ; 
 int RADEON_TV_DAC_RDACPD ; 
 int RADEON_TV_DAC_STD_NTSC ; 
 int RADEON_TV_DAC_STD_PAL ; 
 int RADEON_TV_FIFO_ASYNC_RST ; 
 int RADEON_TV_FIFO_CE_EN ; 
 int /*<<< orphan*/  RADEON_TV_FTOTAL ; 
 int /*<<< orphan*/  RADEON_TV_GAIN_LIMIT_SETTINGS ; 
 int /*<<< orphan*/  RADEON_TV_HDISP ; 
 int /*<<< orphan*/  RADEON_TV_HSTART ; 
 int /*<<< orphan*/  RADEON_TV_HTOTAL ; 
 int /*<<< orphan*/  RADEON_TV_LINEAR_GAIN_SETTINGS ; 
 int RADEON_TV_M0HI_MASK ; 
 int RADEON_TV_M0HI_SHIFT ; 
 int RADEON_TV_M0LO_MASK ; 
 int /*<<< orphan*/  RADEON_TV_MASTER_CNTL ; 
 int /*<<< orphan*/  RADEON_TV_MODULATOR_CNTL1 ; 
 int /*<<< orphan*/  RADEON_TV_MODULATOR_CNTL2 ; 
 int RADEON_TV_N0HI_MASK ; 
 int RADEON_TV_N0HI_SHIFT ; 
 int RADEON_TV_N0LO_MASK ; 
 int RADEON_TV_N0LO_SHIFT ; 
 int RADEON_TV_ON ; 
 int /*<<< orphan*/  RADEON_TV_PLL_CNTL ; 
 int /*<<< orphan*/  RADEON_TV_PLL_CNTL1 ; 
 int /*<<< orphan*/  RADEON_TV_PRE_DAC_MUX_CNTL ; 
 int RADEON_TV_P_MASK ; 
 int RADEON_TV_P_SHIFT ; 
 int /*<<< orphan*/  RADEON_TV_RGB_CNTL ; 
 int /*<<< orphan*/  RADEON_TV_SYNC_CNTL ; 
 int RADEON_TV_SYNC_IO_DRIVE ; 
 int /*<<< orphan*/  RADEON_TV_TIMING_CNTL ; 
 int RADEON_TV_U_BURST_LEVEL_MASK ; 
 int /*<<< orphan*/  RADEON_TV_VDISP ; 
 int /*<<< orphan*/  RADEON_TV_VSCALER_CNTL1 ; 
 int /*<<< orphan*/  RADEON_TV_VSCALER_CNTL2 ; 
 int /*<<< orphan*/  RADEON_TV_VTOTAL ; 
 int RADEON_TV_V_BURST_LEVEL_MASK ; 
 int RADEON_TV_V_BURST_LEVEL_SHIFT ; 
 int /*<<< orphan*/  RADEON_TV_Y_FALL_CNTL ; 
 int /*<<< orphan*/  RADEON_TV_Y_RISE_CNTL ; 
 int /*<<< orphan*/  RADEON_TV_Y_SAW_TOOTH_CNTL ; 
 int RADEON_UVFLT_EN ; 
 int RADEON_UVRAM_READ_MARGIN_SHIFT ; 
 int RADEON_UV_GAIN_LIMIT_SHIFT ; 
 int RADEON_UV_GAIN_SHIFT ; 
 int RADEON_UV_INC_MASK ; 
 int RADEON_UV_INC_SHIFT ; 
 int RADEON_UV_OUTPUT_DITHER_EN ; 
 int RADEON_UV_OUTPUT_POST_SCALE_SHIFT ; 
 int RADEON_UV_TO_BUF_DITHER_EN ; 
 int RADEON_VIN_ASYNC_RST ; 
 int RADEON_YFLT_EN ; 
 int RADEON_Y_DEL_W_SIG_SHIFT ; 
 int RADEON_Y_FALL_PING_PONG ; 
 int RADEON_Y_GAIN_LIMIT_SHIFT ; 
 int RADEON_Y_GAIN_SHIFT ; 
 int RADEON_Y_OUTPUT_DITHER_EN ; 
 int RADEON_Y_RED_EN ; 
 int RADEON_Y_RISE_PING_PONG ; 
 scalar_t__ RMX_OFF ; 
 int RREG32 (int /*<<< orphan*/ ) ; 
 int* SLOPE_limit ; 
 int* SLOPE_value ; 
 scalar_t__ TV_STD_NTSC ; 
 scalar_t__ TV_STD_NTSC_J ; 
 scalar_t__ TV_STD_PAL_60 ; 
 scalar_t__ TV_STD_PAL_M ; 
 scalar_t__ TV_STD_SCART_PAL ; 
 int /*<<< orphan*/  WREG32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PLL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG32_PLL_P (int /*<<< orphan*/ ,int,int) ; 
 int* YCOEF_EN_value ; 
 int* YCOEF_value ; 
 int* hor_timing_NTSC ; 
 int* hor_timing_PAL ; 
 struct radeon_tv_mode_constants* radeon_legacy_tv_get_std_mode (struct radeon_encoder*,int*) ; 
 int /*<<< orphan*/  radeon_legacy_tv_init_restarts (struct drm_encoder*) ; 
 int /*<<< orphan*/  radeon_legacy_write_tv_restarts (struct radeon_encoder*) ; 
 int /*<<< orphan*/  radeon_restore_tv_timing_tables (struct radeon_encoder*) ; 
 int /*<<< orphan*/  radeon_wait_pll_lock (struct drm_encoder*,int,int,int) ; 
 struct radeon_crtc* to_radeon_crtc (int /*<<< orphan*/ ) ; 
 struct radeon_encoder* to_radeon_encoder (struct drm_encoder*) ; 
 int* vert_timing_NTSC ; 
 int* vert_timing_PAL ; 

void radeon_legacy_tv_mode_set(struct drm_encoder *encoder,
			       struct drm_display_mode *mode,
			       struct drm_display_mode *adjusted_mode)
{
	struct drm_device *dev = encoder->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_encoder *radeon_encoder = to_radeon_encoder(encoder);
	struct radeon_encoder_tv_dac *tv_dac = radeon_encoder->enc_priv;
	const struct radeon_tv_mode_constants *const_ptr;
	struct radeon_crtc *radeon_crtc;
	int i;
	uint16_t pll_ref_freq;
	uint32_t vert_space, flicker_removal, tmp;
	uint32_t tv_master_cntl, tv_rgb_cntl, tv_dac_cntl;
	uint32_t tv_modulator_cntl1, tv_modulator_cntl2;
	uint32_t tv_vscaler_cntl1, tv_vscaler_cntl2;
	uint32_t tv_pll_cntl, tv_pll_cntl1, tv_ftotal;
	uint32_t tv_y_fall_cntl, tv_y_rise_cntl, tv_y_saw_tooth_cntl;
	uint32_t m, n, p;
	const uint16_t *hor_timing;
	const uint16_t *vert_timing;

	const_ptr = radeon_legacy_tv_get_std_mode(radeon_encoder, &pll_ref_freq);
	if (!const_ptr)
		return;

	radeon_crtc = to_radeon_crtc(encoder->crtc);

	tv_master_cntl = (RADEON_VIN_ASYNC_RST |
			  RADEON_CRT_FIFO_CE_EN |
			  RADEON_TV_FIFO_CE_EN |
			  RADEON_TV_ON);

	if (!ASIC_IS_R300(rdev))
		tv_master_cntl |= RADEON_TVCLK_ALWAYS_ONb;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J)
		tv_master_cntl |= RADEON_RESTART_PHASE_FIX;

	tv_modulator_cntl1 = (RADEON_SLEW_RATE_LIMIT |
			      RADEON_SYNC_TIP_LEVEL |
			      RADEON_YFLT_EN |
			      RADEON_UVFLT_EN |
			      (6 << RADEON_CY_FILT_BLEND_SHIFT));

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J) {
		tv_modulator_cntl1 |= (0x46 << RADEON_SET_UP_LEVEL_SHIFT) |
			(0x3b << RADEON_BLANK_LEVEL_SHIFT);
		tv_modulator_cntl2 = (-111 & RADEON_TV_U_BURST_LEVEL_MASK) |
			((0 & RADEON_TV_V_BURST_LEVEL_MASK) << RADEON_TV_V_BURST_LEVEL_SHIFT);
	} else if (tv_dac->tv_std == TV_STD_SCART_PAL) {
		tv_modulator_cntl1 |= RADEON_ALT_PHASE_EN;
		tv_modulator_cntl2 = (0 & RADEON_TV_U_BURST_LEVEL_MASK) |
			((0 & RADEON_TV_V_BURST_LEVEL_MASK) << RADEON_TV_V_BURST_LEVEL_SHIFT);
	} else {
		tv_modulator_cntl1 |= RADEON_ALT_PHASE_EN |
			(0x3b << RADEON_SET_UP_LEVEL_SHIFT) |
			(0x3b << RADEON_BLANK_LEVEL_SHIFT);
		tv_modulator_cntl2 = (-78 & RADEON_TV_U_BURST_LEVEL_MASK) |
			((62 & RADEON_TV_V_BURST_LEVEL_MASK) << RADEON_TV_V_BURST_LEVEL_SHIFT);
	}


	tv_rgb_cntl = (RADEON_RGB_DITHER_EN
		       | RADEON_TVOUT_SCALE_EN
		       | (0x0b << RADEON_UVRAM_READ_MARGIN_SHIFT)
		       | (0x07 << RADEON_FIFORAM_FFMACRO_READ_MARGIN_SHIFT)
		       | RADEON_RGB_ATTEN_SEL(0x3)
		       | RADEON_RGB_ATTEN_VAL(0xc));

	if (radeon_crtc->crtc_id == 1)
		tv_rgb_cntl |= RADEON_RGB_SRC_SEL_CRTC2;
	else {
		if (radeon_crtc->rmx_type != RMX_OFF)
			tv_rgb_cntl |= RADEON_RGB_SRC_SEL_RMX;
		else
			tv_rgb_cntl |= RADEON_RGB_SRC_SEL_CRTC1;
	}

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		vert_space = const_ptr->ver_total * 2 * 10000 / NTSC_TV_LINES_PER_FRAME;
	else
		vert_space = const_ptr->ver_total * 2 * 10000 / PAL_TV_LINES_PER_FRAME;

	tmp = RREG32(RADEON_TV_VSCALER_CNTL1);
	tmp &= 0xe3ff0000;
	tmp |= (vert_space * (1 << FRAC_BITS) / 10000);
	tv_vscaler_cntl1 = tmp;

	if (pll_ref_freq == 2700)
		tv_vscaler_cntl1 |= RADEON_RESTART_FIELD;

	if (const_ptr->hor_resolution == 1024)
		tv_vscaler_cntl1 |= (4 << RADEON_Y_DEL_W_SIG_SHIFT);
	else
		tv_vscaler_cntl1 |= (2 << RADEON_Y_DEL_W_SIG_SHIFT);

	/* scale up for int divide */
	tmp = const_ptr->ver_total * 2 * 1000;
	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60) {
		tmp /= NTSC_TV_LINES_PER_FRAME;
	} else {
		tmp /= PAL_TV_LINES_PER_FRAME;
	}
	flicker_removal = (tmp + 500) / 1000;

	if (flicker_removal < 3)
		flicker_removal = 3;
	for (i = 0; i < ARRAY_SIZE(SLOPE_limit); ++i) {
		if (flicker_removal == SLOPE_limit[i])
			break;
	}

	tv_y_saw_tooth_cntl = (vert_space * SLOPE_value[i] * (1 << (FRAC_BITS - 1)) +
				5001) / 10000 / 8 | ((SLOPE_value[i] *
				(1 << (FRAC_BITS - 1)) / 8) << 16);
	tv_y_fall_cntl =
		(YCOEF_EN_value[i] << 17) | ((YCOEF_value[i] * (1 << 8) / 8) << 24) |
		RADEON_Y_FALL_PING_PONG | (272 * SLOPE_value[i] / 8) * (1 << (FRAC_BITS - 1)) /
		1024;
	tv_y_rise_cntl = RADEON_Y_RISE_PING_PONG|
		(flicker_removal * 1024 - 272) * SLOPE_value[i] / 8 * (1 << (FRAC_BITS - 1)) / 1024;

	tv_vscaler_cntl2 = RREG32(RADEON_TV_VSCALER_CNTL2) & 0x00fffff0;
	tv_vscaler_cntl2 |= (0x10 << 24) |
		RADEON_DITHER_MODE |
		RADEON_Y_OUTPUT_DITHER_EN |
		RADEON_UV_OUTPUT_DITHER_EN |
		RADEON_UV_TO_BUF_DITHER_EN;

	tmp = (tv_vscaler_cntl1 >> RADEON_UV_INC_SHIFT) & RADEON_UV_INC_MASK;
	tmp = ((16384 * 256 * 10) / tmp + 5) / 10;
	tmp = (tmp << RADEON_UV_OUTPUT_POST_SCALE_SHIFT) | 0x000b0000;
	tv_dac->tv.timing_cntl = tmp;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60)
		tv_dac_cntl = tv_dac->ntsc_tvdac_adj;
	else
		tv_dac_cntl = tv_dac->pal_tvdac_adj;

	tv_dac_cntl |= RADEON_TV_DAC_NBLANK | RADEON_TV_DAC_NHOLD;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J)
		tv_dac_cntl |= RADEON_TV_DAC_STD_NTSC;
	else
		tv_dac_cntl |= RADEON_TV_DAC_STD_PAL;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J) {
		if (pll_ref_freq == 2700) {
			m = NTSC_TV_PLL_M_27;
			n = NTSC_TV_PLL_N_27;
			p = NTSC_TV_PLL_P_27;
		} else {
			m = NTSC_TV_PLL_M_14;
			n = NTSC_TV_PLL_N_14;
			p = NTSC_TV_PLL_P_14;
		}
	} else {
		if (pll_ref_freq == 2700) {
			m = PAL_TV_PLL_M_27;
			n = PAL_TV_PLL_N_27;
			p = PAL_TV_PLL_P_27;
		} else {
			m = PAL_TV_PLL_M_14;
			n = PAL_TV_PLL_N_14;
			p = PAL_TV_PLL_P_14;
		}
	}

	tv_pll_cntl = (m & RADEON_TV_M0LO_MASK) |
		(((m >> 8) & RADEON_TV_M0HI_MASK) << RADEON_TV_M0HI_SHIFT) |
		((n & RADEON_TV_N0LO_MASK) << RADEON_TV_N0LO_SHIFT) |
		(((n >> 9) & RADEON_TV_N0HI_MASK) << RADEON_TV_N0HI_SHIFT) |
		((p & RADEON_TV_P_MASK) << RADEON_TV_P_SHIFT);

	tv_pll_cntl1 = (((4 & RADEON_TVPCP_MASK) << RADEON_TVPCP_SHIFT) |
			((4 & RADEON_TVPVG_MASK) << RADEON_TVPVG_SHIFT) |
			((1 & RADEON_TVPDC_MASK) << RADEON_TVPDC_SHIFT) |
			RADEON_TVCLK_SRC_SEL_TVPLL |
			RADEON_TVPLL_TEST_DIS);

	tv_dac->tv.tv_uv_adr = 0xc8;

	if (tv_dac->tv_std == TV_STD_NTSC ||
	    tv_dac->tv_std == TV_STD_NTSC_J ||
	    tv_dac->tv_std == TV_STD_PAL_M ||
	    tv_dac->tv_std == TV_STD_PAL_60) {
		tv_ftotal = NTSC_TV_VFTOTAL;
		hor_timing = hor_timing_NTSC;
		vert_timing = vert_timing_NTSC;
	} else {
		hor_timing = hor_timing_PAL;
		vert_timing = vert_timing_PAL;
		tv_ftotal = PAL_TV_VFTOTAL;
	}

	for (i = 0; i < MAX_H_CODE_TIMING_LEN; i++) {
		if ((tv_dac->tv.h_code_timing[i] = hor_timing[i]) == 0)
			break;
	}

	for (i = 0; i < MAX_V_CODE_TIMING_LEN; i++) {
		if ((tv_dac->tv.v_code_timing[i] = vert_timing[i]) == 0)
			break;
	}

	radeon_legacy_tv_init_restarts(encoder);

	/* play with DAC_CNTL */
	/* play with GPIOPAD_A */
	/* DISP_OUTPUT_CNTL */
	/* use reference freq */

	/* program the TV registers */
	WREG32(RADEON_TV_MASTER_CNTL, (tv_master_cntl | RADEON_TV_ASYNC_RST |
				       RADEON_CRT_ASYNC_RST | RADEON_TV_FIFO_ASYNC_RST));

	tmp = RREG32(RADEON_TV_DAC_CNTL);
	tmp &= ~RADEON_TV_DAC_NBLANK;
	tmp |= RADEON_TV_DAC_BGSLEEP |
		RADEON_TV_DAC_RDACPD |
		RADEON_TV_DAC_GDACPD |
		RADEON_TV_DAC_BDACPD;
	WREG32(RADEON_TV_DAC_CNTL, tmp);

	/* TV PLL */
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~RADEON_TVCLK_SRC_SEL_TVPLL);
	WREG32_PLL(RADEON_TV_PLL_CNTL, tv_pll_cntl);
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, RADEON_TVPLL_RESET, ~RADEON_TVPLL_RESET);

	radeon_wait_pll_lock(encoder, 200, 800, 135);

	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~RADEON_TVPLL_RESET);

	radeon_wait_pll_lock(encoder, 300, 160, 27);
	radeon_wait_pll_lock(encoder, 200, 800, 135);

	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~0xf);
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, RADEON_TVCLK_SRC_SEL_TVPLL, ~RADEON_TVCLK_SRC_SEL_TVPLL);

	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, (1 << RADEON_TVPDC_SHIFT), ~RADEON_TVPDC_MASK);
	WREG32_PLL_P(RADEON_TV_PLL_CNTL1, 0, ~RADEON_TVPLL_SLEEP);

	/* TV HV */
	WREG32(RADEON_TV_RGB_CNTL, tv_rgb_cntl);
	WREG32(RADEON_TV_HTOTAL, const_ptr->hor_total - 1);
	WREG32(RADEON_TV_HDISP, const_ptr->hor_resolution - 1);
	WREG32(RADEON_TV_HSTART, const_ptr->hor_start);

	WREG32(RADEON_TV_VTOTAL, const_ptr->ver_total - 1);
	WREG32(RADEON_TV_VDISP, const_ptr->ver_resolution - 1);
	WREG32(RADEON_TV_FTOTAL, tv_ftotal);
	WREG32(RADEON_TV_VSCALER_CNTL1, tv_vscaler_cntl1);
	WREG32(RADEON_TV_VSCALER_CNTL2, tv_vscaler_cntl2);

	WREG32(RADEON_TV_Y_FALL_CNTL, tv_y_fall_cntl);
	WREG32(RADEON_TV_Y_RISE_CNTL, tv_y_rise_cntl);
	WREG32(RADEON_TV_Y_SAW_TOOTH_CNTL, tv_y_saw_tooth_cntl);

	WREG32(RADEON_TV_MASTER_CNTL, (tv_master_cntl | RADEON_TV_ASYNC_RST |
				       RADEON_CRT_ASYNC_RST));

	/* TV restarts */
	radeon_legacy_write_tv_restarts(radeon_encoder);

	/* tv timings */
	radeon_restore_tv_timing_tables(radeon_encoder);

	WREG32(RADEON_TV_MASTER_CNTL, (tv_master_cntl | RADEON_TV_ASYNC_RST));

	/* tv std */
	WREG32(RADEON_TV_SYNC_CNTL, (RADEON_SYNC_PUB | RADEON_TV_SYNC_IO_DRIVE));
	WREG32(RADEON_TV_TIMING_CNTL, tv_dac->tv.timing_cntl);
	WREG32(RADEON_TV_MODULATOR_CNTL1, tv_modulator_cntl1);
	WREG32(RADEON_TV_MODULATOR_CNTL2, tv_modulator_cntl2);
	WREG32(RADEON_TV_PRE_DAC_MUX_CNTL, (RADEON_Y_RED_EN |
					    RADEON_C_GRN_EN |
					    RADEON_CMP_BLU_EN |
					    RADEON_DAC_DITHER_EN));

	WREG32(RADEON_TV_CRC_CNTL, 0);

	WREG32(RADEON_TV_MASTER_CNTL, tv_master_cntl);

	WREG32(RADEON_TV_GAIN_LIMIT_SETTINGS, ((0x17f << RADEON_UV_GAIN_LIMIT_SHIFT) |
					       (0x5ff << RADEON_Y_GAIN_LIMIT_SHIFT)));
	WREG32(RADEON_TV_LINEAR_GAIN_SETTINGS, ((0x100 << RADEON_UV_GAIN_SHIFT) |
						(0x100 << RADEON_Y_GAIN_SHIFT)));

	WREG32(RADEON_TV_DAC_CNTL, tv_dac_cntl);

}