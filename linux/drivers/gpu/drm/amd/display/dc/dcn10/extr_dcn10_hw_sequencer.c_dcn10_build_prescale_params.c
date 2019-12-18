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
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {scalar_t__ enable_adjustment; } ;
struct dc_plane_state {scalar_t__ format; TYPE_2__ coeff_reduction_factor; TYPE_1__ input_csc_color_matrix; } ;
struct dc_bias_and_scale {int scale_blue; int scale_red; int scale_green; } ;

/* Variables and functions */
 scalar_t__ SURFACE_PIXEL_FORMAT_INVALID ; 
 scalar_t__ SURFACE_PIXEL_FORMAT_VIDEO_BEGIN ; 
 int /*<<< orphan*/  dc_fixpt_from_fraction (int,int) ; 
 int /*<<< orphan*/  dc_fixpt_mul (TYPE_2__,int /*<<< orphan*/ ) ; 
 int fixed_point_to_int_frac (int /*<<< orphan*/ ,int,int) ; 

void dcn10_build_prescale_params(struct  dc_bias_and_scale *bias_and_scale,
		const struct dc_plane_state *plane_state)
{
	if (plane_state->format >= SURFACE_PIXEL_FORMAT_VIDEO_BEGIN
			&& plane_state->format != SURFACE_PIXEL_FORMAT_INVALID
			&& plane_state->input_csc_color_matrix.enable_adjustment
			&& plane_state->coeff_reduction_factor.value != 0) {
		bias_and_scale->scale_blue = fixed_point_to_int_frac(
			dc_fixpt_mul(plane_state->coeff_reduction_factor,
					dc_fixpt_from_fraction(256, 255)),
				2,
				13);
		bias_and_scale->scale_red = bias_and_scale->scale_blue;
		bias_and_scale->scale_green = bias_and_scale->scale_blue;
	} else {
		bias_and_scale->scale_blue = 0x2000;
		bias_and_scale->scale_red = 0x2000;
		bias_and_scale->scale_green = 0x2000;
	}
}