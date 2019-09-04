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
struct v4l2_rect {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {scalar_t__ target; struct v4l2_rect r; int /*<<< orphan*/  which; int /*<<< orphan*/  reserved; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct s5k6aa {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 struct v4l2_rect* __s5k6aa_get_crop_rect (struct s5k6aa*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_get_selection(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_selection *sel)
{
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);
	struct v4l2_rect *rect;

	if (sel->target != V4L2_SEL_TGT_CROP)
		return -EINVAL;

	memset(sel->reserved, 0, sizeof(sel->reserved));

	mutex_lock(&s5k6aa->lock);
	rect = __s5k6aa_get_crop_rect(s5k6aa, cfg, sel->which);
	sel->r = *rect;
	mutex_unlock(&s5k6aa->lock);

	v4l2_dbg(1, debug, sd, "Current crop rectangle: (%d,%d)/%dx%d\n",
		 rect->left, rect->top, rect->width, rect->height);

	return 0;
}