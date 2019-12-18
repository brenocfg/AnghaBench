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
struct vpe_q_data {int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_1__ c_rect; } ;
struct vpe_ctx {int dummy; } ;
struct v4l2_selection {int target; TYPE_1__ r; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct vpe_ctx* file2ctx (struct file*) ; 
 struct vpe_q_data* get_q_data (struct vpe_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpe_g_selection(struct file *file, void *fh,
		struct v4l2_selection *s)
{
	struct vpe_ctx *ctx = file2ctx(file);
	struct vpe_q_data *q_data;
	bool use_c_rect = false;

	if ((s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE) &&
	    (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT))
		return -EINVAL;

	q_data = get_q_data(ctx, s->type);
	if (!q_data)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		if (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		break;
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		if (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		break;
	case V4L2_SEL_TGT_COMPOSE:
		if (s->type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		use_c_rect = true;
		break;
	case V4L2_SEL_TGT_CROP:
		if (s->type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		use_c_rect = true;
		break;
	default:
		return -EINVAL;
	}

	if (use_c_rect) {
		/*
		 * for CROP/COMPOSE target type, return c_rect params from the
		 * respective buffer type
		 */
		s->r = q_data->c_rect;
	} else {
		/*
		 * for DEFAULT/BOUNDS target type, return width and height from
		 * S_FMT of the respective buffer type
		 */
		s->r.left = 0;
		s->r.top = 0;
		s->r.width = q_data->width;
		s->r.height = q_data->height;
	}

	return 0;
}