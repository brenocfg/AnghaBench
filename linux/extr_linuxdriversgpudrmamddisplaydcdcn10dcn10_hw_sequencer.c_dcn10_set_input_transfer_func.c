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
struct TYPE_7__ {struct dpp* dpp; } ;
struct pipe_ctx {TYPE_1__ plane_res; } ;
struct dpp {int /*<<< orphan*/  degamma_params; TYPE_5__* funcs; TYPE_4__* ctx; } ;
struct dc_transfer_func {scalar_t__ type; int tf; } ;
struct dc_plane_state {TYPE_6__* gamma_correction; int /*<<< orphan*/  format; struct dc_transfer_func* in_transfer_func; } ;
struct TYPE_12__ {int /*<<< orphan*/  is_identity; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* dpp_program_degamma_pwl ) (struct dpp*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* dpp_set_degamma ) (struct dpp*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* dpp_program_input_lut ) (struct dpp*,TYPE_6__*) ;} ;
struct TYPE_10__ {TYPE_3__* dc; } ;
struct TYPE_8__ {int /*<<< orphan*/  always_use_regamma; } ;
struct TYPE_9__ {TYPE_2__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPP_DEGAMMA_MODE_BYPASS ; 
 int /*<<< orphan*/  IPP_DEGAMMA_MODE_HW_sRGB ; 
 int /*<<< orphan*/  IPP_DEGAMMA_MODE_HW_xvYCC ; 
 scalar_t__ TF_TYPE_BYPASS ; 
 scalar_t__ TF_TYPE_PREDEFINED ; 
#define  TRANSFER_FUNCTION_BT709 131 
#define  TRANSFER_FUNCTION_LINEAR 130 
#define  TRANSFER_FUNCTION_PQ 129 
#define  TRANSFER_FUNCTION_SRGB 128 
 int /*<<< orphan*/  cm_helper_translate_curve_to_degamma_hw_format (struct dc_transfer_func const*,int /*<<< orphan*/ *) ; 
 scalar_t__ dce_use_lut (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dpp*,TYPE_6__*) ; 
 int /*<<< orphan*/  stub2 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct dpp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct dpp*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool dcn10_set_input_transfer_func(struct pipe_ctx *pipe_ctx,
					  const struct dc_plane_state *plane_state)
{
	struct dpp *dpp_base = pipe_ctx->plane_res.dpp;
	const struct dc_transfer_func *tf = NULL;
	bool result = true;

	if (dpp_base == NULL)
		return false;

	if (plane_state->in_transfer_func)
		tf = plane_state->in_transfer_func;

	if (plane_state->gamma_correction &&
		!dpp_base->ctx->dc->debug.always_use_regamma
		&& !plane_state->gamma_correction->is_identity
			&& dce_use_lut(plane_state->format))
		dpp_base->funcs->dpp_program_input_lut(dpp_base, plane_state->gamma_correction);

	if (tf == NULL)
		dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
	else if (tf->type == TF_TYPE_PREDEFINED) {
		switch (tf->tf) {
		case TRANSFER_FUNCTION_SRGB:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_HW_sRGB);
			break;
		case TRANSFER_FUNCTION_BT709:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_HW_xvYCC);
			break;
		case TRANSFER_FUNCTION_LINEAR:
			dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
			break;
		case TRANSFER_FUNCTION_PQ:
		default:
			result = false;
			break;
		}
	} else if (tf->type == TF_TYPE_BYPASS) {
		dpp_base->funcs->dpp_set_degamma(dpp_base, IPP_DEGAMMA_MODE_BYPASS);
	} else {
		cm_helper_translate_curve_to_degamma_hw_format(tf,
					&dpp_base->degamma_params);
		dpp_base->funcs->dpp_program_degamma_pwl(dpp_base,
				&dpp_base->degamma_params);
		result = true;
	}

	return result;
}