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
struct TYPE_2__ {int height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_selection {scalar_t__ type; int target; TYPE_1__ r; } ;
struct sh_vou_device {int std; TYPE_1__ rect; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
#define  V4L2_SEL_TGT_COMPOSE 130 
#define  V4L2_SEL_TGT_COMPOSE_BOUNDS 129 
#define  V4L2_SEL_TGT_COMPOSE_DEFAULT 128 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  VOU_MAX_IMAGE_WIDTH ; 
 struct sh_vou_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int sh_vou_g_selection(struct file *file, void *fh,
			      struct v4l2_selection *sel)
{
	struct sh_vou_device *vou_dev = video_drvdata(file);

	if (sel->type != V4L2_BUF_TYPE_VIDEO_OUTPUT)
		return -EINVAL;
	switch (sel->target) {
	case V4L2_SEL_TGT_COMPOSE:
		sel->r = vou_dev->rect;
		break;
	case V4L2_SEL_TGT_COMPOSE_DEFAULT:
	case V4L2_SEL_TGT_COMPOSE_BOUNDS:
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = VOU_MAX_IMAGE_WIDTH;
		if (vou_dev->std & V4L2_STD_525_60)
			sel->r.height = 480;
		else
			sel->r.height = 576;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}