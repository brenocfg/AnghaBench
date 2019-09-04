#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct tg_color {int color_r_cr; int color_b_cb; int color_g_y; } ;
struct TYPE_5__ {int format; } ;
struct TYPE_6__ {TYPE_1__ scl_data; } ;
struct pipe_ctx {TYPE_4__* stream; TYPE_2__ plane_res; struct pipe_ctx* top_pipe; } ;
struct TYPE_8__ {TYPE_3__* out_transfer_func; } ;
struct TYPE_7__ {int /*<<< orphan*/  tf; } ;

/* Variables and functions */
 int MAX_TG_COLOR_VALUE ; 
#define  PIXEL_FORMAT_ARGB2101010 129 
#define  PIXEL_FORMAT_FP16 128 
 int /*<<< orphan*/  TRANSFER_FUNCTION_GAMMA22 ; 
 int /*<<< orphan*/  TRANSFER_FUNCTION_PQ ; 
 int /*<<< orphan*/  TRANSFER_FUNCTION_UNITY ; 

__attribute__((used)) static void dcn10_get_hdr_visual_confirm_color(
		struct pipe_ctx *pipe_ctx,
		struct tg_color *color)
{
	uint32_t color_value = MAX_TG_COLOR_VALUE;

	// Determine the overscan color based on the top-most (desktop) plane's context
	struct pipe_ctx *top_pipe_ctx  = pipe_ctx;

	while (top_pipe_ctx->top_pipe != NULL)
		top_pipe_ctx = top_pipe_ctx->top_pipe;

	switch (top_pipe_ctx->plane_res.scl_data.format) {
	case PIXEL_FORMAT_ARGB2101010:
		if (top_pipe_ctx->stream->out_transfer_func->tf == TRANSFER_FUNCTION_UNITY) {
			/* HDR10, ARGB2101010 - set boarder color to red */
			color->color_r_cr = color_value;
		}
		break;
	case PIXEL_FORMAT_FP16:
		if (top_pipe_ctx->stream->out_transfer_func->tf == TRANSFER_FUNCTION_PQ) {
			/* HDR10, FP16 - set boarder color to blue */
			color->color_b_cb = color_value;
		} else if (top_pipe_ctx->stream->out_transfer_func->tf == TRANSFER_FUNCTION_GAMMA22) {
			/* FreeSync 2 HDR - set boarder color to green */
			color->color_g_y = color_value;
		}
		break;
	default:
		/* SDR - set boarder color to Gray */
		color->color_r_cr = color_value/2;
		color->color_b_cb = color_value/2;
		color->color_g_y = color_value/2;
		break;
	}
}