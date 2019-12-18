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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {TYPE_5__* xfm; } ;
struct pipe_ctx {TYPE_2__ plane_res; TYPE_3__* stream; } ;
struct out_csc_color_matrix {int color_space; int /*<<< orphan*/ * regval; } ;
struct dc {int dummy; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_10__ {TYPE_1__* funcs; } ;
struct TYPE_9__ {int enable_adjustment; int /*<<< orphan*/ * matrix; } ;
struct TYPE_8__ {int output_color_space; TYPE_4__ csc_color_matrix; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* opp_set_csc_adjustment ) (TYPE_5__*,struct out_csc_color_matrix*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_5__*,struct out_csc_color_matrix*) ; 

__attribute__((used)) static void program_output_csc(struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		enum dc_color_space colorspace,
		uint16_t *matrix,
		int opp_id)
{
	int i;
	struct out_csc_color_matrix tbl_entry;

	if (pipe_ctx->stream->csc_color_matrix.enable_adjustment == true) {
		enum dc_color_space color_space = pipe_ctx->stream->output_color_space;

		for (i = 0; i < 12; i++)
			tbl_entry.regval[i] = pipe_ctx->stream->csc_color_matrix.matrix[i];

		tbl_entry.color_space = color_space;

		pipe_ctx->plane_res.xfm->funcs->opp_set_csc_adjustment(
				pipe_ctx->plane_res.xfm, &tbl_entry);
	}
}