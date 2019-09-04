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
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_mbus_framefmt {int dummy; } ;

/* Variables and functions */
 struct v4l2_mbus_framefmt* v4l2_subdev_get_try_format (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,unsigned int) ; 

struct v4l2_mbus_framefmt *
vsp1_entity_get_pad_format(struct vsp1_entity *entity,
			   struct v4l2_subdev_pad_config *cfg,
			   unsigned int pad)
{
	return v4l2_subdev_get_try_format(&entity->subdev, cfg, pad);
}