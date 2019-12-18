#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_7__* tg; } ;
struct TYPE_11__ {TYPE_8__* mi; } ;
struct pipe_ctx {TYPE_6__ stream_res; TYPE_3__ plane_res; struct dc_plane_state* plane_state; } ;
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_12__ {int is_right_eye; TYPE_2__ current_address; scalar_t__ is_flip_pending; } ;
struct dc_plane_state {TYPE_4__ status; int /*<<< orphan*/  visible; } ;
struct TYPE_16__ {TYPE_2__ current_address; TYPE_2__ request_address; TYPE_1__* funcs; } ;
struct TYPE_15__ {TYPE_5__* funcs; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* is_stereo_left_eye ) (TYPE_7__*) ;} ;
struct TYPE_9__ {scalar_t__ (* mem_input_is_flip_pending ) (TYPE_8__*) ;} ;

/* Variables and functions */
 scalar_t__ PLN_ADDR_TYPE_GRPH_STEREO ; 
 scalar_t__ stub1 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_7__*) ; 

__attribute__((used)) static void dce110_update_pending_status(struct pipe_ctx *pipe_ctx)
{
	struct dc_plane_state *plane_state = pipe_ctx->plane_state;

	if (plane_state == NULL)
		return;

	plane_state->status.is_flip_pending =
			pipe_ctx->plane_res.mi->funcs->mem_input_is_flip_pending(
					pipe_ctx->plane_res.mi);

	if (plane_state->status.is_flip_pending && !plane_state->visible)
		pipe_ctx->plane_res.mi->current_address = pipe_ctx->plane_res.mi->request_address;

	plane_state->status.current_address = pipe_ctx->plane_res.mi->current_address;
	if (pipe_ctx->plane_res.mi->current_address.type == PLN_ADDR_TYPE_GRPH_STEREO &&
			pipe_ctx->stream_res.tg->funcs->is_stereo_left_eye) {
		plane_state->status.is_right_eye =\
				!pipe_ctx->stream_res.tg->funcs->is_stereo_left_eye(pipe_ctx->stream_res.tg);
	}
}