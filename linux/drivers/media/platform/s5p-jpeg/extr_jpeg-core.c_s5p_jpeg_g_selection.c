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
struct TYPE_5__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_2__ r; } ;
struct TYPE_6__ {int /*<<< orphan*/  top; int /*<<< orphan*/  left; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_4__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct s5p_jpeg_ctx {TYPE_3__ crop_rect; TYPE_1__ out_q; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 134 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 133 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 132 
#define  V4L2_SEL_TGT_COMPOSE_PADDED 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct s5p_jpeg_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int s5p_jpeg_g_selection(struct file *file, void *priv,
			 struct v4l2_selection *s)
{
	struct s5p_jpeg_ctx *ctx = fh_to_ctx(priv);

	if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT &&
	    s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	/* For JPEG blob active == default == bounds */
	switch (s->target) {
	case V4L2_SEL_TGT_CROP:
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		s->r.width = ctx->out_q.w;
		s->r.height = ctx->out_q.h;
		s->r.left = 0;
		s->r.top = 0;
		break;
	case V4L2_SEL_TGT_COMPOSE:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
	case V4L2_SEL_TGT_COMPOSE_PADDED:
		s->r.width = ctx->crop_rect.width;
		s->r.height =  ctx->crop_rect.height;
		s->r.left = ctx->crop_rect.left;
		s->r.top = ctx->crop_rect.top;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}