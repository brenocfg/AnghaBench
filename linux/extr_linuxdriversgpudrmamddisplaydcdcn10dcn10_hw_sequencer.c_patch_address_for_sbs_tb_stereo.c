#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pipe_ctx {TYPE_3__* stream; struct dc_plane_state* plane_state; TYPE_1__* top_pipe; } ;
struct TYPE_9__ {int /*<<< orphan*/  left_addr; int /*<<< orphan*/  right_addr; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_4__ grph_stereo; } ;
struct dc_plane_state {TYPE_5__ address; } ;
struct TYPE_7__ {scalar_t__ timing_3d_format; } ;
struct TYPE_8__ {scalar_t__ view_format; TYPE_2__ timing; } ;
struct TYPE_6__ {struct dc_plane_state* plane_state; } ;
typedef  int /*<<< orphan*/  PHYSICAL_ADDRESS_LOC ;

/* Variables and functions */
 scalar_t__ PLN_ADDR_TYPE_GRPH_STEREO ; 
 scalar_t__ TIMING_3D_FORMAT_SIDE_BY_SIDE ; 
 scalar_t__ TIMING_3D_FORMAT_TOP_AND_BOTTOM ; 
 scalar_t__ VIEW_3D_FORMAT_NONE ; 

__attribute__((used)) static bool patch_address_for_sbs_tb_stereo(
		struct pipe_ctx *pipe_ctx, PHYSICAL_ADDRESS_LOC *addr)
{
	struct dc_plane_state *plane_state = pipe_ctx->plane_state;
	bool sec_split = pipe_ctx->top_pipe &&
			pipe_ctx->top_pipe->plane_state == pipe_ctx->plane_state;
	if (sec_split && plane_state->address.type == PLN_ADDR_TYPE_GRPH_STEREO &&
		(pipe_ctx->stream->timing.timing_3d_format ==
		 TIMING_3D_FORMAT_SIDE_BY_SIDE ||
		 pipe_ctx->stream->timing.timing_3d_format ==
		 TIMING_3D_FORMAT_TOP_AND_BOTTOM)) {
		*addr = plane_state->address.grph_stereo.left_addr;
		plane_state->address.grph_stereo.left_addr =
		plane_state->address.grph_stereo.right_addr;
		return true;
	} else {
		if (pipe_ctx->stream->view_format != VIEW_3D_FORMAT_NONE &&
			plane_state->address.type != PLN_ADDR_TYPE_GRPH_STEREO) {
			plane_state->address.type = PLN_ADDR_TYPE_GRPH_STEREO;
			plane_state->address.grph_stereo.right_addr =
			plane_state->address.grph_stereo.left_addr;
		}
	}
	return false;
}