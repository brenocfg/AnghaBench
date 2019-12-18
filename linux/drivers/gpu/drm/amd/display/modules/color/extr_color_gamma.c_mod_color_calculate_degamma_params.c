#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct pwl_float_data_ex {int /*<<< orphan*/  r; int /*<<< orphan*/  b; int /*<<< orphan*/  g; } ;
struct pwl_float_data {int /*<<< orphan*/  r; int /*<<< orphan*/  b; int /*<<< orphan*/  g; } ;
struct pixel_gamma_point {int /*<<< orphan*/  r; int /*<<< orphan*/  b; int /*<<< orphan*/  g; } ;
struct gamma_pixel {int /*<<< orphan*/  r; int /*<<< orphan*/  b; int /*<<< orphan*/  g; } ;
struct dividers {void* divider3; int /*<<< orphan*/  divider2; void* divider1; } ;
struct dc_transfer_func_distributed_points {int x_point_at_y1_red; int x_point_at_y1_green; int x_point_at_y1_blue; scalar_t__ end_exponent; } ;
struct dc_transfer_func {scalar_t__ type; scalar_t__ tf; struct dc_transfer_func_distributed_points tf_pts; } ;
struct dc_gamma {scalar_t__ type; size_t num_entries; } ;
typedef  enum dc_transfer_func_predefined { ____Placeholder_dc_transfer_func_predefined } dc_transfer_func_predefined ;
struct TYPE_6__ {int /*<<< orphan*/  x; } ;

/* Variables and functions */
 scalar_t__ GAMMA_CUSTOM ; 
 scalar_t__ GAMMA_RGB_256 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_HW_POINTS ; 
 scalar_t__ TF_TYPE_BYPASS ; 
 scalar_t__ TF_TYPE_DISTRIBUTED_POINTS ; 
 scalar_t__ TF_TYPE_PREDEFINED ; 
 int TRANSFER_FUNCTION_BT709 ; 
 int TRANSFER_FUNCTION_GAMMA22 ; 
 int TRANSFER_FUNCTION_GAMMA24 ; 
 int TRANSFER_FUNCTION_GAMMA26 ; 
 int TRANSFER_FUNCTION_HLG ; 
 scalar_t__ TRANSFER_FUNCTION_LINEAR ; 
 int TRANSFER_FUNCTION_PQ ; 
 scalar_t__ TRANSFER_FUNCTION_SRGB ; 
 size_t _EXTRA_POINTS ; 
 int /*<<< orphan*/  apply_lut_1d (struct dc_gamma const*,size_t,struct dc_transfer_func_distributed_points*) ; 
 int /*<<< orphan*/  build_de_pq (struct pwl_float_data_ex*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  build_degamma (struct pwl_float_data_ex*,size_t,TYPE_1__*,int) ; 
 int /*<<< orphan*/  build_evenly_distributed_points (struct pwl_float_data_ex*,size_t,struct dividers) ; 
 int /*<<< orphan*/  build_hlg_degamma (struct pwl_float_data_ex*,size_t,TYPE_1__*,int,int) ; 
 TYPE_1__* coordinates_x ; 
 void* dc_fixpt_from_fraction (int,int) ; 
 int /*<<< orphan*/  dc_fixpt_from_int (int) ; 
 struct pwl_float_data_ex* kvcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct pwl_float_data_ex*) ; 
 int /*<<< orphan*/  map_regamma_hw_to_x_user (struct dc_gamma const*,struct pwl_float_data_ex*,struct pwl_float_data_ex*,TYPE_1__*,struct pwl_float_data_ex*,struct pwl_float_data_ex*,size_t,struct dc_transfer_func_distributed_points*,int) ; 
 int /*<<< orphan*/  scale_gamma (struct pwl_float_data_ex*,struct dc_gamma const*,struct dividers) ; 

