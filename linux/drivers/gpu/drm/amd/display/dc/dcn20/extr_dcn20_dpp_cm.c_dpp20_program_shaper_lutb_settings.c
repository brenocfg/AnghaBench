#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pwl_params {struct gamma_curve* arr_curve_points; TYPE_4__* corner_points; } ;
struct gamma_curve {int /*<<< orphan*/  segments_num; int /*<<< orphan*/  offset; } ;
struct dpp {int dummy; } ;
struct dcn20_dpp {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  custom_float_y; int /*<<< orphan*/  custom_float_x; } ;
struct TYPE_6__ {int /*<<< orphan*/  custom_float_y; int /*<<< orphan*/  custom_float_x; } ;
struct TYPE_5__ {int /*<<< orphan*/  custom_float_y; int /*<<< orphan*/  custom_float_x; } ;
struct TYPE_8__ {TYPE_3__ red; TYPE_2__ green; TYPE_1__ blue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_SHAPER_RAMB_END_CNTL_B ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_END_CNTL_G ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_END_CNTL_R ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION0_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION0_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION10_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION10_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION11_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION11_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION12_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION12_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION13_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION13_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION14_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION14_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION15_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION15_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION16_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION16_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION17_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION17_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION18_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION18_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION19_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION19_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION1_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION1_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION20_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION20_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION21_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION21_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION22_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION22_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION23_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION23_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION24_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION24_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION25_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION25_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION26_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION26_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION27_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION27_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION28_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION28_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION29_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION29_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION2_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION2_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION30_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION30_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION31_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION31_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION32_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION32_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION33_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION33_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION3_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION3_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION4_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION4_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION5_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION5_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION6_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION6_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION7_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION7_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION8_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION8_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION9_LUT_OFFSET ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION9_NUM_SEGMENTS ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_END_B ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_END_BASE_B ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_END_BASE_G ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_END_BASE_R ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_END_G ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_END_R ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_START_B ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_START_G ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_START_R ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_B ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_G ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_R ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_0_1 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_10_11 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_12_13 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_14_15 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_16_17 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_18_19 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_20_21 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_22_23 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_24_25 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_26_27 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_28_29 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_2_3 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_30_31 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_32_33 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_4_5 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_6_7 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_REGION_8_9 ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_START_CNTL_B ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_START_CNTL_G ; 
 int /*<<< orphan*/  CM_SHAPER_RAMB_START_CNTL_R ; 
 int /*<<< orphan*/  REG_SET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn20_dpp* TO_DCN20_DPP (struct dpp*) ; 

__attribute__((used)) static void dpp20_program_shaper_lutb_settings(
		struct dpp *dpp_base,
		const struct pwl_params *params)
{
	const struct gamma_curve *curve;
	struct dcn20_dpp *dpp = TO_DCN20_DPP(dpp_base);

	REG_SET_2(CM_SHAPER_RAMB_START_CNTL_B, 0,
		CM_SHAPER_RAMB_EXP_REGION_START_B, params->corner_points[0].blue.custom_float_x,
		CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_B, 0);
	REG_SET_2(CM_SHAPER_RAMB_START_CNTL_G, 0,
		CM_SHAPER_RAMB_EXP_REGION_START_G, params->corner_points[0].green.custom_float_x,
		CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_G, 0);
	REG_SET_2(CM_SHAPER_RAMB_START_CNTL_R, 0,
		CM_SHAPER_RAMB_EXP_REGION_START_R, params->corner_points[0].red.custom_float_x,
		CM_SHAPER_RAMB_EXP_REGION_START_SEGMENT_R, 0);

	REG_SET_2(CM_SHAPER_RAMB_END_CNTL_B, 0,
		CM_SHAPER_RAMB_EXP_REGION_END_B, params->corner_points[1].blue.custom_float_x,
		CM_SHAPER_RAMB_EXP_REGION_END_BASE_B, params->corner_points[1].blue.custom_float_y);

	REG_SET_2(CM_SHAPER_RAMB_END_CNTL_G, 0,
		CM_SHAPER_RAMB_EXP_REGION_END_G, params->corner_points[1].green.custom_float_x,
		CM_SHAPER_RAMB_EXP_REGION_END_BASE_G, params->corner_points[1].green.custom_float_y);

	REG_SET_2(CM_SHAPER_RAMB_END_CNTL_R, 0,
		CM_SHAPER_RAMB_EXP_REGION_END_R, params->corner_points[1].red.custom_float_x,
		CM_SHAPER_RAMB_EXP_REGION_END_BASE_R, params->corner_points[1].red.custom_float_y);

	curve = params->arr_curve_points;
	REG_SET_4(CM_SHAPER_RAMB_REGION_0_1, 0,
		CM_SHAPER_RAMB_EXP_REGION0_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION0_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION1_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION1_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_2_3, 0,
		CM_SHAPER_RAMB_EXP_REGION2_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION2_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION3_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION3_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_4_5, 0,
		CM_SHAPER_RAMB_EXP_REGION4_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION4_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION5_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION5_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_6_7, 0,
		CM_SHAPER_RAMB_EXP_REGION6_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION6_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION7_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION7_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_8_9, 0,
		CM_SHAPER_RAMB_EXP_REGION8_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION8_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION9_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION9_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_10_11, 0,
		CM_SHAPER_RAMB_EXP_REGION10_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION10_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION11_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION11_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_12_13, 0,
		CM_SHAPER_RAMB_EXP_REGION12_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION12_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION13_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION13_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_14_15, 0,
		CM_SHAPER_RAMB_EXP_REGION14_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION14_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION15_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION15_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_16_17, 0,
		CM_SHAPER_RAMB_EXP_REGION16_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION16_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION17_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION17_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_18_19, 0,
		CM_SHAPER_RAMB_EXP_REGION18_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION18_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION19_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION19_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_20_21, 0,
		CM_SHAPER_RAMB_EXP_REGION20_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION20_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION21_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION21_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_22_23, 0,
		CM_SHAPER_RAMB_EXP_REGION22_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION22_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION23_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION23_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_24_25, 0,
		CM_SHAPER_RAMB_EXP_REGION24_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION24_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION25_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION25_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_26_27, 0,
		CM_SHAPER_RAMB_EXP_REGION26_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION26_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION27_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION27_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_28_29, 0,
		CM_SHAPER_RAMB_EXP_REGION28_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION28_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION29_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION29_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_30_31, 0,
		CM_SHAPER_RAMB_EXP_REGION30_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION30_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION31_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION31_NUM_SEGMENTS, curve[1].segments_num);

	curve += 2;
	REG_SET_4(CM_SHAPER_RAMB_REGION_32_33, 0,
		CM_SHAPER_RAMB_EXP_REGION32_LUT_OFFSET, curve[0].offset,
		CM_SHAPER_RAMB_EXP_REGION32_NUM_SEGMENTS, curve[0].segments_num,
		CM_SHAPER_RAMB_EXP_REGION33_LUT_OFFSET, curve[1].offset,
		CM_SHAPER_RAMB_EXP_REGION33_NUM_SEGMENTS, curve[1].segments_num);

}