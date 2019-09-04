#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {TYPE_2__* dpp; } ;
struct pipe_ctx {TYPE_3__ plane_res; } ;
struct dc {int dummy; } ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_5__ {TYPE_1__* funcs; } ;
struct TYPE_4__ {int /*<<< orphan*/ * dpp_set_csc_adjustment; } ;

/* Variables and functions */
 int /*<<< orphan*/  program_csc_matrix (struct pipe_ctx*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dcn10_program_output_csc(struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		enum dc_color_space colorspace,
		uint16_t *matrix,
		int opp_id)
{
	if (pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjustment != NULL)
		program_csc_matrix(pipe_ctx,
				colorspace,
				matrix);
}