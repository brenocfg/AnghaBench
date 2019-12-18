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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct vsp1_histogram {TYPE_1__ entity; } ;
struct v4l2_subdev_selection {scalar_t__ pad; scalar_t__ target; int /*<<< orphan*/  which; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HISTO_PAD_SINK ; 
 scalar_t__ V4L2_SEL_TGT_COMPOSE ; 
 scalar_t__ V4L2_SEL_TGT_CROP ; 
 int histo_set_compose (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_selection*) ; 
 int histo_set_crop (struct v4l2_subdev*,struct v4l2_subdev_pad_config*,struct v4l2_subdev_selection*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_histogram* subdev_to_histo (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (TYPE_1__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int histo_set_selection(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_selection *sel)
{
	struct vsp1_histogram *histo = subdev_to_histo(subdev);
	struct v4l2_subdev_pad_config *config;
	int ret;

	if (sel->pad != HISTO_PAD_SINK)
		return -EINVAL;

	mutex_lock(&histo->entity.lock);

	config = vsp1_entity_get_pad_config(&histo->entity, cfg, sel->which);
	if (!config) {
		ret = -EINVAL;
		goto done;
	}

	if (sel->target == V4L2_SEL_TGT_CROP)
		ret = histo_set_crop(subdev, config, sel);
	else if (sel->target == V4L2_SEL_TGT_COMPOSE)
		ret = histo_set_compose(subdev, config, sel);
	else
		ret = -EINVAL;

done:
	mutex_unlock(&histo->entity.lock);
	return ret;
}