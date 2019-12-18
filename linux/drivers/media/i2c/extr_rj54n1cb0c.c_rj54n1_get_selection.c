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
struct TYPE_2__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {scalar_t__ which; int target; TYPE_1__ r; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct rj54n1 {TYPE_1__ rect; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RJ54N1_COLUMN_SKIP ; 
 int /*<<< orphan*/  RJ54N1_MAX_HEIGHT ; 
 int /*<<< orphan*/  RJ54N1_MAX_WIDTH ; 
 int /*<<< orphan*/  RJ54N1_ROW_SKIP ; 
#define  V4L2_SEL_TGT_CROP 129 
#define  V4L2_SEL_TGT_CROP_BOUNDS 128 
 scalar_t__ V4L2_SUBDEV_FORMAT_ACTIVE ; 
 struct rj54n1* to_rj54n1 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int rj54n1_get_selection(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_selection *sel)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct rj54n1 *rj54n1 = to_rj54n1(client);

	if (sel->which != V4L2_SUBDEV_FORMAT_ACTIVE)
		return -EINVAL;

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
		sel->r.left = RJ54N1_COLUMN_SKIP;
		sel->r.top = RJ54N1_ROW_SKIP;
		sel->r.width = RJ54N1_MAX_WIDTH;
		sel->r.height = RJ54N1_MAX_HEIGHT;
		return 0;
	case V4L2_SEL_TGT_CROP:
		sel->r = rj54n1->rect;
		return 0;
	default:
		return -EINVAL;
	}
}