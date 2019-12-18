#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct pwl_float_data_ex {int /*<<< orphan*/  b; int /*<<< orphan*/  g; int /*<<< orphan*/  r; } ;
struct dc_transfer_func_distributed_points {int x_point_at_y1_red; int x_point_at_y1_green; int x_point_at_y1_blue; scalar_t__ end_exponent; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;
typedef  enum dc_transfer_func_predefined { ____Placeholder_dc_transfer_func_predefined } dc_transfer_func_predefined ;
struct TYPE_5__ {int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t MAX_HW_POINTS ; 
 int TRANSFER_FUNCTION_BT709 ; 
 int TRANSFER_FUNCTION_GAMMA22 ; 
 int TRANSFER_FUNCTION_GAMMA24 ; 
 int TRANSFER_FUNCTION_GAMMA26 ; 
 int TRANSFER_FUNCTION_HLG ; 
 int TRANSFER_FUNCTION_LINEAR ; 
 int TRANSFER_FUNCTION_PQ ; 
 int TRANSFER_FUNCTION_SRGB ; 
 int TRANSFER_FUNCTION_UNITY ; 
 scalar_t__ _EXTRA_POINTS ; 
 int /*<<< orphan*/  build_de_pq (struct pwl_float_data_ex*,size_t,TYPE_1__*) ; 
 int /*<<< orphan*/  build_degamma (struct pwl_float_data_ex*,size_t,TYPE_1__*,int) ; 
 int /*<<< orphan*/  build_hlg_degamma (struct pwl_float_data_ex*,size_t,TYPE_1__*,int,int) ; 
 TYPE_1__* coordinates_x ; 
 struct pwl_float_data_ex* kvcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct pwl_float_data_ex*) ; 

bool  mod_color_calculate_degamma_curve(enum dc_transfer_func_predefined trans,
				struct dc_transfer_func_distributed_points *points)
{
	uint32_t i;
	bool ret = false;
	struct pwl_float_data_ex *rgb_degamma = NULL;

	if (trans == TRANSFER_FUNCTION_UNITY ||
		trans == TRANSFER_FUNCTION_LINEAR) {

		for (i = 0; i <= MAX_HW_POINTS ; i++) {
			points->red[i]    = coordinates_x[i].x;
			points->green[i]  = coordinates_x[i].x;
			points->blue[i]   = coordinates_x[i].x;
		}
		ret = true;
	} else if (trans == TRANSFER_FUNCTION_PQ) {
		rgb_degamma = kvcalloc(MAX_HW_POINTS + _EXTRA_POINTS,
				       sizeof(*rgb_degamma),
				       GFP_KERNEL);
		if (!rgb_degamma)
			goto rgb_degamma_alloc_fail;


		build_de_pq(rgb_degamma,
				MAX_HW_POINTS,
				coordinates_x);
		for (i = 0; i <= MAX_HW_POINTS ; i++) {
			points->red[i]    = rgb_degamma[i].r;
			points->green[i]  = rgb_degamma[i].g;
			points->blue[i]   = rgb_degamma[i].b;
		}
		ret = true;

		kvfree(rgb_degamma);
	} else if (trans == TRANSFER_FUNCTION_SRGB ||
		trans == TRANSFER_FUNCTION_BT709 ||
		trans == TRANSFER_FUNCTION_GAMMA22 ||
		trans == TRANSFER_FUNCTION_GAMMA24 ||
		trans == TRANSFER_FUNCTION_GAMMA26) {
		rgb_degamma = kvcalloc(MAX_HW_POINTS + _EXTRA_POINTS,
				       sizeof(*rgb_degamma),
				       GFP_KERNEL);
		if (!rgb_degamma)
			goto rgb_degamma_alloc_fail;

		build_degamma(rgb_degamma,
				MAX_HW_POINTS,
				coordinates_x,
				trans);
		for (i = 0; i <= MAX_HW_POINTS ; i++) {
			points->red[i]    = rgb_degamma[i].r;
			points->green[i]  = rgb_degamma[i].g;
			points->blue[i]   = rgb_degamma[i].b;
		}
		ret = true;

		kvfree(rgb_degamma);
	} else if (trans == TRANSFER_FUNCTION_HLG) {
		rgb_degamma = kvcalloc(MAX_HW_POINTS + _EXTRA_POINTS,
				       sizeof(*rgb_degamma),
				       GFP_KERNEL);
		if (!rgb_degamma)
			goto rgb_degamma_alloc_fail;

		build_hlg_degamma(rgb_degamma,
				MAX_HW_POINTS,
				coordinates_x,
				80, 1000);
		for (i = 0; i <= MAX_HW_POINTS ; i++) {
			points->red[i]    = rgb_degamma[i].r;
			points->green[i]  = rgb_degamma[i].g;
			points->blue[i]   = rgb_degamma[i].b;
		}
		ret = true;
		kvfree(rgb_degamma);
	}
	points->end_exponent = 0;
	points->x_point_at_y1_red = 1;
	points->x_point_at_y1_green = 1;
	points->x_point_at_y1_blue = 1;

rgb_degamma_alloc_fail:
	return ret;
}