#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_6__* tg; } ;
struct pipe_ctx {TYPE_5__ stream_res; TYPE_4__* stream; } ;
struct dc_context {int dummy; } ;
struct dc {struct dc_context* ctx; } ;
struct TYPE_15__ {TYPE_3__* event_source; } ;
struct TYPE_14__ {TYPE_1__* funcs; } ;
struct TYPE_12__ {TYPE_8__ triggered_crtc_reset; } ;
struct TYPE_10__ {int /*<<< orphan*/  primary_otg_inst; } ;
struct TYPE_11__ {TYPE_2__ status; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* enable_crtc_reset ) (TYPE_6__*,int /*<<< orphan*/ ,TYPE_8__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_SYNC_INFO (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  wait_for_reset_trigger_to_occur (struct dc_context*,TYPE_6__*) ; 

__attribute__((used)) static void dcn10_enable_per_frame_crtc_position_reset(
	struct dc *dc,
	int group_size,
	struct pipe_ctx *grouped_pipes[])
{
	struct dc_context *dc_ctx = dc->ctx;
	int i;

	DC_SYNC_INFO("Setting up\n");
	for (i = 0; i < group_size; i++)
		if (grouped_pipes[i]->stream_res.tg->funcs->enable_crtc_reset)
			grouped_pipes[i]->stream_res.tg->funcs->enable_crtc_reset(
					grouped_pipes[i]->stream_res.tg,
					grouped_pipes[i]->stream->triggered_crtc_reset.event_source->status.primary_otg_inst,
					&grouped_pipes[i]->stream->triggered_crtc_reset);

	DC_SYNC_INFO("Waiting for trigger\n");

	for (i = 0; i < group_size; i++)
		wait_for_reset_trigger_to_occur(dc_ctx, grouped_pipes[i]->stream_res.tg);

	DC_SYNC_INFO("Multi-display sync is complete\n");
}