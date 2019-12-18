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
struct cam_sensor {int stream_count; int /*<<< orphan*/  sd; } ;
struct camif_dev {struct cam_sensor sensor; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  s_stream ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int sensor_set_streaming(struct camif_dev *camif, int on)
{
	struct cam_sensor *sensor = &camif->sensor;
	int err = 0;

	if (camif->sensor.stream_count == !on)
		err = v4l2_subdev_call(sensor->sd, video, s_stream, on);
	if (!err)
		sensor->stream_count += on ? 1 : -1;

	pr_debug("on: %d, stream_count: %d, err: %d\n",
		 on, sensor->stream_count, err);

	return err;
}