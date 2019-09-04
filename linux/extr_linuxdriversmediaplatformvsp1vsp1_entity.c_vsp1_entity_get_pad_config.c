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
struct vsp1_entity {struct v4l2_subdev_pad_config* config; } ;
struct v4l2_subdev_pad_config {int dummy; } ;
typedef  enum v4l2_subdev_format_whence { ____Placeholder_v4l2_subdev_format_whence } v4l2_subdev_format_whence ;

/* Variables and functions */
#define  V4L2_SUBDEV_FORMAT_ACTIVE 129 
#define  V4L2_SUBDEV_FORMAT_TRY 128 

struct v4l2_subdev_pad_config *
vsp1_entity_get_pad_config(struct vsp1_entity *entity,
			   struct v4l2_subdev_pad_config *cfg,
			   enum v4l2_subdev_format_whence which)
{
	switch (which) {
	case V4L2_SUBDEV_FORMAT_ACTIVE:
		return entity->config;
	case V4L2_SUBDEV_FORMAT_TRY:
	default:
		return cfg;
	}
}