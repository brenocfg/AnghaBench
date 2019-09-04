#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__ top; scalar_t__ left; } ;
struct v4l2_selection {scalar_t__ type; int target; struct v4l2_rect r; } ;
struct file {int dummy; } ;
struct delta_frameinfo {int flags; int /*<<< orphan*/  aligned_height; int /*<<< orphan*/  aligned_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; struct v4l2_rect crop; } ;
struct delta_ctx {int flags; struct delta_frameinfo frameinfo; } ;

/* Variables and functions */
 int DELTA_FLAG_FRAMEINFO ; 
 int DELTA_FRAMEINFO_FLAG_CROP ; 
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
#define  V4L2_SEL_TGT_COMPOSE 131 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 130 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 129 
#define  V4L2_SEL_TGT_COMPOSE_PADDED 128 
 struct delta_ctx* to_ctx (void*) ; 

__attribute__((used)) static int delta_g_selection(struct file *file, void *fh,
			     struct v4l2_selection *s)
{
	struct delta_ctx *ctx = to_ctx(fh);
	struct delta_frameinfo *frameinfo = &ctx->frameinfo;
	struct v4l2_rect crop;

	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if ((ctx->flags & DELTA_FLAG_FRAMEINFO) &&
	    (frameinfo->flags & DELTA_FRAMEINFO_FLAG_CROP)) {
		crop = frameinfo->crop;
	} else {
		/* default to video dimensions */
		crop.left = 0;
		crop.top = 0;
		crop.width = frameinfo->width;
		crop.height = frameinfo->height;
	}

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE:
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
		/* visible area inside video */
		s->r = crop;
		break;
	case V4L2_SEL_TGT_COMPOSE_PADDED:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		/* up to aligned dimensions */
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = frameinfo->aligned_width;
		s->r.height = frameinfo->aligned_height;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}