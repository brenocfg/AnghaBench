#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* tg; } ;
struct pipe_ctx {TYPE_3__ stream_res; TYPE_2__* stream; } ;
struct dc_context {int dummy; } ;
struct dc {struct dc_context* ctx; } ;
struct TYPE_9__ {TYPE_1__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  triggered_crtc_reset; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* enable_crtc_reset ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DC_SYNC_INFO (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_reset_trigger_to_occur (struct dc_context*,TYPE_4__*) ; 

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
					0,
					&grouped_pipes[i]->stream->triggered_crtc_reset);

	DC_SYNC_INFO("Waiting for trigger\n");

	for (i = 0; i < group_size; i++)
		wait_for_reset_trigger_to_occur(dc_ctx, grouped_pipes[i]->stream_res.tg);

	DC_SYNC_INFO("Multi-display sync is complete\n");
}