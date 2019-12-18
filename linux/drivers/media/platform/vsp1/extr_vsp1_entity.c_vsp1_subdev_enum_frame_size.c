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
struct vsp1_entity {int /*<<< orphan*/  lock; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_frame_size_enum {scalar_t__ code; unsigned int min_width; unsigned int max_width; unsigned int min_height; unsigned int max_height; int /*<<< orphan*/  pad; scalar_t__ index; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {scalar_t__ code; unsigned int width; unsigned int height; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_entity* to_vsp1_entity (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (struct vsp1_entity*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (struct vsp1_entity*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

int vsp1_subdev_enum_frame_size(struct v4l2_subdev *subdev,
				struct v4l2_subdev_pad_config *cfg,
				struct v4l2_subdev_frame_size_enum *fse,
				unsigned int min_width, unsigned int min_height,
				unsigned int max_width, unsigned int max_height)
{
	struct vsp1_entity *entity = to_vsp1_entity(subdev);
	struct v4l2_subdev_pad_config *config;
	struct v4l2_mbus_framefmt *format;
	int ret = 0;

	config = vsp1_entity_get_pad_config(entity, cfg, fse->which);
	if (!config)
		return -EINVAL;

	format = vsp1_entity_get_pad_format(entity, config, fse->pad);

	mutex_lock(&entity->lock);

	if (fse->index || fse->code != format->code) {
		ret = -EINVAL;
		goto done;
	}

	if (fse->pad == 0) {
		fse->min_width = min_width;
		fse->max_width = max_width;
		fse->min_height = min_height;
		fse->max_height = max_height;
	} else {
		/*
		 * The size on the source pad are fixed and always identical to
		 * the size on the sink pad.
		 */
		fse->min_width = format->width;
		fse->max_width = format->width;
		fse->min_height = format->height;
		fse->max_height = format->height;
	}

done:
	mutex_unlock(&entity->lock);
	return ret;
}