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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int /*<<< orphan*/  ctrl_handler; } ;
struct v4l2_ctrl {int dummy; } ;
struct media_entity {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  V4L2_CID_PIXEL_RATE ; 
 struct media_entity* camss_find_sensor (struct media_entity*) ; 
 struct v4l2_subdev* media_entity_to_v4l2_subdev (struct media_entity*) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_g_ctrl_int64 (struct v4l2_ctrl*) ; 

int camss_get_pixel_clock(struct media_entity *entity, u32 *pixel_clock)
{
	struct media_entity *sensor;
	struct v4l2_subdev *subdev;
	struct v4l2_ctrl *ctrl;

	sensor = camss_find_sensor(entity);
	if (!sensor)
		return -ENODEV;

	subdev = media_entity_to_v4l2_subdev(sensor);

	ctrl = v4l2_ctrl_find(subdev->ctrl_handler, V4L2_CID_PIXEL_RATE);

	if (!ctrl)
		return -EINVAL;

	*pixel_clock = v4l2_ctrl_g_ctrl_int64(ctrl);

	return 0;
}