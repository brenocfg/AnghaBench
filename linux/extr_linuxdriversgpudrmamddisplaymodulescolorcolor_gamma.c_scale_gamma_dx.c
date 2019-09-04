#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct pwl_float_data {void* b; void* g; void* r; } ;
struct fixed31_32 {int dummy; } ;
struct dividers {int dummy; } ;
struct TYPE_2__ {struct fixed31_32* blue; struct fixed31_32* green; struct fixed31_32* red; } ;
struct dc_gamma {size_t num_entries; TYPE_1__ entries; } ;

/* Variables and functions */
 struct fixed31_32 dc_fixpt_add (struct fixed31_32,struct fixed31_32) ; 
 void* dc_fixpt_div (struct fixed31_32,struct fixed31_32) ; 
 scalar_t__ dc_fixpt_lt (struct fixed31_32,struct fixed31_32) ; 
 int /*<<< orphan*/  dc_fixpt_mul_int (void*,int) ; 
 struct fixed31_32 dc_fixpt_neg (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_one ; 
 void* dc_fixpt_sub (int /*<<< orphan*/ ,void*) ; 
 struct fixed31_32 dc_fixpt_zero ; 

__attribute__((used)) static void scale_gamma_dx(struct pwl_float_data *pwl_rgb,
		const struct dc_gamma *ramp,
		struct dividers dividers)
{
	uint32_t i;
	struct fixed31_32 min = dc_fixpt_zero;
	struct fixed31_32 max = dc_fixpt_one;

	struct fixed31_32 delta = dc_fixpt_zero;
	struct fixed31_32 offset = dc_fixpt_zero;

	for (i = 0 ; i < ramp->num_entries; i++) {
		if (dc_fixpt_lt(ramp->entries.red[i], min))
			min = ramp->entries.red[i];

		if (dc_fixpt_lt(ramp->entries.green[i], min))
			min = ramp->entries.green[i];

		if (dc_fixpt_lt(ramp->entries.blue[i], min))
			min = ramp->entries.blue[i];

		if (dc_fixpt_lt(max, ramp->entries.red[i]))
			max = ramp->entries.red[i];

		if (dc_fixpt_lt(max, ramp->entries.green[i]))
			max = ramp->entries.green[i];

		if (dc_fixpt_lt(max, ramp->entries.blue[i]))
			max = ramp->entries.blue[i];
	}

	if (dc_fixpt_lt(min, dc_fixpt_zero))
		delta = dc_fixpt_neg(min);

	offset = dc_fixpt_add(min, max);

	for (i = 0 ; i < ramp->num_entries; i++) {
		pwl_rgb[i].r = dc_fixpt_div(
			dc_fixpt_add(
				ramp->entries.red[i], delta), offset);
		pwl_rgb[i].g = dc_fixpt_div(
			dc_fixpt_add(
				ramp->entries.green[i], delta), offset);
		pwl_rgb[i].b = dc_fixpt_div(
			dc_fixpt_add(
				ramp->entries.blue[i], delta), offset);

	}

	pwl_rgb[i].r =  dc_fixpt_sub(dc_fixpt_mul_int(
				pwl_rgb[i-1].r, 2), pwl_rgb[i-2].r);
	pwl_rgb[i].g =  dc_fixpt_sub(dc_fixpt_mul_int(
				pwl_rgb[i-1].g, 2), pwl_rgb[i-2].g);
	pwl_rgb[i].b =  dc_fixpt_sub(dc_fixpt_mul_int(
				pwl_rgb[i-1].b, 2), pwl_rgb[i-2].b);
	++i;
	pwl_rgb[i].r =  dc_fixpt_sub(dc_fixpt_mul_int(
				pwl_rgb[i-1].r, 2), pwl_rgb[i-2].r);
	pwl_rgb[i].g =  dc_fixpt_sub(dc_fixpt_mul_int(
				pwl_rgb[i-1].g, 2), pwl_rgb[i-2].g);
	pwl_rgb[i].b =  dc_fixpt_sub(dc_fixpt_mul_int(
				pwl_rgb[i-1].b, 2), pwl_rgb[i-2].b);
}