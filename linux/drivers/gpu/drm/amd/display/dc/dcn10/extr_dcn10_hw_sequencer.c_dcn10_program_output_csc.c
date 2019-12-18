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
typedef  scalar_t__ uint16_t ;
struct TYPE_10__ {TYPE_5__* dpp; } ;
struct pipe_ctx {TYPE_4__ plane_res; TYPE_2__* stream; } ;
struct dc {int dummy; } ;
typedef  scalar_t__ int16_t ;
typedef  enum dc_color_space { ____Placeholder_dc_color_space } dc_color_space ;
struct TYPE_11__ {TYPE_3__* funcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* dpp_set_csc_default ) (TYPE_5__*,int) ;int /*<<< orphan*/  (* dpp_set_csc_adjustment ) (TYPE_5__*,scalar_t__*) ;} ;
struct TYPE_7__ {int enable_adjustment; } ;
struct TYPE_8__ {TYPE_1__ csc_color_matrix; } ;

/* Variables and functions */
 scalar_t__ dcn10_is_rear_mpo_fix_required (struct pipe_ctx*,int) ; 
 int /*<<< orphan*/  dcn10_set_csc_adjustment_rgb_mpo_fix (struct pipe_ctx*,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,int) ; 

__attribute__((used)) static void dcn10_program_output_csc(struct dc *dc,
		struct pipe_ctx *pipe_ctx,
		enum dc_color_space colorspace,
		uint16_t *matrix,
		int opp_id)
{
	if (pipe_ctx->stream->csc_color_matrix.enable_adjustment == true) {
		if (pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjustment != NULL) {

			/* MPO is broken with RGB colorspaces when OCSC matrix
			 * brightness offset >= 0 on DCN1 due to OCSC before MPC
			 * Blending adds offsets from front + rear to rear plane
			 *
			 * Fix is to set RGB bias to 0 on rear plane, top plane
			 * black value pixels add offset instead of rear + front
			 */

			int16_t rgb_bias = matrix[3];
			// matrix[3/7/11] are all the same offset value

			if (rgb_bias > 0 && dcn10_is_rear_mpo_fix_required(pipe_ctx, colorspace)) {
				dcn10_set_csc_adjustment_rgb_mpo_fix(pipe_ctx, matrix);
			} else {
				pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_adjustment(pipe_ctx->plane_res.dpp, matrix);
			}
		}
	} else {
		if (pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_default != NULL)
			pipe_ctx->plane_res.dpp->funcs->dpp_set_csc_default(pipe_ctx->plane_res.dpp, colorspace);
	}
}