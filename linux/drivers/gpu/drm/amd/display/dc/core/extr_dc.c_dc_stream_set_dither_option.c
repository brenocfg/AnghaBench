#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {TYPE_10__* opp; } ;
struct TYPE_18__ {int /*<<< orphan*/  depth; } ;
struct TYPE_19__ {TYPE_5__ lb_params; } ;
struct TYPE_20__ {TYPE_6__ scl_data; TYPE_11__* xfm; } ;
struct pipe_ctx {TYPE_9__ stream_res; TYPE_7__ plane_res; struct dc_stream_state* stream; } ;
struct bit_depth_reduction_params {int dummy; } ;
struct dc_stream_state {int dither_option; struct bit_depth_reduction_params bit_depth_params; struct dc_link* link; } ;
struct dc_link {TYPE_3__* dc; } ;
typedef  int /*<<< orphan*/  params ;
typedef  enum dc_dither_option { ____Placeholder_dc_dither_option } dc_dither_option ;
struct TYPE_21__ {int /*<<< orphan*/  (* opp_program_bit_depth_reduction ) (TYPE_10__*,struct bit_depth_reduction_params*) ;} ;
struct TYPE_17__ {int /*<<< orphan*/  (* transform_set_pixel_storage_depth ) (TYPE_11__*,int /*<<< orphan*/ ,struct bit_depth_reduction_params*) ;} ;
struct TYPE_16__ {TYPE_2__* current_state; } ;
struct TYPE_14__ {struct pipe_ctx* pipe_ctx; } ;
struct TYPE_15__ {TYPE_1__ res_ctx; } ;
struct TYPE_13__ {TYPE_4__* funcs; } ;
struct TYPE_12__ {TYPE_8__* funcs; } ;

/* Variables and functions */
 int DITHER_OPTION_MAX ; 
 int MAX_PIPES ; 
 int /*<<< orphan*/  memset (struct bit_depth_reduction_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resource_build_bit_depth_reduction_params (struct dc_stream_state*,struct bit_depth_reduction_params*) ; 
 int /*<<< orphan*/  stub1 (TYPE_11__*,int /*<<< orphan*/ ,struct bit_depth_reduction_params*) ; 
 int /*<<< orphan*/  stub2 (TYPE_10__*,struct bit_depth_reduction_params*) ; 

void dc_stream_set_dither_option(struct dc_stream_state *stream,
		enum dc_dither_option option)
{
	struct bit_depth_reduction_params params;
	struct dc_link *link = stream->link;
	struct pipe_ctx *pipes = NULL;
	int i;

	for (i = 0; i < MAX_PIPES; i++) {
		if (link->dc->current_state->res_ctx.pipe_ctx[i].stream ==
				stream) {
			pipes = &link->dc->current_state->res_ctx.pipe_ctx[i];
			break;
		}
	}

	if (!pipes)
		return;
	if (option > DITHER_OPTION_MAX)
		return;

	stream->dither_option = option;

	memset(&params, 0, sizeof(params));
	resource_build_bit_depth_reduction_params(stream, &params);
	stream->bit_depth_params = params;

	if (pipes->plane_res.xfm &&
	    pipes->plane_res.xfm->funcs->transform_set_pixel_storage_depth) {
		pipes->plane_res.xfm->funcs->transform_set_pixel_storage_depth(
			pipes->plane_res.xfm,
			pipes->plane_res.scl_data.lb_params.depth,
			&stream->bit_depth_params);
	}

	pipes->stream_res.opp->funcs->
		opp_program_bit_depth_reduction(pipes->stream_res.opp, &params);
}