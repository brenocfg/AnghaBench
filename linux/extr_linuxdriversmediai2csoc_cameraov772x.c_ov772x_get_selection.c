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
struct v4l2_subdev_selection {scalar_t__ which; int target; TYPE_1__ r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OV772X_MAX_HEIGHT ; 
 int /*<<< orphan*/  OV772X_MAX_WIDTH ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  VGA_HEIGHT ; 
 int /*<<< orphan*/  VGA_WIDTH ; 

__attribute__((used)) static int ov772x_get_selection(struct v4l2_subdev *sd,
		struct v4l2_subdev_pad_config *cfg,
		struct v4l2_subdev_selection *sel)
{
	if (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		return -EINVAL;

	sel->r.left = 0;
	sel->r.top = 0;
	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		sel->r.width = OV772X_MAX_WIDTH;
		sel->r.height = OV772X_MAX_HEIGHT;
		return 0;
	case V4L2_SEL_TGT_CROP:
		sel->r.width = VGA_WIDTH;
		sel->r.height = VGA_HEIGHT;
		return 0;
	default:
		return -EINVAL;
	}
}