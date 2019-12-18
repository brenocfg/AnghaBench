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
struct TYPE_4__ {struct input_pixel_processor* ipp; } ;
struct pipe_ctx {TYPE_1__ plane_res; } ;
struct ipp_prescale_params {int /*<<< orphan*/  member_0; } ;
struct input_pixel_processor {TYPE_2__* funcs; } ;
struct dc_transfer_func {scalar_t__ type; int tf; } ;
struct dc_plane_state {TYPE_3__* gamma_correction; int /*<<< orphan*/  format; struct dc_transfer_func* in_transfer_func; } ;
struct TYPE_6__ {int /*<<< orphan*/  is_identity; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ipp_set_degamma ) (struct input_pixel_processor*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ipp_program_input_lut ) (struct input_pixel_processor*,TYPE_3__*) ;int /*<<< orphan*/  (* ipp_program_prescale ) (struct input_pixel_processor*,struct ipp_prescale_params*) ;} ;

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
 int /*<<< orphan*/  build_prescale_params (struct ipp_prescale_params*,struct dc_plane_state const*) ; 
 scalar_t__ dce_use_lut (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct input_pixel_processor*,struct ipp_prescale_params*) ; 
 int /*<<< orphan*/  stub2 (struct input_pixel_processor*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (struct input_pixel_processor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct input_pixel_processor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct input_pixel_processor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct input_pixel_processor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct input_pixel_processor*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
dce110_set_input_transfer_func(struct pipe_ctx *pipe_ctx,
			       const struct dc_plane_state *plane_state)
{
	struct input_pixel_processor *ipp = pipe_ctx->plane_res.ipp;
	const struct dc_transfer_func *tf = NULL;
	struct ipp_prescale_params prescale_params = { 0 };
	bool result = true;

	if (ipp == NULL)
		return false;

	if (plane_state->in_transfer_func)
		tf = plane_state->in_transfer_func;

	build_prescale_params(&prescale_params, plane_state);
	ipp->funcs->ipp_program_prescale(ipp, &prescale_params);

	if (plane_state->gamma_correction &&
			!plane_state->gamma_correction->is_identity &&
			dce_use_lut(plane_state->format))
		ipp->funcs->ipp_program_input_lut(ipp, plane_state->gamma_correction);

	if (tf == NULL) {
		/* Default case if no input transfer function specified */
		ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_sRGB);
	} else if (tf->type == TF_TYPE_PREDEFINED) {
		switch (tf->tf) {
		case TRANSFER_FUNCTION_SRGB:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_sRGB);
			break;
		case TRANSFER_FUNCTION_BT709:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_HW_xvYCC);
			break;
		case TRANSFER_FUNCTION_LINEAR:
			ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_BYPASS);
			break;
		case TRANSFER_FUNCTION_PQ:
		default:
			result = false;
			break;
		}
	} else if (tf->type == TF_TYPE_BYPASS) {
		ipp->funcs->ipp_set_degamma(ipp, IPP_DEGAMMA_MODE_BYPASS);
	} else {
		/*TF_TYPE_DISTRIBUTED_POINTS - Not supported in DCE 11*/
		result = false;
	}

	return result;
}