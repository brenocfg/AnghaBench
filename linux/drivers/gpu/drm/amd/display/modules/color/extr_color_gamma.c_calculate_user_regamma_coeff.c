#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * gamma; int /*<<< orphan*/ * A3; int /*<<< orphan*/ * A2; int /*<<< orphan*/ * A1; int /*<<< orphan*/ * A0; } ;
struct regamma_lut {TYPE_1__ coeff; } ;
struct hw_x_point {int /*<<< orphan*/  x; } ;
struct gamma_coefficients {void** user_gamma; void** a3; void** a2; void** a1; void** a0; } ;
struct TYPE_4__ {void** blue; void** green; void** red; } ;
struct dc_transfer_func {int /*<<< orphan*/  type; TYPE_2__ tf_pts; } ;

/* Variables and functions */
 int MAX_HW_POINTS ; 
 int /*<<< orphan*/  TF_TYPE_DISTRIBUTED_POINTS ; 
 int /*<<< orphan*/  build_new_custom_resulted_curve (int,TYPE_2__*) ; 
 struct hw_x_point* coordinates_x ; 
 void* dc_fixpt_from_fraction (int /*<<< orphan*/ ,int) ; 
 void* dc_fixpt_zero ; 
 void* translate_from_linear_space_ex (int /*<<< orphan*/ ,struct gamma_coefficients*,int) ; 

bool calculate_user_regamma_coeff(struct dc_transfer_func *output_tf,
		const struct regamma_lut *regamma)
{
	struct gamma_coefficients coeff;
	const struct hw_x_point *coord_x = coordinates_x;
	uint32_t i = 0;

	do {
		coeff.a0[i] = dc_fixpt_from_fraction(
				regamma->coeff.A0[i], 10000000);
		coeff.a1[i] = dc_fixpt_from_fraction(
				regamma->coeff.A1[i], 1000);
		coeff.a2[i] = dc_fixpt_from_fraction(
				regamma->coeff.A2[i], 1000);
		coeff.a3[i] = dc_fixpt_from_fraction(
				regamma->coeff.A3[i], 1000);
		coeff.user_gamma[i] = dc_fixpt_from_fraction(
				regamma->coeff.gamma[i], 1000);

		++i;
	} while (i != 3);

	i = 0;
	/* fixed_pt library has problems handling too small values */
	while (i != 32) {
		output_tf->tf_pts.red[i] = dc_fixpt_zero;
		output_tf->tf_pts.green[i] = dc_fixpt_zero;
		output_tf->tf_pts.blue[i] = dc_fixpt_zero;
		++coord_x;
		++i;
	}
	while (i != MAX_HW_POINTS + 1) {
		output_tf->tf_pts.red[i] = translate_from_linear_space_ex(
				coord_x->x, &coeff, 0);
		output_tf->tf_pts.green[i] = translate_from_linear_space_ex(
				coord_x->x, &coeff, 1);
		output_tf->tf_pts.blue[i] = translate_from_linear_space_ex(
				coord_x->x, &coeff, 2);
		++coord_x;
		++i;
	}

	// this function just clamps output to 0-1
	build_new_custom_resulted_curve(MAX_HW_POINTS, &output_tf->tf_pts);
	output_tf->type = TF_TYPE_DISTRIBUTED_POINTS;

	return true;
}