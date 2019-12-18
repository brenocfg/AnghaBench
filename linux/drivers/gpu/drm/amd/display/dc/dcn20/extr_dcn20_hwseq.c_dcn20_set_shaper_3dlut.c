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
struct pwl_params {int dummy; } ;
struct TYPE_7__ {struct dpp* dpp; } ;
struct pipe_ctx {TYPE_1__ plane_res; } ;
struct dpp {TYPE_5__* funcs; struct pwl_params shaper_params; } ;
struct dc_plane_state {TYPE_4__* lut3d_func; TYPE_6__* in_shaper_func; } ;
struct TYPE_12__ {scalar_t__ type; struct pwl_params pwl; } ;
struct TYPE_11__ {int (* dpp_program_shaper_lut ) (struct dpp*,struct pwl_params*) ;int (* dpp_program_3dlut ) (struct dpp*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dpp_set_hdr_multiplier ) (struct dpp*,int) ;} ;
struct TYPE_8__ {int initialized; } ;
struct TYPE_9__ {TYPE_2__ bits; } ;
struct TYPE_10__ {int hdr_multiplier; TYPE_3__ state; int /*<<< orphan*/  lut_3d; } ;

/* Variables and functions */
 scalar_t__ TF_TYPE_DISTRIBUTED_POINTS ; 
 scalar_t__ TF_TYPE_HWPWL ; 
 int /*<<< orphan*/  cm_helper_translate_curve_to_hw_format (TYPE_6__*,struct pwl_params*,int) ; 
 int stub1 (struct dpp*,struct pwl_params*) ; 
 int stub2 (struct dpp*,int /*<<< orphan*/ *) ; 
 int stub3 (struct dpp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct dpp*,int) ; 
 int /*<<< orphan*/  stub5 (struct dpp*,int) ; 

__attribute__((used)) static bool dcn20_set_shaper_3dlut(
	struct pipe_ctx *pipe_ctx, const struct dc_plane_state *plane_state)
{
	struct dpp *dpp_base = pipe_ctx->plane_res.dpp;
	bool result = true;
	struct pwl_params *shaper_lut = NULL;

	if (plane_state->in_shaper_func) {
		if (plane_state->in_shaper_func->type == TF_TYPE_HWPWL)
			shaper_lut = &plane_state->in_shaper_func->pwl;
		else if (plane_state->in_shaper_func->type == TF_TYPE_DISTRIBUTED_POINTS) {
			cm_helper_translate_curve_to_hw_format(
					plane_state->in_shaper_func,
					&dpp_base->shaper_params, true);
			shaper_lut = &dpp_base->shaper_params;
		}
	}

	result = dpp_base->funcs->dpp_program_shaper_lut(dpp_base, shaper_lut);
	if (plane_state->lut3d_func &&
		plane_state->lut3d_func->state.bits.initialized == 1)
		result = dpp_base->funcs->dpp_program_3dlut(dpp_base,
								&plane_state->lut3d_func->lut_3d);
	else
		result = dpp_base->funcs->dpp_program_3dlut(dpp_base, NULL);

	if (plane_state->lut3d_func &&
		plane_state->lut3d_func->state.bits.initialized == 1 &&
		plane_state->lut3d_func->hdr_multiplier != 0)
		dpp_base->funcs->dpp_set_hdr_multiplier(dpp_base,
				plane_state->lut3d_func->hdr_multiplier);
	else
		dpp_base->funcs->dpp_set_hdr_multiplier(dpp_base, 0x1f000);

	return result;
}