bool mod_color_calculate_degamma_params(struct dc_transfer_func *input_tf,
		const struct dc_gamma *ramp, bool mapUserRamp)
{
	struct dc_transfer_func_distributed_points *tf_pts = &input_tf->tf_pts;
	struct dividers dividers;
	struct pwl_float_data *rgb_user = NULL;
	struct pwl_float_data_ex *curve = NULL;
	struct gamma_pixel *axis_x = NULL;
	struct pixel_gamma_point *coeff = NULL;
	enum dc_transfer_func_predefined tf = TRANSFER_FUNCTION_SRGB;
	uint32_t i;
	bool ret = false;

	if (input_tf->type == TF_TYPE_BYPASS)
		return false;

	/* we can use hardcoded curve for plain SRGB TF
	 * If linear, it's bypass if on user ramp
	 */
	if (input_tf->type == TF_TYPE_PREDEFINED &&
			(input_tf->tf == TRANSFER_FUNCTION_SRGB ||
					input_tf->tf == TRANSFER_FUNCTION_LINEAR) &&
					!mapUserRamp)
		return true;

	input_tf->type = TF_TYPE_DISTRIBUTED_POINTS;

	if (mapUserRamp && ramp && ramp->type == GAMMA_RGB_256) {
		rgb_user = kvcalloc(ramp->num_entries + _EXTRA_POINTS,
				sizeof(*rgb_user),
				GFP_KERNEL);
		if (!rgb_user)
			goto rgb_user_alloc_fail;

		axis_x = kvcalloc(ramp->num_entries + _EXTRA_POINTS, sizeof(*axis_x),
				GFP_KERNEL);
		if (!axis_x)
			goto axis_x_alloc_fail;

		dividers.divider1 = dc_fixpt_from_fraction(3, 2);
		dividers.divider2 = dc_fixpt_from_int(2);
		dividers.divider3 = dc_fixpt_from_fraction(5, 2);

		build_evenly_distributed_points(
				axis_x,
				ramp->num_entries,
				dividers);

		scale_gamma(rgb_user, ramp, dividers);
	}

	curve = kvcalloc(MAX_HW_POINTS + _EXTRA_POINTS, sizeof(*curve),
			GFP_KERNEL);
	if (!curve)
		goto curve_alloc_fail;

	coeff = kvcalloc(MAX_HW_POINTS + _EXTRA_POINTS, sizeof(*coeff),
			GFP_KERNEL);
	if (!coeff)
		goto coeff_alloc_fail;

	tf = input_tf->tf;

	if (tf == TRANSFER_FUNCTION_PQ)
		build_de_pq(curve,
				MAX_HW_POINTS,
				coordinates_x);
	else if (tf == TRANSFER_FUNCTION_SRGB ||
		tf == TRANSFER_FUNCTION_BT709 ||
		tf == TRANSFER_FUNCTION_GAMMA22 ||
		tf == TRANSFER_FUNCTION_GAMMA24 ||
		tf == TRANSFER_FUNCTION_GAMMA26)
		build_degamma(curve,
				MAX_HW_POINTS,
				coordinates_x,
				tf);
	else if (tf == TRANSFER_FUNCTION_HLG)
		build_hlg_degamma(curve,
				MAX_HW_POINTS,
				coordinates_x,
				80, 1000);
	else if (tf == TRANSFER_FUNCTION_LINEAR) {
		// just copy coordinates_x into curve
		i = 0;
		while (i != MAX_HW_POINTS + 1) {
			curve[i].r = coordinates_x[i].x;
			curve[i].g = curve[i].r;
			curve[i].b = curve[i].r;
			i++;
		}
	} else
		goto invalid_tf_fail;

	tf_pts->end_exponent = 0;
	tf_pts->x_point_at_y1_red = 1;
	tf_pts->x_point_at_y1_green = 1;
	tf_pts->x_point_at_y1_blue = 1;

	map_regamma_hw_to_x_user(ramp, coeff, rgb_user,
			coordinates_x, axis_x, curve,
			MAX_HW_POINTS, tf_pts,
			mapUserRamp && ramp && ramp->type == GAMMA_RGB_256);
	if (ramp->type == GAMMA_CUSTOM)
		apply_lut_1d(ramp, MAX_HW_POINTS, tf_pts);

	ret = true;

invalid_tf_fail:
	kvfree(coeff);
coeff_alloc_fail:
	kvfree(curve);
curve_alloc_fail:
	kvfree(axis_x);
axis_x_alloc_fail:
	kvfree(rgb_user);
rgb_user_alloc_fail:

	return ret;
}