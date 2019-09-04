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
struct TYPE_2__ {scalar_t__ top; scalar_t__ left; } ;
struct vivid_dev {TYPE_1__ sink_rect; int /*<<< orphan*/  has_compose_out; TYPE_1__ compose_out; int /*<<< orphan*/  has_crop_out; TYPE_1__ fmt_out_rect; TYPE_1__ crop_out; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTTY ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 133 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 132 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 131 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 struct vivid_dev* video_drvdata (struct file*) ; 
 TYPE_1__ vivid_max_rect ; 

int vivid_vid_out_g_selection(struct file *file, void *priv,
			      struct v4l2_selection *sel)
{
	struct vivid_dev *dev = video_drvdata(file);

	if (!dev->has_crop_out && !dev->has_compose_out)
		return -ENOTTY;
	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;

	sel->r.left = sel->r.top = 0;
	switch (sel->target) {
	case V4L2_SEL_TGT_CROP:
		if (!dev->has_crop_out)
			return -EINVAL;
		sel->r = dev->crop_out;
		break;
	case V4L2_SEL_TGT_CROP_DEFAULT:
		if (!dev->has_crop_out)
			return -EINVAL;
		sel->r = dev->fmt_out_rect;
		break;
	case V4L2_SEL_TGT_CROP_BOUNDS:
		if (!dev->has_crop_out)
			return -EINVAL;
		sel->r = vivid_max_rect;
		break;
	case V4L2_SEL_TGT_COMPOSE:
		if (!dev->has_compose_out)
			return -EINVAL;
		sel->r = dev->compose_out;
		break;
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		if (!dev->has_compose_out)
			return -EINVAL;
		sel->r = dev->sink_rect;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}