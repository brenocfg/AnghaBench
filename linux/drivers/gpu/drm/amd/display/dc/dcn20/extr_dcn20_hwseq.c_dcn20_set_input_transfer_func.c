#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct dpp* dpp; } ;
struct pipe_ctx {TYPE_1__ plane_res; } ;
struct dpp {TYPE_2__* funcs; int /*<<< orphan*/  degamma_params; } ;
struct dc_transfer_func {scalar_t__ type; int tf; int /*<<< orphan*/  pwl; } ;
struct dc_plane_state {struct dc_transfer_func* in_transfer_func; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* dpp_set_degamma ) (struct dpp*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dpp_program_degamma_pwl ) (struct dpp*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
 int /*<<< orphan*/  IPP_DEGAMMA_MODE_BYPASS ; 
 int /*<<< orphan*/  IPP_DEGAMMA_MODE_HW_sRGB ; 
 int /*<<< orphan*/  IPP_DEGAMMA_MODE_HW_xvYCC ; 
 scalar_t__ TF_TYPE_BYPASS ; 
 scalar_t__ TF_TYPE_DISTRIBUTED_POINTS ; 
 scalar_t__ TF_TYPE_HWPWL ; 
 scalar_t__ TF_TYPE_PREDEFINED ; 
#define  TRANSFER_FUNCTION_BT709 131 
#define  TRANSFER_FUNCTION_LINEAR 130 
#define  TRANSFER_FUNCTION_PQ 129 
#define  TRANSFER_FUNCTION_SRGB 128 
 int /*<<< orphan*/  cm_helper_translate_curve_to_degamma_hw_format (struct dc_transfer_func const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dcn20_set_blend_lut (struct pipe_ctx*,struct dc_plane_state const*) ; 
 int /*<<< orphan*/  dcn20_set_shaper_3dlut (struct pipe_ctx*,struct dc_plane_state const*) ; 
 int /*<<< orphan*/  stub1 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dpp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct dpp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct dpp*,int /*<<< orphan*/ ) ; 

bool dcn20_set_input_transfer_func(struct pipe_ctx *pipe_ctx,
					  const struct dc_plane_state *plane_state)
{
	struct dpp *dpp_base = pipe_ctx->plane_res.dpp;
	const struct dc_transfer_func *tf = NULL;
	bool result = true;
	bool use_degamma_ram = false;

	if (dpp_base == NULL || plane_state == NULL)
		return false;

	dcn20_set_shaper_3dlut(pipe_ctx, plane_state);
	dcn20_set_blend_lut(pipe_ctx, plane_state);

	if (plane_state->in_transfer_func)
		tf = plane_state->in_transfer_func;


	if (tf == NULL) {
		dpp_base->funcs->dpp_set_degamma(dpp_base,
				IPP_DEGAMMA_MODE_BYPASS);
		return true;
	}

	if (tf->type == TF_TYPE_HWPWL || tf->type == TF_TYPE_DISTRIBUTED_POINTS)
		use_degamma_ram = true;

	if (use_degamma_ram == true) {
		if (tf->type == TF_TYPE_HWPWL)
			dpp_base->funcs->dpp_program_degamma_pwl(dpp_base,
					&tf->pwl);
		else if (tf->type == TF_TYPE_DISTRIBUTED_POINTS) {
			cm_helper_translate_curve_to_degamma_hw_format(tf,
					&dpp_base->degamma_params);
			dpp_base->funcs->dpp_program_degamma_pwl(dpp_base,
				&dpp_base->degamma_params);
		}
		return true;
	}
	/* handle here the optimized cases when de-gamma ROM could be used.
	 *
	 */
	if (tf->type == TF_TYPE_PREDEFINED) {
		switch (tf->tf) {
		case TRANSFER_FUNCTION_SRGB:
			dpp_base->funcs->dpp_set_degamma(dpp_base,
					IPP_DEGAMMA_MODE_HW_sRGB);
			break;
		case TRANSFER_FUNCTION_BT709:
			dpp_base->funcs->dpp_set_degamma(dpp_base,
					IPP_DEGAMMA_MODE_HW_xvYCC);
			break;
		case TRANSFER_FUNCTION_LINEAR:
			dpp_base->funcs->dpp_set_degamma(dpp_base,
					IPP_DEGAMMA_MODE_BYPASS);
			break;
		case TRANSFER_FUNCTION_PQ:
		default:
			result = false;
			break;
		}
	} else if (tf->type == TF_TYPE_BYPASS)
		dpp_base->funcs->dpp_set_degamma(dpp_base,
				IPP_DEGAMMA_MODE_BYPASS);
	else {
		/*
		 * if we are here, we did not handle correctly.
		 * fix is required for this use case
		 */
		BREAK_TO_DEBUGGER();
		dpp_base->funcs->dpp_set_degamma(dpp_base,
				IPP_DEGAMMA_MODE_BYPASS);
	}

	return result;
}