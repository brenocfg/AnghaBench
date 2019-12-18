#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct tg_color {int /*<<< orphan*/  member_0; } ;
struct stream_resource {TYPE_6__* abm; TYPE_4__* tg; TYPE_8__* opp; } ;
struct pipe_ctx {struct stream_resource stream_res; struct pipe_ctx* next_odm_pipe; struct dc_stream_state* stream; } ;
struct TYPE_13__ {int h_addressable; int h_border_left; int h_border_right; int v_addressable; int v_border_bottom; int v_border_top; int /*<<< orphan*/  display_color_depth; } ;
struct dc_stream_state {int output_color_space; int /*<<< orphan*/  abm_level; TYPE_3__ timing; } ;
struct TYPE_12__ {scalar_t__ visual_confirm; } ;
struct dc {TYPE_2__ debug; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
typedef  enum controller_dp_test_pattern { ____Placeholder_controller_dp_test_pattern } controller_dp_test_pattern ;
struct TYPE_17__ {TYPE_1__* funcs; } ;
struct TYPE_16__ {TYPE_5__* funcs; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* set_abm_level ) (TYPE_6__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_pipe ) (TYPE_6__*,scalar_t__) ;int /*<<< orphan*/  (* set_abm_immediate_disable ) (TYPE_6__*) ;} ;
struct TYPE_14__ {scalar_t__ inst; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* opp_set_disp_pattern_generator ) (TYPE_8__*,int,int /*<<< orphan*/ ,struct tg_color*,int,int) ;} ;

/* Variables and functions */
 int CONTROLLER_DP_TEST_PATTERN_COLORRAMP ; 
 int CONTROLLER_DP_TEST_PATTERN_COLORSQUARES ; 
 int CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR ; 
 int CONTROLLER_DP_TEST_PATTERN_VIDEOMODE ; 
 scalar_t__ VISUAL_CONFIRM_DISABLE ; 
 int /*<<< orphan*/  color_space_to_black_color (struct dc*,int,struct tg_color*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_8__*,int,int /*<<< orphan*/ ,struct tg_color*,int,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_8__*,int,int /*<<< orphan*/ ,struct tg_color*,int,int) ; 
 int /*<<< orphan*/  stub4 (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (TYPE_6__*,int /*<<< orphan*/ ) ; 

void dcn20_blank_pixel_data(
		struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		bool blank)
{
	struct tg_color black_color = {0};
	struct stream_resource *stream_res = &pipe_ctx->stream_res;
	struct dc_stream_state *stream = pipe_ctx->stream;
	enum dc_color_space color_space = stream->output_color_space;
	enum controller_dp_test_pattern test_pattern = CONTROLLER_DP_TEST_PATTERN_SOLID_COLOR;
	struct pipe_ctx *odm_pipe;
	int odm_cnt = 1;

	int width = stream->timing.h_addressable + stream->timing.h_border_left + stream->timing.h_border_right;
	int height = stream->timing.v_addressable + stream->timing.v_border_bottom + stream->timing.v_border_top;

	/* get opp dpg blank color */
	color_space_to_black_color(dc, color_space, &black_color);

	for (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe)
		odm_cnt++;

	width = width / odm_cnt;

	if (blank) {
		if (stream_res->abm)
			stream_res->abm->funcs->set_abm_immediate_disable(stream_res->abm);

		if (dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE)
			test_pattern = CONTROLLER_DP_TEST_PATTERN_COLORSQUARES;
	} else {
		test_pattern = CONTROLLER_DP_TEST_PATTERN_VIDEOMODE;
	}

	stream_res->opp->funcs->opp_set_disp_pattern_generator(
			stream_res->opp,
			test_pattern,
			stream->timing.display_color_depth,
			&black_color,
			width,
			height);

	for (odm_pipe = pipe_ctx->next_odm_pipe; odm_pipe; odm_pipe = odm_pipe->next_odm_pipe) {
		odm_pipe->stream_res.opp->funcs->opp_set_disp_pattern_generator(
				odm_pipe->stream_res.opp,
				dc->debug.visual_confirm != VISUAL_CONFIRM_DISABLE && blank ?
						CONTROLLER_DP_TEST_PATTERN_COLORRAMP : test_pattern,
				stream->timing.display_color_depth,
				&black_color,
				width,
				height);
	}

	if (!blank)
		if (stream_res->abm) {
			stream_res->abm->funcs->set_pipe(stream_res->abm, stream_res->tg->inst + 1);
			stream_res->abm->funcs->set_abm_level(stream_res->abm, stream->abm_level);
		}
}