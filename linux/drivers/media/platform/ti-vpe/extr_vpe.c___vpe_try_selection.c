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
struct vpe_q_data {int flags; int height; scalar_t__ width; } ;
struct vpe_ctx {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; scalar_t__ width; int height; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  H_ALIGN ; 
 int /*<<< orphan*/  MIN_H ; 
 int /*<<< orphan*/  MIN_W ; 
 int Q_DATA_INTERLACED_SEQ_TB ; 
 int /*<<< orphan*/  S_ALIGN ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 129 
#define  V4L2_SEL_TGT_CROP 128 
 struct vpe_q_data* get_q_data (struct vpe_ctx*,scalar_t__) ; 
 int /*<<< orphan*/  v4l_bound_align_image (scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int,int*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vpe_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int __vpe_try_selection(struct vpe_ctx *ctx, struct v4l2_selection *s)
{
	struct vpe_q_data *q_data;
	int height;

	if ((s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT))
		return -EINVAL;

	q_data = get_q_data(ctx, s->type);
	if (!q_data)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE:
		/*
		 * COMPOSE target is only valid for capture buffer type, return
		 * error for output buffer type
		 */
		if (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		break;
	case V4L2_SEL_TGT_CROP:
		/*
		 * CROP target is only valid for output buffer type, return
		 * error for capture buffer type
		 */
		if (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		break;
	/*
	 * bound and default crop/compose targets are invalid targets to
	 * try/set
	 */
	default:
		return -EINVAL;
	}

	/*
	 * For SEQ_TB buffers, crop height should be less than the height of
	 * the field height, not the buffer height
	 */
	if (q_data->flags & Q_DATA_INTERLACED_SEQ_TB)
		height = q_data->height / 2;
	else
		height = q_data->height;

	if (s->r.top < 0 || s->r.left < 0) {
		vpe_err(ctx->dev, "negative values for top and left\n");
		s->r.top = s->r.left = 0;
	}

	v4l_bound_align_image(&s->r.width, MIN_W, q_data->width, 1,
		&s->r.height, MIN_H, height, H_ALIGN, S_ALIGN);

	/* adjust left/top if cropping rectangle is out of bounds */
	if (s->r.left + s->r.width > q_data->width)
		s->r.left = q_data->width - s->r.width;
	if (s->r.top + s->r.height > q_data->height)
		s->r.top = q_data->height - s->r.height;

	return 0;
}