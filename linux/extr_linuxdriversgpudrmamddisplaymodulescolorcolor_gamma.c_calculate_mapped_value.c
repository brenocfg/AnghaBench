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
typedef  size_t uint32_t ;
struct pwl_float_data {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct gamma_point {size_t left_index; size_t right_index; scalar_t__ pos; int /*<<< orphan*/  coeff; } ;
struct pixel_gamma_point {struct gamma_point b; struct gamma_point g; struct gamma_point r; } ;
struct fixed31_32 {int dummy; } ;
typedef  enum channel_name { ____Placeholder_channel_name } channel_name ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int CHANNEL_NAME_GREEN ; 
 int CHANNEL_NAME_RED ; 
 scalar_t__ HW_POINT_POSITION_LEFT ; 
 scalar_t__ HW_POINT_POSITION_MIDDLE ; 
 struct fixed31_32 dc_fixpt_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_fixpt_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_one ; 
 int /*<<< orphan*/  dc_fixpt_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_zero ; 

__attribute__((used)) static struct fixed31_32 calculate_mapped_value(
	struct pwl_float_data *rgb,
	const struct pixel_gamma_point *coeff,
	enum channel_name channel,
	uint32_t max_index)
{
	const struct gamma_point *point;

	struct fixed31_32 result;

	if (channel == CHANNEL_NAME_RED)
		point = &coeff->r;
	else if (channel == CHANNEL_NAME_GREEN)
		point = &coeff->g;
	else
		point = &coeff->b;

	if ((point->left_index < 0) || (point->left_index > max_index)) {
		BREAK_TO_DEBUGGER();
		return dc_fixpt_zero;
	}

	if ((point->right_index < 0) || (point->right_index > max_index)) {
		BREAK_TO_DEBUGGER();
		return dc_fixpt_zero;
	}

	if (point->pos == HW_POINT_POSITION_MIDDLE)
		if (channel == CHANNEL_NAME_RED)
			result = dc_fixpt_add(
				dc_fixpt_mul(
					point->coeff,
					dc_fixpt_sub(
						rgb[point->right_index].r,
						rgb[point->left_index].r)),
				rgb[point->left_index].r);
		else if (channel == CHANNEL_NAME_GREEN)
			result = dc_fixpt_add(
				dc_fixpt_mul(
					point->coeff,
					dc_fixpt_sub(
						rgb[point->right_index].g,
						rgb[point->left_index].g)),
				rgb[point->left_index].g);
		else
			result = dc_fixpt_add(
				dc_fixpt_mul(
					point->coeff,
					dc_fixpt_sub(
						rgb[point->right_index].b,
						rgb[point->left_index].b)),
				rgb[point->left_index].b);
	else if (point->pos == HW_POINT_POSITION_LEFT) {
		BREAK_TO_DEBUGGER();
		result = dc_fixpt_zero;
	} else {
		BREAK_TO_DEBUGGER();
		result = dc_fixpt_one;
	}

	return result;
}