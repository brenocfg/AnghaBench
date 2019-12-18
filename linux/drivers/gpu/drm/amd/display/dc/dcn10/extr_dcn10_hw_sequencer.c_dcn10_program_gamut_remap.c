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
struct TYPE_9__ {TYPE_5__* dpp; } ;
struct pipe_ctx {TYPE_4__ plane_res; TYPE_2__* stream; } ;
struct dpp_grph_csc_adjustment {int /*<<< orphan*/ * temperature_matrix; int /*<<< orphan*/  gamut_adjust_type; } ;
typedef  int /*<<< orphan*/  adjust ;
struct TYPE_10__ {TYPE_3__* funcs; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* dpp_set_gamut_remap ) (TYPE_5__*,struct dpp_grph_csc_adjustment*) ;} ;
struct TYPE_6__ {int enable_remap; int /*<<< orphan*/ * matrix; } ;
struct TYPE_7__ {TYPE_1__ gamut_remap_matrix; } ;

/* Variables and functions */
 int CSC_TEMPERATURE_MATRIX_SIZE ; 
 int /*<<< orphan*/  GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS ; 
 int /*<<< orphan*/  GRAPHICS_GAMUT_ADJUST_TYPE_SW ; 
 int /*<<< orphan*/  memset (struct dpp_grph_csc_adjustment*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,struct dpp_grph_csc_adjustment*) ; 

__attribute__((used)) static void dcn10_program_gamut_remap(struct pipe_ctx *pipe_ctx)
{
	int i = 0;
	struct dpp_grph_csc_adjustment adjust;
	memset(&adjust, 0, sizeof(adjust));
	adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_BYPASS;


	if (pipe_ctx->stream->gamut_remap_matrix.enable_remap == true) {
		adjust.gamut_adjust_type = GRAPHICS_GAMUT_ADJUST_TYPE_SW;
		for (i = 0; i < CSC_TEMPERATURE_MATRIX_SIZE; i++)
			adjust.temperature_matrix[i] =
				pipe_ctx->stream->gamut_remap_matrix.matrix[i];
	}

	pipe_ctx->plane_res.dpp->funcs->dpp_set_gamut_remap(pipe_ctx->plane_res.dpp, &adjust);
}