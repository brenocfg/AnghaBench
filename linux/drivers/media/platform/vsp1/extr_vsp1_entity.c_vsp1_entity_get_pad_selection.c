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
struct v4l2_rect {int dummy; } ;

/* Variables and functions */
#define  V4L2_SEL_TGT_COMPOSE 129 
#define  V4L2_SEL_TGT_CROP 128 
 struct v4l2_rect* v4l2_subdev_get_try_compose (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,unsigned int) ; 
 struct v4l2_rect* v4l2_subdev_get_try_crop (int /*<<< orphan*/ *,struct v4l2_subdev_pad_config*,unsigned int) ; 

struct v4l2_rect *
vsp1_entity_get_pad_selection(struct vsp1_entity *entity,
			      struct v4l2_subdev_pad_config *cfg,
			      unsigned int pad, unsigned int target)
{
	switch (target) {
	case V4L2_SEL_TGT_COMPOSE:
		return v4l2_subdev_get_try_compose(&entity->subdev, cfg, pad);
	case V4L2_SEL_TGT_CROP:
		return v4l2_subdev_get_try_crop(&entity->subdev, cfg, pad);
	default:
		return NULL;
	}
}