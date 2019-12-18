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
struct tpg_draw_params {unsigned int img_width; int wss_width; int wss_random_offset; int twopixsize; unsigned int left_pillar_width; unsigned int right_pillar_start; int sav_eav_f; scalar_t__ is_60hz; } ;
struct TYPE_4__ {int left; int width; } ;
struct TYPE_3__ {unsigned int left; unsigned int width; } ;
struct tpg_data {int src_width; scalar_t__ field; TYPE_2__ crop; TYPE_1__ border; } ;

/* Variables and functions */
 scalar_t__ V4L2_FIELD_BOTTOM ; 
 scalar_t__ V4L2_FIELD_TOP ; 
 int prandom_u32_max (int) ; 
 void* tpg_hscale_div (struct tpg_data const*,unsigned int,unsigned int) ; 

__attribute__((used)) static void tpg_fill_params_extras(const struct tpg_data *tpg,
				   unsigned p,
				   struct tpg_draw_params *params)
{
	unsigned left_pillar_width = 0;
	unsigned right_pillar_start = params->img_width;

	params->wss_width = tpg->crop.left < tpg->src_width / 2 ?
		tpg->src_width / 2 - tpg->crop.left : 0;
	if (params->wss_width > tpg->crop.width)
		params->wss_width = tpg->crop.width;
	params->wss_width = tpg_hscale_div(tpg, p, params->wss_width);
	params->wss_random_offset =
		params->twopixsize * prandom_u32_max(tpg->src_width / 2);

	if (tpg->crop.left < tpg->border.left) {
		left_pillar_width = tpg->border.left - tpg->crop.left;
		if (left_pillar_width > tpg->crop.width)
			left_pillar_width = tpg->crop.width;
		left_pillar_width = tpg_hscale_div(tpg, p, left_pillar_width);
	}
	params->left_pillar_width = left_pillar_width;

	if (tpg->crop.left + tpg->crop.width >
	    tpg->border.left + tpg->border.width) {
		right_pillar_start =
			tpg->border.left + tpg->border.width - tpg->crop.left;
		right_pillar_start =
			tpg_hscale_div(tpg, p, right_pillar_start);
		if (right_pillar_start > params->img_width)
			right_pillar_start = params->img_width;
	}
	params->right_pillar_start = right_pillar_start;

	params->sav_eav_f = tpg->field ==
			(params->is_60hz ? V4L2_FIELD_TOP : V4L2_FIELD_BOTTOM);
}