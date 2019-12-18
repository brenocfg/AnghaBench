#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct pwl_result_data {void* delta_blue_reg; int /*<<< orphan*/  delta_blue; void* delta_green_reg; int /*<<< orphan*/  delta_green; void* delta_red_reg; int /*<<< orphan*/  delta_red; void* blue_reg; int /*<<< orphan*/  blue; void* green_reg; int /*<<< orphan*/  green; void* red_reg; int /*<<< orphan*/  red; } ;
struct custom_float_format {int exponenta_bits; int mantissa_bits; int sign; } ;
struct TYPE_5__ {void* custom_float_slope; int /*<<< orphan*/  slope; void* custom_float_y; int /*<<< orphan*/  y; void* custom_float_x; int /*<<< orphan*/  x; void* custom_float_offset; int /*<<< orphan*/  offset; } ;
struct TYPE_4__ {void* custom_float_slope; int /*<<< orphan*/  slope; void* custom_float_y; int /*<<< orphan*/  y; void* custom_float_x; int /*<<< orphan*/  x; void* custom_float_offset; int /*<<< orphan*/  offset; } ;
struct TYPE_6__ {void* custom_float_slope; int /*<<< orphan*/  slope; void* custom_float_y; int /*<<< orphan*/  y; void* custom_float_x; int /*<<< orphan*/  x; void* custom_float_offset; int /*<<< orphan*/  offset; } ;
struct curve_points3 {TYPE_2__ blue; TYPE_1__ green; TYPE_3__ red; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  convert_to_custom_float_format (int /*<<< orphan*/ ,struct custom_float_format*,void**) ; 
 void* dc_fixpt_clamp_u0d14 (int /*<<< orphan*/ ) ; 

bool cm_helper_convert_to_custom_float(
		struct pwl_result_data *rgb_resulted,
		struct curve_points3 *corner_points,
		uint32_t hw_points_num,
		bool fixpoint)
{
	struct custom_float_format fmt;

	struct pwl_result_data *rgb = rgb_resulted;

	uint32_t i = 0;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = false;

	/* corner_points[0] - beginning base, slope offset for R,G,B
	 * corner_points[1] - end base, slope offset for R,G,B
	 */
	if (!convert_to_custom_float_format(corner_points[0].red.x, &fmt,
				&corner_points[0].red.custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[0].green.x, &fmt,
				&corner_points[0].green.custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[0].blue.x, &fmt,
				&corner_points[0].blue.custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!convert_to_custom_float_format(corner_points[0].red.offset, &fmt,
				&corner_points[0].red.custom_float_offset)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[0].green.offset, &fmt,
				&corner_points[0].green.custom_float_offset)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[0].blue.offset, &fmt,
				&corner_points[0].blue.custom_float_offset)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!convert_to_custom_float_format(corner_points[0].red.slope, &fmt,
				&corner_points[0].red.custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[0].green.slope, &fmt,
				&corner_points[0].green.custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[0].blue.slope, &fmt,
				&corner_points[0].blue.custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	fmt.mantissa_bits = 10;
	fmt.sign = false;

	if (!convert_to_custom_float_format(corner_points[1].red.x, &fmt,
				&corner_points[1].red.custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[1].green.x, &fmt,
				&corner_points[1].green.custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[1].blue.x, &fmt,
				&corner_points[1].blue.custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (fixpoint == true) {
		corner_points[1].red.custom_float_y =
				dc_fixpt_clamp_u0d14(corner_points[1].red.y);
		corner_points[1].green.custom_float_y =
				dc_fixpt_clamp_u0d14(corner_points[1].green.y);
		corner_points[1].blue.custom_float_y =
				dc_fixpt_clamp_u0d14(corner_points[1].blue.y);
	} else {
		if (!convert_to_custom_float_format(corner_points[1].red.y,
				&fmt, &corner_points[1].red.custom_float_y)) {
			BREAK_TO_DEBUGGER();
			return false;
		}
		if (!convert_to_custom_float_format(corner_points[1].green.y,
				&fmt, &corner_points[1].green.custom_float_y)) {
			BREAK_TO_DEBUGGER();
			return false;
		}
		if (!convert_to_custom_float_format(corner_points[1].blue.y,
				&fmt, &corner_points[1].blue.custom_float_y)) {
			BREAK_TO_DEBUGGER();
			return false;
		}
	}

	if (!convert_to_custom_float_format(corner_points[1].red.slope, &fmt,
				&corner_points[1].red.custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[1].green.slope, &fmt,
				&corner_points[1].green.custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}
	if (!convert_to_custom_float_format(corner_points[1].blue.slope, &fmt,
				&corner_points[1].blue.custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (hw_points_num == 0 || rgb_resulted == NULL || fixpoint == true)
		return true;

	fmt.mantissa_bits = 12;
	fmt.sign = true;

	while (i != hw_points_num) {
		if (!convert_to_custom_float_format(rgb->red, &fmt,
						    &rgb->red_reg)) {
			BREAK_TO_DEBUGGER();
			return false;
		}

		if (!convert_to_custom_float_format(rgb->green, &fmt,
						    &rgb->green_reg)) {
			BREAK_TO_DEBUGGER();
			return false;
		}

		if (!convert_to_custom_float_format(rgb->blue, &fmt,
						    &rgb->blue_reg)) {
			BREAK_TO_DEBUGGER();
			return false;
		}

		if (!convert_to_custom_float_format(rgb->delta_red, &fmt,
						    &rgb->delta_red_reg)) {
			BREAK_TO_DEBUGGER();
			return false;
		}

		if (!convert_to_custom_float_format(rgb->delta_green, &fmt,
						    &rgb->delta_green_reg)) {
			BREAK_TO_DEBUGGER();
			return false;
		}

		if (!convert_to_custom_float_format(rgb->delta_blue, &fmt,
						    &rgb->delta_blue_reg)) {
			BREAK_TO_DEBUGGER();
			return false;
		}

		++rgb;
		++i;
	}

	return true;
}