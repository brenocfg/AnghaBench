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
struct TYPE_2__ {scalar_t__ left; scalar_t__ top; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct v4l2_subdev_selection {scalar_t__ pad; scalar_t__ target; TYPE_1__ r; int /*<<< orphan*/  flags; int /*<<< orphan*/  which; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct stimx274 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_SEL_TGT_COMPOSE ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 int __imx274_change_compose (struct stimx274*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int imx274_set_selection_crop (struct stimx274*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_selection*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct stimx274* to_imx274 (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx274_set_selection(struct v4l2_subdev *sd,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_selection *sel)
{
	struct stimx274 *imx274 = to_imx274(sd);

	if (sel->pad != 0)
		return -EINVAL;

	if (sel->target == V4L2_SEL_TGT_CROP)
		return imx274_set_selection_crop(imx274, cfg, sel);

	if (sel->target == V4L2_SEL_TGT_COMPOSE) {
		int err;

		mutex_lock(&imx274->lock);
		err =  __imx274_change_compose(imx274, cfg, sel->which,
					       &sel->r.width, &sel->r.height,
					       sel->flags);
		mutex_unlock(&imx274->lock);

		/*
		 * __imx274_change_compose already set width and
		 * height in set->r, we still need to set top-left
		 */
		if (!err) {
			sel->r.top = 0;
			sel->r.left = 0;
		}

		return err;
	}

	return -EINVAL;
}