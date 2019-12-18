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
struct pwl_float_data_ex {void* b; void* g; void* r; } ;
struct hw_x_point {int /*<<< orphan*/  x; } ;
struct gamma_coefficients {int dummy; } ;
typedef  enum dc_transfer_func_predefined { ____Placeholder_dc_transfer_func_predefined } dc_transfer_func_predefined ;

/* Variables and functions */
 int NUM_PTS_IN_REGION ; 
 int /*<<< orphan*/  build_coefficients (struct gamma_coefficients*,int) ; 
 void* dc_fixpt_one ; 
 void* dc_fixpt_zero ; 
 void* translate_to_linear_space_ex (int /*<<< orphan*/ ,struct gamma_coefficients*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool build_degamma(struct pwl_float_data_ex *curve,
		uint32_t hw_points_num,
		const struct hw_x_point *coordinate_x, enum dc_transfer_func_predefined type)
{
	uint32_t i;
	struct gamma_coefficients coeff;
	uint32_t begin_index, end_index;
	bool ret = false;

	if (!build_coefficients(&coeff, type))
		goto release;

	i = 0;

	/* X points is 2^-25 to 2^7
	 * De-gamma X is 2^-12 to 2^0 – we are skipping first -12-(-25) = 13 regions
	 */
	begin_index = 13 * NUM_PTS_IN_REGION;
	end_index = begin_index + 12 * NUM_PTS_IN_REGION;

	while (i != begin_index) {
		curve[i].r = dc_fixpt_zero;
		curve[i].g = dc_fixpt_zero;
		curve[i].b = dc_fixpt_zero;
		i++;
	}

	while (i != end_index) {
		curve[i].r = translate_to_linear_space_ex(
				coordinate_x[i].x, &coeff, 0);
		curve[i].g = curve[i].r;
		curve[i].b = curve[i].r;
		i++;
	}
	while (i != hw_points_num + 1) {
		curve[i].r = dc_fixpt_one;
		curve[i].g = dc_fixpt_one;
		curve[i].b = dc_fixpt_one;
		i++;
	}
	ret = true;
release:
	return ret;
}