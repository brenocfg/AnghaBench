#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct et8ek8_sensor {int /*<<< orphan*/  ctrl_handler; TYPE_1__* current_reglist; struct v4l2_subdev subdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int et8ek8_i2c_write_regs (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int et8ek8_configure(struct et8ek8_sensor *sensor)
{
	struct v4l2_subdev *subdev = &sensor->subdev;
	struct i2c_client *client = v4l2_get_subdevdata(subdev);
	int rval;

	rval = et8ek8_i2c_write_regs(client, sensor->current_reglist->regs);
	if (rval)
		goto fail;

	/* Controls set while the power to the sensor is turned off are saved
	 * but not applied to the hardware. Now that we're about to start
	 * streaming apply all the current values to the hardware.
	 */
	rval = v4l2_ctrl_handler_setup(&sensor->ctrl_handler);
	if (rval)
		goto fail;

	return 0;

fail:
	dev_err(&client->dev, "sensor configuration failed\n");

	return rval;
}