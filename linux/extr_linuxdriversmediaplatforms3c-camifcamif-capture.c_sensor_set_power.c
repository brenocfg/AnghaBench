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
struct cam_sensor {int power_count; int /*<<< orphan*/  sd; } ;
struct camif_dev {struct cam_sensor sensor; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  s_power ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sensor_set_power(struct camif_dev *camif, int on)
{
	struct cam_sensor *sensor = &camif->sensor;
	int err = 0;

	if (camif->sensor.power_count == !on)
		err = v4l2_subdev_call(sensor->sd, core, s_power, on);
	if (err == -ENOIOCTLCMD)
		err = 0;
	if (!err)
		sensor->power_count += on ? 1 : -1;

	pr_debug("on: %d, power_count: %d, err: %d\n",
		 on, sensor->power_count, err);

	return err;
}