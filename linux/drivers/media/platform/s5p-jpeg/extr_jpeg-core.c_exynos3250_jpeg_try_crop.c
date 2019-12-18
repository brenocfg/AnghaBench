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
struct v4l2_rect {void* height; void* width; void* top; void* left; } ;
struct TYPE_8__ {void* height; void* width; void* top; void* left; } ;
struct TYPE_7__ {void* h; void* w; } ;
struct TYPE_6__ {TYPE_1__* fmt; } ;
struct s5p_jpeg_ctx {int crop_altered; TYPE_4__ crop_rect; TYPE_3__ out_q; TYPE_2__ cap_q; } ;
struct TYPE_5__ {int fourcc; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_PIX_FMT_NV12 130 
#define  V4L2_PIX_FMT_NV21 129 
#define  V4L2_PIX_FMT_YUV420 128 
 int /*<<< orphan*/  enclosed_rectangle (struct v4l2_rect*,struct v4l2_rect*) ; 
 void* round_down (void*,int) ; 

__attribute__((used)) static int exynos3250_jpeg_try_crop(struct s5p_jpeg_ctx *ctx,
				   struct v4l2_rect *r)
{
	struct v4l2_rect base_rect;
	int w_step, h_step;

	switch (ctx->cap_q.fmt->fourcc) {
	case V4L2_PIX_FMT_NV12:
	case V4L2_PIX_FMT_NV21:
		w_step = 1;
		h_step = 2;
		break;
	case V4L2_PIX_FMT_YUV420:
		w_step = 2;
		h_step = 2;
		break;
	default:
		w_step = 1;
		h_step = 1;
		break;
	}

	base_rect.top = 0;
	base_rect.left = 0;
	base_rect.width = ctx->out_q.w;
	base_rect.height = ctx->out_q.h;

	r->width = round_down(r->width, w_step);
	r->height = round_down(r->height, h_step);
	r->left = round_down(r->left, 2);
	r->top = round_down(r->top, 2);

	if (!enclosed_rectangle(r, &base_rect))
		return -EINVAL;

	ctx->crop_rect.left = r->left;
	ctx->crop_rect.top = r->top;
	ctx->crop_rect.width = r->width;
	ctx->crop_rect.height = r->height;

	ctx->crop_altered = true;

	return 0;
}