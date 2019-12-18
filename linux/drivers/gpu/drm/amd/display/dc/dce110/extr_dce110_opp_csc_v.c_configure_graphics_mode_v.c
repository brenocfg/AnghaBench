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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {struct dc_context* ctx; } ;
struct dce_transform {TYPE_1__ base; } ;
struct dc_context {int dummy; } ;
typedef  enum graphics_csc_adjust_type { ____Placeholder_graphics_csc_adjust_type } graphics_csc_adjust_type ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
typedef  enum csc_color_mode { ____Placeholder_csc_color_mode } csc_color_mode ;

/* Variables and functions */
#define  COLOR_SPACE_SRGB 133 
#define  COLOR_SPACE_SRGB_LIMITED 132 
#define  COLOR_SPACE_YCBCR601 131 
#define  COLOR_SPACE_YCBCR601_LIMITED 130 
#define  COLOR_SPACE_YCBCR709 129 
#define  COLOR_SPACE_YCBCR709_LIMITED 128 
 int /*<<< orphan*/  COL_MAN_OUTPUT_CSC_CONTROL ; 
 int CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC ; 
 int GRAPHICS_CSC_ADJUST_TYPE_HW ; 
 int GRAPHICS_CSC_ADJUST_TYPE_SW ; 
 int /*<<< orphan*/  OUTPUT_CSC_MODE ; 
 int /*<<< orphan*/  dm_read_reg (struct dc_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_write_reg (struct dc_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmCOL_MAN_OUTPUT_CSC_CONTROL ; 
 int /*<<< orphan*/  set_reg_field_value (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool configure_graphics_mode_v(
	struct dce_transform *xfm_dce,
	enum csc_color_mode config,
	enum graphics_csc_adjust_type csc_adjust_type,
	enum dc_color_space color_space)
{
	struct dc_context *ctx = xfm_dce->base.ctx;
	uint32_t addr = mmCOL_MAN_OUTPUT_CSC_CONTROL;
	uint32_t value = dm_read_reg(ctx, addr);

	set_reg_field_value(
		value,
		0,
		COL_MAN_OUTPUT_CSC_CONTROL,
		OUTPUT_CSC_MODE);

	if (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_SW) {
		if (config == CSC_COLOR_MODE_GRAPHICS_OUTPUT_CSC)
			return true;

		switch (color_space) {
		case COLOR_SPACE_SRGB:
			/* by pass */
			set_reg_field_value(
				value,
				0,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			break;
		case COLOR_SPACE_SRGB_LIMITED:
			/* not supported for underlay on CZ */
			return false;

		case COLOR_SPACE_YCBCR601_LIMITED:
			/* YCbCr601 */
			set_reg_field_value(
				value,
				2,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			break;
		case COLOR_SPACE_YCBCR709:
		case COLOR_SPACE_YCBCR709_LIMITED:
			/* YCbCr709 */
			set_reg_field_value(
				value,
				3,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			break;
		default:
			return false;
		}

	} else if (csc_adjust_type == GRAPHICS_CSC_ADJUST_TYPE_HW) {
		switch (color_space) {
		case COLOR_SPACE_SRGB:
			/* by pass */
			set_reg_field_value(
				value,
				0,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			break;
		case COLOR_SPACE_SRGB_LIMITED:
			/* not supported for underlay on CZ */
			return false;
		case COLOR_SPACE_YCBCR601:
		case COLOR_SPACE_YCBCR601_LIMITED:
			/* YCbCr601 */
			set_reg_field_value(
				value,
				2,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			break;
		case COLOR_SPACE_YCBCR709:
		case COLOR_SPACE_YCBCR709_LIMITED:
			 /* YCbCr709 */
			set_reg_field_value(
				value,
				3,
				COL_MAN_OUTPUT_CSC_CONTROL,
				OUTPUT_CSC_MODE);
			break;
		default:
			return false;
		}

	} else
		/* by pass */
		set_reg_field_value(
			value,
			0,
			COL_MAN_OUTPUT_CSC_CONTROL,
			OUTPUT_CSC_MODE);

	addr = mmCOL_MAN_OUTPUT_CSC_CONTROL;
	dm_write_reg(ctx, addr, value);

	return true;
}