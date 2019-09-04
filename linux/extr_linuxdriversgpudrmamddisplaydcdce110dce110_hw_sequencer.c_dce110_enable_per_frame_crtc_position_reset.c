#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_6__* tg; } ;
struct pipe_ctx {TYPE_5__ stream_res; TYPE_3__* stream; } ;
struct dcp_gsl_params {int /*<<< orphan*/  gsl_master; scalar_t__ gsl_group; int /*<<< orphan*/  member_0; } ;
struct dc_context {int dummy; } ;
struct dc {struct dc_context* ctx; } ;
struct TYPE_17__ {TYPE_2__* event_source; } ;
struct TYPE_16__ {TYPE_4__* funcs; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* tear_down_global_swap_lock ) (TYPE_6__*) ;int /*<<< orphan*/  (* enable_crtc_reset ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_9__*) ;int /*<<< orphan*/  (* setup_global_swap_lock ) (TYPE_6__*,struct dcp_gsl_params*) ;} ;
struct TYPE_13__ {TYPE_9__ triggered_crtc_reset; } ;
struct TYPE_11__ {int /*<<< orphan*/  primary_otg_inst; } ;
struct TYPE_12__ {TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_SYNC_INFO (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,struct dcp_gsl_params*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_9__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_6__*) ; 
 int /*<<< orphan*/  wait_for_reset_trigger_to_occur (struct dc_context*,TYPE_6__*) ; 

__attribute__((used)) static void dce110_enable_per_frame_crtc_position_reset(
		struct dc *dc,
		int group_size,
		struct pipe_ctx *grouped_pipes[])
{
	struct dc_context *dc_ctx = dc->ctx;
	struct dcp_gsl_params gsl_params = { 0 };
	int i;

	gsl_params.gsl_group = 0;
	gsl_params.gsl_master = grouped_pipes[0]->stream->triggered_crtc_reset.event_source->status.primary_otg_inst;

	for (i = 0; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->setup_global_swap_lock(
					grouped_pipes[i]->stream_res.tg, &gsl_params);

	DC_SYNC_INFO("GSL: enabling trigger-reset\n");

	for (i = 1; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->enable_crtc_reset(
				grouped_pipes[i]->stream_res.tg,
				gsl_params.gsl_master,
				&grouped_pipes[i]->stream->triggered_crtc_reset);

	DC_SYNC_INFO("GSL: waiting for reset to occur.\n");
	for (i = 1; i < group_size; i++)
		wait_for_reset_trigger_to_occur(dc_ctx, grouped_pipes[i]->stream_res.tg);

	for (i = 0; i < group_size; i++)
		grouped_pipes[i]->stream_res.tg->funcs->tear_down_global_swap_lock(grouped_pipes[i]->stream_res.tg);

}