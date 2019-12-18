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
struct pwl_float_data {int dummy; } ;
struct pixel_gamma_point {int dummy; } ;
struct hw_x_point {int dummy; } ;
struct gamma_pixel {int dummy; } ;
struct dc_transfer_func_distributed_points {void** blue; void** green; void** red; } ;
struct dc_gamma {scalar_t__ num_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_NAME_BLUE ; 
 int /*<<< orphan*/  CHANNEL_NAME_GREEN ; 
 int /*<<< orphan*/  CHANNEL_NAME_RED ; 
 int /*<<< orphan*/  build_custom_gamma_mapping_coefficients_worker (struct dc_gamma const*,struct pixel_gamma_point*,struct hw_x_point const*,struct gamma_pixel const*,int,int) ; 
 void* calculate_mapped_value (struct pwl_float_data*,struct pixel_gamma_point const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool calculate_interpolated_hardware_curve(
	const struct dc_gamma *ramp,
	struct pixel_gamma_point *coeff128,
	struct pwl_float_data *rgb_user,
	const struct hw_x_point *coordinates_x,
	const struct gamma_pixel *axis_x,
	uint32_t number_of_points,
	struct dc_transfer_func_distributed_points *tf_pts)
{

	const struct pixel_gamma_point *coeff = coeff128;
	uint32_t max_entries = 3 - 1;

	uint32_t i = 0;

	for (i = 0; i < 3; i++) {
		if (!build_custom_gamma_mapping_coefficients_worker(
				ramp, coeff128, coordinates_x, axis_x, i,
				number_of_points))
			return false;
	}

	i = 0;
	max_entries += ramp->num_entries;

	/* TODO: float point case */

	while (i <= number_of_points) {
		tf_pts->red[i] = calculate_mapped_value(
			rgb_user, coeff, CHANNEL_NAME_RED, max_entries);
		tf_pts->green[i] = calculate_mapped_value(
			rgb_user, coeff, CHANNEL_NAME_GREEN, max_entries);
		tf_pts->blue[i] = calculate_mapped_value(
			rgb_user, coeff, CHANNEL_NAME_BLUE, max_entries);

		++coeff;
		++i;
	}

	return true;
}