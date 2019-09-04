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
struct smiapp_sensor {int streaming; TYPE_1__* src; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int smiapp_start_streaming (struct smiapp_sensor*) ; 
 int smiapp_stop_streaming (struct smiapp_sensor*) ; 
 struct smiapp_sensor* to_smiapp_sensor (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smiapp_set_stream(struct v4l2_subdev *subdev, int enable)
{
	struct smiapp_sensor *sensor = to_smiapp_sensor(subdev);
	struct i2c_client *client = v4l2_get_subdevdata(&sensor->src->sd);
	int rval;

	if (sensor->streaming == enable)
		return 0;

	if (enable) {
		rval = pm_runtime_get_sync(&client->dev);
		if (rval < 0) {
			if (rval != -EBUSY && rval != -EAGAIN)
				pm_runtime_set_active(&client->dev);
			pm_runtime_put(&client->dev);
			return rval;
		}

		sensor->streaming = true;

		rval = smiapp_start_streaming(sensor);
		if (rval < 0)
			sensor->streaming = false;
	} else {
		rval = smiapp_stop_streaming(sensor);
		sensor->streaming = false;
		pm_runtime_mark_last_busy(&client->dev);
		pm_runtime_put_autosuspend(&client->dev);
	}

	return rval;
}