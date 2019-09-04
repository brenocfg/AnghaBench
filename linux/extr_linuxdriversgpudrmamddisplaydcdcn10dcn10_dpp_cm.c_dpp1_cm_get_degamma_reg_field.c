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
struct TYPE_7__ {int /*<<< orphan*/  exp_resion_start_segment; int /*<<< orphan*/  exp_region_start; int /*<<< orphan*/  field_region_linear_slope; int /*<<< orphan*/  field_region_end_base; int /*<<< orphan*/  field_region_end_slope; int /*<<< orphan*/  field_region_end; int /*<<< orphan*/  exp_region1_num_segments; int /*<<< orphan*/  exp_region1_lut_offset; int /*<<< orphan*/  exp_region0_num_segments; int /*<<< orphan*/  exp_region0_lut_offset; } ;
struct TYPE_5__ {int /*<<< orphan*/  exp_resion_start_segment; int /*<<< orphan*/  exp_region_start; int /*<<< orphan*/  field_region_linear_slope; int /*<<< orphan*/  field_region_end_base; int /*<<< orphan*/  field_region_end_slope; int /*<<< orphan*/  field_region_end; int /*<<< orphan*/  exp_region1_num_segments; int /*<<< orphan*/  exp_region1_lut_offset; int /*<<< orphan*/  exp_region0_num_segments; int /*<<< orphan*/  exp_region0_lut_offset; } ;
struct xfer_func_reg {TYPE_3__ masks; TYPE_1__ shifts; } ;
struct dcn10_dpp {TYPE_4__* tf_mask; TYPE_2__* tf_shift; } ;
struct TYPE_8__ {int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_START_SEGMENT_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_START_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_END_BASE_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_END_SLOPE_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_END_B; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION1_NUM_SEGMENTS; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION1_LUT_OFFSET; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION0_NUM_SEGMENTS; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION0_LUT_OFFSET; } ;
struct TYPE_6__ {int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_START_SEGMENT_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_START_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_END_BASE_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_END_SLOPE_B; int /*<<< orphan*/  CM_DGAM_RAMB_EXP_REGION_END_B; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION1_NUM_SEGMENTS; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION1_LUT_OFFSET; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION0_NUM_SEGMENTS; int /*<<< orphan*/  CM_DGAM_RAMA_EXP_REGION0_LUT_OFFSET; } ;

/* Variables and functions */

__attribute__((used)) static void dpp1_cm_get_degamma_reg_field(
		struct dcn10_dpp *dpp,
		struct xfer_func_reg *reg)
{
	reg->shifts.exp_region0_lut_offset = dpp->tf_shift->CM_DGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->masks.exp_region0_lut_offset = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION0_LUT_OFFSET;
	reg->shifts.exp_region0_num_segments = dpp->tf_shift->CM_DGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->masks.exp_region0_num_segments = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION0_NUM_SEGMENTS;
	reg->shifts.exp_region1_lut_offset = dpp->tf_shift->CM_DGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->masks.exp_region1_lut_offset = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION1_LUT_OFFSET;
	reg->shifts.exp_region1_num_segments = dpp->tf_shift->CM_DGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;
	reg->masks.exp_region1_num_segments = dpp->tf_mask->CM_DGAM_RAMA_EXP_REGION1_NUM_SEGMENTS;

	reg->shifts.field_region_end = dpp->tf_shift->CM_DGAM_RAMB_EXP_REGION_END_B;
	reg->masks.field_region_end = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_END_B;
	reg->shifts.field_region_end_slope = dpp->tf_shift->CM_DGAM_RAMB_EXP_REGION_END_SLOPE_B;
	reg->masks.field_region_end_slope = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_END_SLOPE_B;
	reg->shifts.field_region_end_base = dpp->tf_shift->CM_DGAM_RAMB_EXP_REGION_END_BASE_B;
	reg->masks.field_region_end_base = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_END_BASE_B;
	reg->shifts.field_region_linear_slope = dpp->tf_shift->CM_DGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B;
	reg->masks.field_region_linear_slope = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_LINEAR_SLOPE_B;
	reg->shifts.exp_region_start = dpp->tf_shift->CM_DGAM_RAMB_EXP_REGION_START_B;
	reg->masks.exp_region_start = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_START_B;
	reg->shifts.exp_resion_start_segment = dpp->tf_shift->CM_DGAM_RAMB_EXP_REGION_START_SEGMENT_B;
	reg->masks.exp_resion_start_segment = dpp->tf_mask->CM_DGAM_RAMB_EXP_REGION_START_SEGMENT_B;
}