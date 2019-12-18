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
struct pwl_params {int dummy; } ;
struct TYPE_5__ {struct dpp* dpp; } ;
struct pipe_ctx {TYPE_2__ plane_res; } ;
struct dpp {TYPE_1__* funcs; struct pwl_params regamma_params; } ;
struct dc_plane_state {TYPE_3__* blend_tf; } ;
struct TYPE_6__ {scalar_t__ type; struct pwl_params pwl; } ;
struct TYPE_4__ {int (* dpp_program_blnd_lut ) (struct dpp*,struct pwl_params*) ;} ;

/* Variables and functions */
 scalar_t__ TF_TYPE_DISTRIBUTED_POINTS ; 
 scalar_t__ TF_TYPE_HWPWL ; 
 int /*<<< orphan*/  cm_helper_translate_curve_to_hw_format (TYPE_3__*,struct pwl_params*,int) ; 
 int stub1 (struct dpp*,struct pwl_params*) ; 

__attribute__((used)) static bool dcn20_set_blend_lut(
	struct pipe_ctx *pipe_ctx, const struct dc_plane_state *plane_state)
{
	struct dpp *dpp_base = pipe_ctx->plane_res.dpp;
	bool result = true;
	struct pwl_params *blend_lut = NULL;

	if (plane_state->blend_tf) {
		if (plane_state->blend_tf->type == TF_TYPE_HWPWL)
			blend_lut = &plane_state->blend_tf->pwl;
		else if (plane_state->blend_tf->type == TF_TYPE_DISTRIBUTED_POINTS) {
			cm_helper_translate_curve_to_hw_format(
					plane_state->blend_tf,
					&dpp_base->regamma_params, false);
			blend_lut = &dpp_base->regamma_params;
		}
	}
	result = dpp_base->funcs->dpp_program_blnd_lut(dpp_base, blend_lut);

	return result;
}