#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_5__* hubp; } ;
struct pipe_ctx {struct dc_plane_state* plane_state; TYPE_2__ plane_res; } ;
struct TYPE_10__ {int /*<<< orphan*/  left_addr; } ;
struct TYPE_12__ {TYPE_4__ grph_stereo; } ;
struct TYPE_9__ {TYPE_6__ current_address; TYPE_6__ requested_address; } ;
struct dc_plane_state {TYPE_6__ address; TYPE_3__ status; scalar_t__ flip_immediate; } ;
struct dc {int dummy; } ;
struct TYPE_11__ {TYPE_1__* funcs; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* hubp_program_surface_flip_and_addr ) (TYPE_5__*,TYPE_6__*,scalar_t__) ;} ;
typedef  int /*<<< orphan*/  PHYSICAL_ADDRESS_LOC ;

/* Variables and functions */
 int patch_address_for_sbs_tb_stereo (struct pipe_ctx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_6__*,scalar_t__) ; 

__attribute__((used)) static void dcn10_update_plane_addr(const struct dc *dc, struct pipe_ctx *pipe_ctx)
{
	bool addr_patched = false;
	PHYSICAL_ADDRESS_LOC addr;
	struct dc_plane_state *plane_state = pipe_ctx->plane_state;

	if (plane_state == NULL)
		return;

	addr_patched = patch_address_for_sbs_tb_stereo(pipe_ctx, &addr);

	pipe_ctx->plane_res.hubp->funcs->hubp_program_surface_flip_and_addr(
			pipe_ctx->plane_res.hubp,
			&plane_state->address,
			plane_state->flip_immediate);

	plane_state->status.requested_address = plane_state->address;

	if (plane_state->flip_immediate)
		plane_state->status.current_address = plane_state->address;

	if (addr_patched)
		pipe_ctx->plane_state->address.grph_stereo.left_addr = addr;
}