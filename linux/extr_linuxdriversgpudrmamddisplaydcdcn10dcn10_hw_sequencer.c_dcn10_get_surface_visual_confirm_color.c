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
typedef  void* uint32_t ;
struct tg_color {void* color_g_y; void* color_b_cb; void* color_r_cr; } ;
struct TYPE_3__ {int format; } ;
struct TYPE_4__ {TYPE_1__ scl_data; } ;
struct pipe_ctx {TYPE_2__ plane_res; } ;

/* Variables and functions */
 void* MAX_TG_COLOR_VALUE ; 
#define  PIXEL_FORMAT_420BPP10 132 
#define  PIXEL_FORMAT_420BPP8 131 
#define  PIXEL_FORMAT_ARGB2101010 130 
#define  PIXEL_FORMAT_ARGB8888 129 
#define  PIXEL_FORMAT_FP16 128 

__attribute__((used)) static void dcn10_get_surface_visual_confirm_color(
		const struct pipe_ctx *pipe_ctx,
		struct tg_color *color)
{
	uint32_t color_value = MAX_TG_COLOR_VALUE;

	switch (pipe_ctx->plane_res.scl_data.format) {
	case PIXEL_FORMAT_ARGB8888:
		/* set boarder color to red */
		color->color_r_cr = color_value;
		break;

	case PIXEL_FORMAT_ARGB2101010:
		/* set boarder color to blue */
		color->color_b_cb = color_value;
		break;
	case PIXEL_FORMAT_420BPP8:
		/* set boarder color to green */
		color->color_g_y = color_value;
		break;
	case PIXEL_FORMAT_420BPP10:
		/* set boarder color to yellow */
		color->color_g_y = color_value;
		color->color_r_cr = color_value;
		break;
	case PIXEL_FORMAT_FP16:
		/* set boarder color to white */
		color->color_r_cr = color_value;
		color->color_b_cb = color_value;
		color->color_g_y = color_value;
		break;
	default:
		break;
	}
}