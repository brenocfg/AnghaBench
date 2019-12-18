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
typedef  scalar_t__ uint16_t ;
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIVIDER ; 
 int /*<<< orphan*/  S2D13_MAX ; 
 int /*<<< orphan*/  S2D13_MIN ; 
 int /*<<< orphan*/  dc_fixpt_clamp (struct fixed31_32,struct fixed31_32 const,struct fixed31_32 const) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t fixed_point_to_int_frac (int /*<<< orphan*/ ,int,int) ; 

void convert_float_matrix(
	uint16_t *matrix,
	struct fixed31_32 *flt,
	uint32_t buffer_size)
{
	const struct fixed31_32 min_2_13 =
		dc_fixpt_from_fraction(S2D13_MIN, DIVIDER);
	const struct fixed31_32 max_2_13 =
		dc_fixpt_from_fraction(S2D13_MAX, DIVIDER);
	uint32_t i;

	for (i = 0; i < buffer_size; ++i) {
		uint32_t reg_value =
				fixed_point_to_int_frac(
					dc_fixpt_clamp(
						flt[i],
						min_2_13,
						max_2_13),
						2,
						13);

		matrix[i] = (uint16_t)reg_value;
	}
}