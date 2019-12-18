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
struct out_csc_color_matrix {int color_space; int /*<<< orphan*/ * regval; } ;
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;
struct dc_csc_transform {int enable_adjustment; int /*<<< orphan*/ * matrix; } ;
struct cnv_alpha_2bit_lut {int lut0; int lut1; int lut2; int lut3; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
typedef  enum expansion_mode { ____Placeholder_expansion_mode } expansion_mode ;
typedef  enum dcn10_input_csc_select { ____Placeholder_dcn10_input_csc_select } dcn10_input_csc_select ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_2BIT_LUT ; 
 int /*<<< orphan*/  ALPHA_2BIT_LUT0 ; 
 int /*<<< orphan*/  ALPHA_2BIT_LUT1 ; 
 int /*<<< orphan*/  ALPHA_2BIT_LUT2 ; 
 int /*<<< orphan*/  ALPHA_2BIT_LUT3 ; 
 int /*<<< orphan*/  CLAMP_POSITIVE ; 
 int /*<<< orphan*/  CLAMP_POSITIVE_C ; 
 int /*<<< orphan*/  CNVC_BYPASS ; 
 int /*<<< orphan*/  CNVC_BYPASS_MSB_ALIGN ; 
 int /*<<< orphan*/  CNVC_SURFACE_PIXEL_FORMAT ; 
 int COLOR_SPACE_SRGB ; 
 int COLOR_SPACE_YCBCR601 ; 
 int COLOR_SPACE_YCBCR709 ; 
 int /*<<< orphan*/  CUR0_ENABLE ; 
 int /*<<< orphan*/  CURSOR0_CONTROL ; 
 int /*<<< orphan*/  CURSOR_CONTROL ; 
 int /*<<< orphan*/  CURSOR_ENABLE ; 
 int /*<<< orphan*/  FORMAT_CNV16 ; 
 int /*<<< orphan*/  FORMAT_CONTROL ; 
 int /*<<< orphan*/  FORMAT_CONTROL__ALPHA_EN ; 
 int /*<<< orphan*/  FORMAT_EXPANSION_MODE ; 
 int INPUT_CSC_SELECT_BYPASS ; 
 int INPUT_CSC_SELECT_ICSC ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 147 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 146 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 145 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 144 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 143 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 142 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 141 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 140 
#define  SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX 139 
#define  SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 135 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr 134 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb 133 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 132 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 131 
#define  SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_AYCrCb8888 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_CrYCbA1010102 128 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 
 int /*<<< orphan*/  dpp1_program_input_csc (struct dpp*,int,int,struct out_csc_color_matrix*) ; 
 int /*<<< orphan*/  dpp2_power_on_obuf (struct dpp*,int) ; 

__attribute__((used)) static void dpp2_cnv_setup (
		struct dpp *dpp_base,
		enum surface_pixel_format format,
		enum expansion_mode mode,
		struct dc_csc_transform input_csc_color_matrix,
		enum dc_color_space input_color_space,
		struct cnv_alpha_2bit_lut *alpha_2bit_lut)
{
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);
	uint32_t pixel_format = 0;
	uint32_t alpha_en = 1;
	enum dc_color_space color_space = COLOR_SPACE_SRGB;
	enum dcn10_input_csc_select select = INPUT_CSC_SELECT_BYPASS;
	bool force_disable_cursor = false;
	struct out_csc_color_matrix tbl_entry;
	uint32_t is_2bit = 0;
	int i = 0;

	REG_SET_2(FORMAT_CONTROL, 0,
		CNVC_BYPASS, 0,
		FORMAT_EXPANSION_MODE, mode);

	//hardcode default
    //FORMAT_CONTROL. FORMAT_CNV16                                 	default 0: U0.16/S.1.15;         1: U1.15/ S.1.14
    //FORMAT_CONTROL. CNVC_BYPASS_MSB_ALIGN          				default 0: disabled              1: enabled
    //FORMAT_CONTROL. CLAMP_POSITIVE                               	default 0: disabled              1: enabled
    //FORMAT_CONTROL. CLAMP_POSITIVE_C                          	default 0: disabled              1: enabled
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CNV16, 0);
	REG_UPDATE(FORMAT_CONTROL, CNVC_BYPASS_MSB_ALIGN, 0);
	REG_UPDATE(FORMAT_CONTROL, CLAMP_POSITIVE, 0);
	REG_UPDATE(FORMAT_CONTROL, CLAMP_POSITIVE_C, 0);

	switch (format) {
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB1555:
		pixel_format = 1;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_RGB565:
		pixel_format = 3;
		alpha_en = 0;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB8888:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR8888:
		pixel_format = 8;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010:
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010:
		pixel_format = 10;
		is_2bit = 1;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr:
		force_disable_cursor = false;
		pixel_format = 65;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb:
		force_disable_cursor = true;
		pixel_format = 64;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr:
		force_disable_cursor = true;
		pixel_format = 67;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb:
		force_disable_cursor = true;
		pixel_format = 66;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616:
		pixel_format = 22;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F:
		pixel_format = 24;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F:
		pixel_format = 25;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_AYCrCb8888:
		pixel_format = 12;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FIX:
		pixel_format = 112;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FIX:
		pixel_format = 113;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_ACrYCb2101010:
		pixel_format = 114;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		is_2bit = 1;
		break;
	case SURFACE_PIXEL_FORMAT_VIDEO_CrYCbA1010102:
		pixel_format = 115;
		color_space = COLOR_SPACE_YCBCR709;
		select = INPUT_CSC_SELECT_ICSC;
		is_2bit = 1;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_RGB111110_FLOAT:
		pixel_format = 118;
		break;
	case SURFACE_PIXEL_FORMAT_GRPH_BGR101111_FLOAT:
		pixel_format = 119;
		break;
	default:
		break;
	}

	if (is_2bit == 1 && alpha_2bit_lut != NULL) {
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT0, alpha_2bit_lut->lut0);
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT1, alpha_2bit_lut->lut1);
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT2, alpha_2bit_lut->lut2);
		REG_UPDATE(ALPHA_2BIT_LUT, ALPHA_2BIT_LUT3, alpha_2bit_lut->lut3);
	}

	REG_SET(CNVC_SURFACE_PIXEL_FORMAT, 0,
			CNVC_SURFACE_PIXEL_FORMAT, pixel_format);
	REG_UPDATE(FORMAT_CONTROL, FORMAT_CONTROL__ALPHA_EN, alpha_en);

	// if input adjustments exist, program icsc with those values
	if (input_csc_color_matrix.enable_adjustment
				== true) {
		for (i = 0; i < 12; i++)
			tbl_entry.regval[i] = input_csc_color_matrix.matrix[i];

		tbl_entry.color_space = input_color_space;

		if (color_space >= COLOR_SPACE_YCBCR601)
			select = INPUT_CSC_SELECT_ICSC;
		else
			select = INPUT_CSC_SELECT_BYPASS;

		dpp1_program_input_csc(dpp_base, color_space, select, &tbl_entry);
	} else
	dpp1_program_input_csc(dpp_base, color_space, select, NULL);

	if (force_disable_cursor) {
		REG_UPDATE(CURSOR_CONTROL,
				CURSOR_ENABLE, 0);
		REG_UPDATE(CURSOR0_CONTROL,
				CUR0_ENABLE, 0);

	}
	dpp2_power_on_obuf(dpp_base, true);

}