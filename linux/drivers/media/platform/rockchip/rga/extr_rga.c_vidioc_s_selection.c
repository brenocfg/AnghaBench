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
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; scalar_t__ width; scalar_t__ height; } ;
struct v4l2_selection {int target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct rockchip_rga {int /*<<< orphan*/  v4l2_dev; } ;
struct rga_frame {scalar_t__ width; scalar_t__ height; TYPE_1__ crop; } ;
struct rga_ctx {struct rockchip_rga* rga; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct rga_frame*) ; 
 scalar_t__ MIN_HEIGHT ; 
 scalar_t__ MIN_WIDTH ; 
 int PTR_ERR (struct rga_frame*) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 129 
#define  V4L2_SEL_TGT_CROP 128 
 int /*<<< orphan*/  debug ; 
 struct rga_frame* rga_get_frame (struct rga_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int vidioc_s_selection(struct file *file, void *prv,
			      struct v4l2_selection *s)
{
	struct rga_ctx *ctx = prv;
	struct rockchip_rga *rga = ctx->rga;
	struct rga_frame *f;
	int ret = 0;

	f = rga_get_frame(ctx, s->type);
	if (IS_ERR(f))
		return PTR_ERR(f);

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE:
		/*
		 * COMPOSE target is only valid for capture buffer type, return
		 * error for output buffer type
		 */
		if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		break;
	case V4L2_SEL_TGT_CROP:
		/*
		 * CROP target is only valid for output buffer type, return
		 * error for capture buffer type
		 */
		if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		break;
	/*
	 * bound and default crop/compose targets are invalid targets to
	 * try/set
	 */
	default:
		return -EINVAL;
	}

	if (s->r.top < 0 || s->r.left < 0) {
		v4l2_dbg(debug, 1, &rga->v4l2_dev,
			 "doesn't support negative values for top & left.\n");
		return -EINVAL;
	}

	if (s->r.left + s->r.width > f->width ||
	    s->r.top + s->r.height > f->height ||
	    s->r.width < MIN_WIDTH || s->r.height < MIN_HEIGHT) {
		v4l2_dbg(debug, 1, &rga->v4l2_dev, "unsupported crop value.\n");
		return -EINVAL;
	}

	f->crop = s->r;

	return ret;
}