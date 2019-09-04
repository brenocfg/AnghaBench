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
struct dcn10_dpp {int dummy; } ;
struct dc_csc_transform {int enable_adjustment; int /*<<< orphan*/ * matrix; } ;
typedef  enum surface_pixel_format { ____Placeholder_surface_pixel_format } surface_pixel_format ;
typedef  enum pixel_format_description { ____Placeholder_pixel_format_description } pixel_format_description ;
typedef  enum expansion_mode { ____Placeholder_expansion_mode } expansion_mode ;
typedef  enum dcn10_input_csc_select { ____Placeholder_dcn10_input_csc_select } dcn10_input_csc_select ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;

/* Variables and functions */
 int /*<<< orphan*/  CNVC_BYPASS ; 
 int /*<<< orphan*/  CNVC_SURFACE_PIXEL_FORMAT ; 
 int COLOR_SPACE_SRGB ; 
 int COLOR_SPACE_YCBCR601 ; 
 int COLOR_SPACE_YCBCR709 ; 
 int /*<<< orphan*/  CUR0_ENABLE ; 
 int /*<<< orphan*/  CURSOR0_CONTROL ; 
 int /*<<< orphan*/  CURSOR_CONTROL ; 
 int /*<<< orphan*/  CURSOR_ENABLE ; 
 int /*<<< orphan*/  FORMAT_CONTROL ; 
 int /*<<< orphan*/  FORMAT_CONTROL__ALPHA_EN ; 
 int /*<<< orphan*/  FORMAT_EXPANSION_MODE ; 
 int INPUT_CSC_SELECT_BYPASS ; 
 int INPUT_CSC_SELECT_ICSC ; 
 int /*<<< orphan*/  OUTPUT_FP ; 
#define  PIXEL_FORMAT_FIXED 143 
#define  PIXEL_FORMAT_FIXED16 142 
#define  PIXEL_FORMAT_FLOAT 141 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR16161616F 140 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR2101010 139 
#define  SURFACE_PIXEL_FORMAT_GRPH_ABGR8888 138 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB1555 137 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616 136 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB16161616F 135 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB2101010 134 
#define  SURFACE_PIXEL_FORMAT_GRPH_ARGB8888 133 
#define  SURFACE_PIXEL_FORMAT_GRPH_RGB565 132 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCbCr 131 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_10bpc_YCrCb 130 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCbCr 129 
#define  SURFACE_PIXEL_FORMAT_VIDEO_420_YCrCb 128 
 struct dcn10_dpp* TO_DCN10_DPP (struct dpp*) ; 
 int /*<<< orphan*/  dpp1_program_input_csc (struct dpp*,int,int,struct out_csc_color_matrix*) ; 
 int /*<<< orphan*/  dpp1_set_degamma_format_float (struct dpp*,int) ; 
 int /*<<< orphan*/  dpp1_setup_format_flags (int,int*) ; 

void dpp1_cnv_setup (
		struct dpp *dpp_base,
		enum surface_pixel_format format,
		enum expansion_mode mode,
		struct dc_csc_transform input_csc_color_matrix,
		enum dc_color_space input_color_space)
{
	uint32_t pixel_format;
	uint32_t alpha_en;
	enum pixel_format_description fmt ;
	enum dc_color_space color_space;
	enum dcn10_input_csc_select select;
	bool is_float;
	struct dcn10_dpp *dpp = TO_DCN10_DPP(dpp_base);
	bool force_disable_cursor = false;
	struct out_csc_color_matrix tbl_entry;
	int i = 0;

	dpp1_setup_format_flags(format, &fmt);
	alpha_en = 1;
	pixel_format = 0;
	color_space = COLOR_SPACE_SRGB;
	select = INPUT_CSC_SELECT_BYPASS;
	is_float = false;

	switch (fmt) {
	case PIXEL_FORMAT_FIXED:
	case PIXEL_FORMAT_FIXED16:
	/*when output is float then FORMAT_CONTROL__OUTPUT_FP=1*/
		REG_SET_3(FORMAT_CONTROL, 0,
			CNVC_BYPASS, 0,
			FORMAT_EXPANSION_MODE, mode,
			OUTPUT_FP, 0);
		break;
	case PIXEL_FORMAT_FLOAT:
		REG_SET_3(FORMAT_CONTROL, 0,
			CNVC_BYPASS, 0,
			FORMAT_EXPANSION_MODE, mode,
			OUTPUT_FP, 1);
		is_float = true;
		break;
	default:

		break;
	}

	dpp1_set_degamma_format_float(dpp_base, is_float);

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
	default:
		break;
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
}