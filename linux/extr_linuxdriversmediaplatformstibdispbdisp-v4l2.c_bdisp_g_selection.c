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
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {TYPE_1__ r; int /*<<< orphan*/  target; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct bdisp_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ crop; } ;
struct bdisp_ctx {TYPE_2__* bdisp_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct bdisp_frame*) ; 
 int PTR_ERR (struct bdisp_frame*) ; 
#define  V4L2_BUF_TYPE_VIDEO_CAPTURE 136 
#define  V4L2_BUF_TYPE_VIDEO_OUTPUT 135 
#define  V4L2_SEL_TGT_COMPOSE 134 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 133 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 132 
#define  V4L2_SEL_TGT_COMPOSE_PADDED 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct bdisp_frame* ctx_get_frame (struct bdisp_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct bdisp_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int bdisp_g_selection(struct file *file, void *fh,
			     struct v4l2_selection *s)
{
	struct bdisp_frame *frame;
	struct bdisp_ctx *ctx = fh_to_ctx(fh);

	frame = ctx_get_frame(ctx, s->type);
	if (IS_ERR(frame)) {
		dev_err(ctx->bdisp_dev->dev, "Invalid frame (%p)\n", frame);
		return PTR_ERR(frame);
	}

	switch (s->type) {
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		switch (s->target) {
		case V4L2_SEL_TGT_CROP:
			/* cropped frame */
			s->r = frame->crop;
			break;
		case V4L2_SEL_TGT_CROP_DEFAULT:
		case V4L2_SEL_TGT_CROP_BOUNDS:
			/* complete frame */
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = frame->width;
			s->r.height = frame->height;
			break;
		default:
			dev_err(ctx->bdisp_dev->dev, "Invalid target\n");
			return -EINVAL;
		}
		break;

	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
		switch (s->target) {
		case V4L2_SEL_TGT_COMPOSE:
		case V4L2_SEL_TGT_COMPOSE_PADDED:
			/* composed (cropped) frame */
			s->r = frame->crop;
			break;
		case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		case V4L2_SEL_TGT_COMPOSE_BOUNDS:
			/* complete frame */
			s->r.left = 0;
			s->r.top = 0;
			s->r.width = frame->width;
			s->r.height = frame->height;
			break;
		default:
			dev_err(ctx->bdisp_dev->dev, "Invalid target\n");
			return -EINVAL;
		}
		break;

	default:
		dev_err(ctx->bdisp_dev->dev, "Invalid type\n");
		return -EINVAL;
	}

	return 0;
}