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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct et8ek8_sensor {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/  __et8ek8_get_pad_format (struct et8ek8_sensor*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_priv_mem ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int et8ek8_dev_init (struct v4l2_subdev*) ; 
 int et8ek8_init_controls (struct et8ek8_sensor*) ; 
 struct et8ek8_sensor* to_et8ek8_sensor (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int
et8ek8_registered(struct v4l2_subdev *subdev)
{
	struct et8ek8_sensor *sensor = to_et8ek8_sensor(subdev);
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	int rval;

	dev_dbg(&client->dev, "registered!");

	rval = device_create_file(&client->dev, &dev_attr_priv_mem);
	if (rval) {
		dev_err(&client->dev, "could not register sysfs entry\n");
		return rval;
	}

	rval = et8ek8_dev_init(subdev);
	if (rval)
		goto err_file;

	rval = et8ek8_init_controls(sensor);
	if (rval) {
		dev_err(&client->dev, "controls initialization failed\n");
		goto err_file;
	}

	__et8ek8_get_pad_format(sensor, NULL, 0, V4L2_SUBDEV_FORMAT_ACTIVE);

	return 0;

err_file:
	device_remove_file(&client->dev, &dev_attr_priv_mem);

	return rval;
}