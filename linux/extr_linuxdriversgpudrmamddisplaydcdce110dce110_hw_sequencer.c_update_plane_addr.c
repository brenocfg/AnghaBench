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
struct TYPE_6__ {TYPE_4__* mi; } ;
struct pipe_ctx {TYPE_2__ plane_res; struct dc_plane_state* plane_state; } ;
struct TYPE_7__ {int /*<<< orphan*/  requested_address; } ;
struct dc_plane_state {int /*<<< orphan*/  address; TYPE_3__ status; int /*<<< orphan*/  flip_immediate; } ;
struct dc {int dummy; } ;
struct TYPE_8__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* mem_input_program_surface_flip_and_addr ) (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void update_plane_addr(const struct dc *dc,
		struct pipe_ctx *pipe_ctx)
{
	struct dc_plane_state *plane_state = pipe_ctx->plane_state;

	if (plane_state == NULL)
		return;

	pipe_ctx->plane_res.mi->funcs->mem_input_program_surface_flip_and_addr(
			pipe_ctx->plane_res.mi,
			&plane_state->address,
			plane_state->flip_immediate);

	plane_state->status.requested_address = plane_state->address;
}