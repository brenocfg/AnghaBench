#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {TYPE_5__* dpp; } ;
struct pipe_ctx {TYPE_1__ plane_res; TYPE_3__* stream; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_11__ {TYPE_4__* funcs; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* dpp_set_csc_default ) (TYPE_5__*,int) ;int /*<<< orphan*/  (* dpp_set_csc_adjustment ) (TYPE_5__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {int enable_adjustment; } ;
struct TYPE_9__ {TYPE_2__ csc_color_matrix; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int) ; 

__attribute__((used)) static void program_csc_matrix(struct pipe_ctx *pipe_ctx,
		enum dc_color_space colorspace,
		uint16_t *matrix)
{
	if (pipe_ctx->stream->csc_color_matrix.enable_adjustment == true) {
			if (pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjustment != NULL)
				pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjustment(pipe_ctx->plane_res.dpp, matrix);
	} else {
		if (pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_default != NULL)
			pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_default(pipe_ctx->plane_res.dpp, colorspace);
	}
}