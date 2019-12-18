#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct timing_generator {TYPE_1__* funcs; } ;
struct tg_color {int /*<<< orphan*/  member_0; } ;
struct output_pixel_processor {TYPE_4__* funcs; } ;
struct dc {TYPE_3__* res_pool; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_8__ {int /*<<< orphan*/  (* opp_set_disp_pattern_generator ) (struct output_pixel_processor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tg_color*,size_t,size_t) ;} ;
struct TYPE_7__ {struct output_pixel_processor** opps; TYPE_2__* res_cap; } ;
struct TYPE_6__ {size_t num_opp; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_optc_source ) (struct timing_generator*,size_t*,size_t*,size_t*) ;int /*<<< orphan*/  (* get_otg_active_size ) (struct timing_generator*,size_t*,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  COLOR_DEPTH_UNDEFINED ; 
 int COLOR_SPACE_SRGB ; 
 int /*<<< orphan*/  CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR ; 
 int /*<<< orphan*/  color_space_to_black_color (struct dc*,int,struct tg_color*) ; 
 int /*<<< orphan*/  dcn20_hwss_wait_for_blank_complete (struct output_pixel_processor*) ; 
 int /*<<< orphan*/  stub1 (struct timing_generator*,size_t*,size_t*) ; 
 int /*<<< orphan*/  stub2 (struct timing_generator*,size_t*,size_t*,size_t*) ; 
 int /*<<< orphan*/  stub3 (struct output_pixel_processor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tg_color*,size_t,size_t) ; 
 int /*<<< orphan*/  stub4 (struct output_pixel_processor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tg_color*,size_t,size_t) ; 

void dcn20_init_blank(
		struct dc *dc,
		struct timing_generator *tg)
{
	enum dc_color_space color_space;
	struct tg_color black_color = {0};
	struct output_pixel_processor *opp = NULL;
	struct output_pixel_processor *bottom_opp = NULL;
	uint32_t num_opps, opp_id_src0, opp_id_src1;
	uint32_t otg_active_width, otg_active_height;

	/* program opp dpg blank color */
	color_space = COLOR_SPACE_SRGB;
	color_space_to_black_color(dc, color_space, &black_color);

	/* get the OTG active size */
	tg->funcs->get_otg_active_size(tg,
			&otg_active_width,
			&otg_active_height);

	/* get the OPTC source */
	tg->funcs->get_optc_source(tg, &num_opps, &opp_id_src0, &opp_id_src1);
	ASSERT(opp_id_src0 < dc->res_pool->res_cap->num_opp);
	opp = dc->res_pool->opps[opp_id_src0];

	if (num_opps == 2) {
		otg_active_width = otg_active_width / 2;
		ASSERT(opp_id_src1 < dc->res_pool->res_cap->num_opp);
		bottom_opp = dc->res_pool->opps[opp_id_src1];
	}

	opp->funcs->opp_set_disp_pattern_generator(
			opp,
			CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR,
			COLOR_DEPTH_UNDEFINED,
			&black_color,
			otg_active_width,
			otg_active_height);

	if (num_opps == 2) {
		bottom_opp->funcs->opp_set_disp_pattern_generator(
				bottom_opp,
				CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR,
				COLOR_DEPTH_UNDEFINED,
				&black_color,
				otg_active_width,
				otg_active_height);
	}

	dcn20_hwss_wait_for_blank_complete(opp);
}