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
struct v4l2_subdev_mbus_code_enum {scalar_t__ pad; unsigned int index; unsigned int code; int /*<<< orphan*/  which; } ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_mbus_framefmt {unsigned int code; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vsp1_entity* to_vsp1_entity (struct v4l2_subdev*) ; 
 struct v4l2_subdev_pad_config* vsp1_entity_get_pad_config (struct vsp1_entity*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 struct v4l2_mbus_framefmt* vsp1_entity_get_pad_format (struct vsp1_entity*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 

int vsp1_subdev_enum_mbus_code(struct v4l2_subdev *subdev,
			       struct v4l2_subdev_pad_config *cfg,
			       struct v4l2_subdev_mbus_code_enum *code,
			       const unsigned int *codes, unsigned int ncodes)
{
	struct vsp1_entity *entity = to_vsp1_entity(subdev);

	if (code->pad == 0) {
		if (code->index >= ncodes)
			return -EINVAL;

		code->code = codes[code->index];
	} else {
		struct v4l2_subdev_pad_config *config;
		struct v4l2_mbus_framefmt *format;

		/*
		 * The entity can't perform format conversion, the sink format
		 * is always identical to the source format.
		 */
		if (code->index)
			return -EINVAL;

		config = vsp1_entity_get_pad_config(entity, cfg, code->which);
		if (!config)
			return -EINVAL;

		mutex_lock(&entity->lock);
		format = vsp1_entity_get_pad_format(entity, config, 0);
		code->code = format->code;
		mutex_unlock(&entity->lock);
	}

	return 0;
}