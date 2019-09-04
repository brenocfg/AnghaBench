#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct vsp1_uif {TYPE_2__ entity; } ;
struct TYPE_5__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct v4l2_subdev_selection {scalar_t__ pad; int target; TYPE_1__ r; int /*<<< orphan*/  which; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ UIF_PAD_SINK ; 
#define  V4L2_SEL_TGT_CROP 130 
#define  V4L2_SEL_TGT_CROP_BOUNDS 129 
#define  V4L2_SEL_TGT_CROP_DEFAULT 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_uif* to_uif (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (TYPE_2__*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (TYPE_2__*,struct v4l2_subdev_pad_config*,scalar_t__) ; 
 TYPE_1__* vsp1_entity_get_pad_selection (TYPE_2__*,struct v4l2_subdev_pad_config*,scalar_t__,int) ; 

__attribute__((used)) static int uif_get_selection(struct v4l2_subdev *subdev,
			     struct v4l2_subdev_pad_config *cfg,
			     struct v4l2_subdev_selection *sel)
{
	struct vsp1_uif *uif = to_uif(subdev);
	struct v4l2_subdev_pad_config *config;
	struct v4l2_mbus_framefmt *format;
	int ret = 0;

	if (sel->pad != UIF_PAD_SINK)
		return -EINVAL;

	mutex_lock(&uif->entity.lock);

	config = vsp1_entity_get_pad_config(&uif->entity, cfg, sel->which);
	if (!config) {
		ret = -EINVAL;
		goto done;
	}

	switch (sel->target) {
	case V4L2_SEL_TGT_CROP_BOUNDS:
	case V4L2_SEL_TGT_CROP_DEFAULT:
		format = vsp1_entity_get_pad_format(&uif->entity, config,
						    UIF_PAD_SINK);
		sel->r.left = 0;
		sel->r.top = 0;
		sel->r.width = format->width;
		sel->r.height = format->height;
		break;

	case V4L2_SEL_TGT_CROP:
		sel->r = *vsp1_entity_get_pad_selection(&uif->entity, config,
							sel->pad, sel->target);
		break;

	default:
		ret = -EINVAL;
		break;
	}

done:
	mutex_unlock(&uif->entity.lock);
	return ret;
}