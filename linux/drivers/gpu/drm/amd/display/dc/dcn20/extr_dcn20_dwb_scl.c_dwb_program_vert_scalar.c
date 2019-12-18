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
typedef  int /*<<< orphan*/  uint16_t ;
struct scaling_taps {int v_taps; int v_taps_c; } ;
struct fixed31_32 {int dummy; } ;
struct dcn20_dwbc {int dummy; } ;
typedef  int int32_t ;
typedef  enum dwb_subsample_position { ____Placeholder_dwb_subsample_position } dwb_subsample_position ;

/* Variables and functions */
 int DWB_COSITED_SUBSAMPLING ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WBSCL_COEF_CHROMA_VERT_FILTER ; 
 int /*<<< orphan*/  WBSCL_COEF_LUMA_VERT_FILTER ; 
 int /*<<< orphan*/  WBSCL_TAP_CONTROL ; 
 int /*<<< orphan*/  WBSCL_VERT_FILTER_INIT_CBCR ; 
 int /*<<< orphan*/  WBSCL_VERT_FILTER_INIT_Y_RGB ; 
 int /*<<< orphan*/  WBSCL_VERT_FILTER_SCALE_RATIO ; 
 int /*<<< orphan*/  WBSCL_V_INIT_FRAC_CBCR ; 
 int /*<<< orphan*/  WBSCL_V_INIT_FRAC_Y_RGB ; 
 int /*<<< orphan*/  WBSCL_V_INIT_INT_CBCR ; 
 int /*<<< orphan*/  WBSCL_V_INIT_INT_Y_RGB ; 
 int /*<<< orphan*/  WBSCL_V_NUM_OF_TAPS_CBCR ; 
 int /*<<< orphan*/  WBSCL_V_NUM_OF_TAPS_Y_RGB ; 
 int /*<<< orphan*/  WBSCL_V_SCALE_RATIO ; 
 struct fixed31_32 dc_fixpt_add (struct fixed31_32,struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_add_int (struct fixed31_32,int) ; 
 struct fixed31_32 dc_fixpt_div_int (struct fixed31_32,int) ; 
 int dc_fixpt_floor (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int,int) ; 
 struct fixed31_32 dc_fixpt_from_int (int) ; 
 struct fixed31_32 dc_fixpt_mul_int (struct fixed31_32,int) ; 
 int dc_fixpt_s4d19 (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_sub_int (struct fixed31_32,int) ; 
 int dc_fixpt_u3d19 (struct fixed31_32) ; 
 int /*<<< orphan*/ * wbscl_get_filter_coeffs_16p (int,struct fixed31_32) ; 
 int /*<<< orphan*/  wbscl_set_scaler_filter (struct dcn20_dwbc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

bool dwb_program_vert_scalar(struct dcn20_dwbc *dwbc20,
		uint32_t src_height,
		uint32_t dest_height,
		struct scaling_taps num_taps,
		enum dwb_subsample_position subsample_position)
{
	uint32_t v_ratio_luma = 1;
	uint32_t v_ratio_chroma = 1;
	uint32_t v_taps_luma = num_taps.v_taps;
	uint32_t v_taps_chroma = num_taps.v_taps_c;
	int32_t v_init_phase_luma = 0;
	int32_t v_init_phase_chroma = 0;
	uint32_t v_init_phase_luma_int = 0;
	uint32_t v_init_phase_luma_frac = 0;
	uint32_t v_init_phase_chroma_int = 0;
	uint32_t v_init_phase_chroma_frac = 0;

	const uint16_t *filter_v = NULL;
	const uint16_t *filter_v_c = NULL;

	struct fixed31_32 tmp_v_init_phase_luma = dc_fixpt_from_int(0);
	struct fixed31_32 tmp_v_init_phase_chroma = dc_fixpt_from_int(0);

	/*Calculate ratio*/
	struct fixed31_32 tmp_v_ratio_luma = dc_fixpt_from_fraction(
		src_height, dest_height);

	if (dc_fixpt_floor(tmp_v_ratio_luma) == 8)
		v_ratio_luma = -1;
	else
		v_ratio_luma = dc_fixpt_u3d19(tmp_v_ratio_luma) << 5;
	v_ratio_chroma = v_ratio_luma * 2;

	/*Program ratio*/
	REG_UPDATE(WBSCL_VERT_FILTER_SCALE_RATIO, WBSCL_V_SCALE_RATIO, v_ratio_luma);

	/* Program taps*/
	REG_UPDATE(WBSCL_TAP_CONTROL, WBSCL_V_NUM_OF_TAPS_Y_RGB, v_taps_luma - 1);
	REG_UPDATE(WBSCL_TAP_CONTROL, WBSCL_V_NUM_OF_TAPS_CBCR, v_taps_chroma - 1);

	/* Calculate phase*/
	tmp_v_init_phase_luma = dc_fixpt_add_int(tmp_v_ratio_luma, v_taps_luma + 1);
	tmp_v_init_phase_luma = dc_fixpt_div_int(tmp_v_init_phase_luma, 2);
	tmp_v_init_phase_luma = dc_fixpt_sub_int(tmp_v_init_phase_luma, v_taps_luma);

	v_init_phase_luma = dc_fixpt_s4d19(tmp_v_init_phase_luma);
	v_init_phase_luma_int = (v_init_phase_luma >> 19) & 0x1f;
	v_init_phase_luma_frac = (v_init_phase_luma & 0x7ffff) << 5;

	tmp_v_init_phase_chroma = dc_fixpt_mul_int(tmp_v_ratio_luma, 2);
	tmp_v_init_phase_chroma = dc_fixpt_add_int(tmp_v_init_phase_chroma, v_taps_chroma + 1);
	tmp_v_init_phase_chroma = dc_fixpt_div_int(tmp_v_init_phase_chroma, 2);
	tmp_v_init_phase_chroma = dc_fixpt_sub_int(tmp_v_init_phase_chroma, v_taps_chroma);
	if (subsample_position == DWB_COSITED_SUBSAMPLING)
		tmp_v_init_phase_chroma = dc_fixpt_add(tmp_v_init_phase_chroma, dc_fixpt_from_fraction(1, 4));

	v_init_phase_chroma = dc_fixpt_s4d19(tmp_v_init_phase_chroma);
	v_init_phase_chroma_int = (v_init_phase_chroma >> 19) & 0x1f;
	v_init_phase_chroma_frac = (v_init_phase_chroma & 0x7ffff) << 5;

	/* Program phase*/
	REG_UPDATE(WBSCL_VERT_FILTER_INIT_Y_RGB, WBSCL_V_INIT_INT_Y_RGB, v_init_phase_luma_int);
	REG_UPDATE(WBSCL_VERT_FILTER_INIT_Y_RGB, WBSCL_V_INIT_FRAC_Y_RGB, v_init_phase_luma_frac);
	REG_UPDATE(WBSCL_VERT_FILTER_INIT_CBCR, WBSCL_V_INIT_INT_CBCR, v_init_phase_chroma_int);
	REG_UPDATE(WBSCL_VERT_FILTER_INIT_CBCR, WBSCL_V_INIT_FRAC_CBCR, v_init_phase_chroma_frac);


	/* Program LUT coefficients*/
	filter_v  = wbscl_get_filter_coeffs_16p(
		v_taps_luma, tmp_v_ratio_luma);
	filter_v_c = wbscl_get_filter_coeffs_16p(
		v_taps_chroma, dc_fixpt_from_int(v_ratio_luma * 2));
	wbscl_set_scaler_filter(dwbc20, v_taps_luma,
		WBSCL_COEF_LUMA_VERT_FILTER, filter_v);

	wbscl_set_scaler_filter(dwbc20, v_taps_chroma,
		WBSCL_COEF_CHROMA_VERT_FILTER, filter_v_c);
	return true;
}