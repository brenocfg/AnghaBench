#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct timing_generator {TYPE_5__* funcs; } ;
struct TYPE_13__ {struct timing_generator* tg; } ;
struct TYPE_9__ {TYPE_7__* hubp; } ;
struct pipe_ctx {TYPE_6__ stream_res; TYPE_2__ plane_res; struct dc_plane_state* plane_state; } ;
struct TYPE_10__ {scalar_t__ type; } ;
struct TYPE_11__ {int is_flip_pending; int is_right_eye; TYPE_3__ current_address; TYPE_3__ requested_address; } ;
struct dc_plane_state {TYPE_4__ status; } ;
struct TYPE_14__ {TYPE_1__* funcs; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* is_stereo_left_eye ) (struct timing_generator*) ;} ;
struct TYPE_8__ {int (* hubp_is_flip_pending ) (TYPE_7__*) ;} ;

/* Variables and functions */
 scalar_t__ PLN_ADDR_TYPE_GRPH_STEREO ; 
 int stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub2 (struct timing_generator*) ; 

__attribute__((used)) static void dcn10_update_pending_status(struct pipe_ctx *pipe_ctx)
{
	struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	struct timing_generator *tg = pipe_ctx->stream_res.tg;
	bool flip_pending;

	if (plane_state == NULL)
		return;

	flip_pending = pipe_ctx->plane_res.hubp->funcs->hubp_is_flip_pending(
					pipe_ctx->plane_res.hubp);

	plane_state->status.is_flip_pending = plane_state->status.is_flip_pending || flip_pending;

	if (!flip_pending)
		plane_state->status.current_address = plane_state->status.requested_address;

	if (plane_state->status.current_address.type == PLN_ADDR_TYPE_GRPH_STEREO &&
			tg->funcs->is_stereo_left_eye) {
		plane_state->status.is_right_eye =
				!tg->funcs->is_stereo_left_eye(pipe_ctx->stream_res.tg);
	}
}