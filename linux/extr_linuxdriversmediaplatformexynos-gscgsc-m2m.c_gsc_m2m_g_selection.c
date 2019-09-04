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
struct v4l2_selection {int target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct gsc_frame {TYPE_2__ crop; int /*<<< orphan*/  f_height; int /*<<< orphan*/  f_width; } ;
struct gsc_ctx {int dummy; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct gsc_frame*) ; 
 int PTR_ERR (struct gsc_frame*) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct gsc_frame* ctx_get_frame (struct gsc_ctx*,int /*<<< orphan*/ ) ; 
 struct gsc_ctx* fh_to_ctx (void*) ; 

__attribute__((used)) static int gsc_m2m_g_selection(struct file *file, void *fh,
			struct v4l2_selection *s)
{
	struct gsc_frame *frame;
	struct gsc_ctx *ctx = fh_to_ctx(fh);

	if ((s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT))
		return -EINVAL;

	frame = ctx_get_frame(ctx, s->type);
	if (IS_ERR(frame))
		return PTR_ERR(frame);

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = frame->f_width;
		s->r.height = frame->f_height;
		return 0;

	case V4L2_SEL_TGT_COMPOSE:
	case V4L2_SEL_TGT_CROP:
		s->r.left = frame->crop.left;
		s->r.top = frame->crop.top;
		s->r.width = frame->crop.width;
		s->r.height = frame->crop.height;
		return 0;
	}

	return -EINVAL;
}