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
struct venus_inst {int /*<<< orphan*/  out_height; int /*<<< orphan*/  out_width; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_2__ {scalar_t__ left; scalar_t__ top; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
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
 struct venus_inst* to_inst (struct file*) ; 

__attribute__((used)) static int
vdec_g_selection(struct file *file, void *fh, struct v4l2_selection *s)
{
	struct venus_inst *inst = to_inst(file);

	if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE &&
	    s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	switch (s->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
	case V4L2_SEL_TGT_CROP:
		if (s->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
			return -EINVAL;
		s->r.width = inst->out_width;
		s->r.height = inst->out_height;
		break;
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
	case V4L2_SEL_TGT_COMPOSE_PADDED:
		if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		s->r.width = inst->width;
		s->r.height = inst->height;
		break;
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE:
		if (s->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
			return -EINVAL;
		s->r.width = inst->out_width;
		s->r.height = inst->out_height;
		break;
	default:
		return -EINVAL;
	}

	s->r.top = 0;
	s->r.left = 0;

	return 0;
}