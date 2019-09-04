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
struct pwl_float_data_ex {int /*<<< orphan*/  r; int /*<<< orphan*/  b; int /*<<< orphan*/  g; } ;
struct hw_x_point {int /*<<< orphan*/  x; } ;
struct gamma_coefficients {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_coefficients (struct gamma_coefficients*,int) ; 
 struct hw_x_point* coordinates_x ; 
 int /*<<< orphan*/  translate_from_linear_space_ex (int /*<<< orphan*/ ,struct gamma_coefficients*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_degamma_for_user_regamma(struct pwl_float_data_ex *rgb_regamma,
		uint32_t hw_points_num)
{
	uint32_t i;

	struct gamma_coefficients coeff;
	struct pwl_float_data_ex *rgb = rgb_regamma;
	const struct hw_x_point *coord_x = coordinates_x;

	build_coefficients(&coeff, true);

	i = 0;
	while (i != hw_points_num + 1) {
		rgb->r = translate_from_linear_space_ex(
				coord_x->x, &coeff, 0);
		rgb->g = rgb->r;
		rgb->b = rgb->r;
		++coord_x;
		++rgb;
		++i;
	}
}