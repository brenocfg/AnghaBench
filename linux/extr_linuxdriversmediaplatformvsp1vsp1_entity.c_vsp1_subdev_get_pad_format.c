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
struct v4l2_subdev_format {int /*<<< orphan*/  pad; int /*<<< orphan*/  format; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_entity* to_vsp1_entity (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (struct vsp1_entity*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vsp1_entity_get_pad_format (struct vsp1_entity*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

int vsp1_subdev_get_pad_format(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_format *fmt)
{
	struct vsp1_entity *entity = to_vsp1_entity(subdev);
	struct v4l2_subdev_pad_config *config;

	config = vsp1_entity_get_pad_config(entity, cfg, fmt->which);
	if (!config)
		return -EINVAL;

	mutex_lock(&entity->lock);
	fmt->format = *vsp1_entity_get_pad_format(entity, config, fmt->pad);
	mutex_unlock(&entity->lock);

	return 0;
}