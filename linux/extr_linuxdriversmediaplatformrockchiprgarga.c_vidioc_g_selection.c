#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_selection {int target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct rga_frame {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ crop; } ;
struct rga_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rga_frame*) ; 
 int PTR_ERR (struct rga_frame*) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct rga_frame* rga_get_frame (struct rga_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vidioc_g_selection(struct file *file, void *prv,
			      struct v4l2_selection *s)
{
	struct rga_ctx *ctx = prv;
	struct rga_frame *f;
	bool use_frame = false;

	f = rga_get_frame(ctx, s->type);
	if (IS_ERR(f))
		return PTR_ERR(f);

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP_BOUNDS:
		if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		break;
	case V4L2_SEL_TGT_COMPOSE:
		if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		use_frame = true;
		break;
	case V4L2_SEL_TGT_CROP:
		if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		use_frame = true;
		break;
	default:
		return -EINVAL;
	}

	if (use_frame) {
		s->r = f->crop;
	} else {
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = f->width;
		s->r.height = f->height;
	}

	return 0;
}