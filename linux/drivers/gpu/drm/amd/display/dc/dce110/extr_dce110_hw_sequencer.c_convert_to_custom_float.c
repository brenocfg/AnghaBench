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
typedef  scalar_t__ uint32_t ;
struct pwl_result_data {int /*<<< orphan*/  delta_blue_reg; int /*<<< orphan*/  delta_blue; int /*<<< orphan*/  delta_green_reg; int /*<<< orphan*/  delta_green; int /*<<< orphan*/  delta_red_reg; int /*<<< orphan*/  delta_red; int /*<<< orphan*/  blue_reg; int /*<<< orphan*/  blue; int /*<<< orphan*/  green_reg; int /*<<< orphan*/  green; int /*<<< orphan*/  red_reg; int /*<<< orphan*/  red; } ;
struct custom_float_format {int exponenta_bits; int mantissa_bits; int sign; } ;
struct curve_points {int /*<<< orphan*/  custom_float_slope; int /*<<< orphan*/  slope; int /*<<< orphan*/  custom_float_y; int /*<<< orphan*/  y; int /*<<< orphan*/  custom_float_x; int /*<<< orphan*/  x; int /*<<< orphan*/  custom_float_offset; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  convert_to_custom_float_format (int /*<<< orphan*/ ,struct custom_float_format*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool convert_to_custom_float(struct pwl_result_data *rgb_resulted,
				    struct curve_points *arr_points,
				    uint32_t hw_points_num)
{
	struct custom_float_format fmt;

	struct pwl_result_data *rgb = rgb_resulted;

	uint32_t i = 0;

	fmt.exponenta_bits = 6;
	fmt.mantissa_bits = 12;
	fmt.sign = true;

	if (!convert_to_custom_float_format(arr_points[0].x, &fmt,
					    &arr_points[0].custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!convert_to_custom_float_format(arr_points[0].offset, &fmt,
					    &arr_points[0].custom_float_offset)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!convert_to_custom_float_format(arr_points[0].slope, &fmt,
					    &arr_points[0].custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	fmt.mantissa_bits = 10;
	fmt.sign = false;

	if (!convert_to_custom_float_format(arr_points[1].x, &fmt,
					    &arr_points[1].custom_float_x)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!convert_to_custom_float_format(arr_points[1].y, &fmt,
					    &arr_points[1].custom_float_y)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	if (!convert_to_custom_float_format(arr_points[1].slope, &fmt,
					    &arr_points[1].custom_float_slope)) {
		BREAK_TO_DEBUGGER();
		return false;
	}

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