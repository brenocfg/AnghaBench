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
struct ov5670 {int streaming; int /*<<< orphan*/  mutex; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov5670_start_streaming (struct ov5670*) ; 
 int ov5670_stop_streaming (struct ov5670*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 struct ov5670* to_ov5670 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5670_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct ov5670 *ov5670 = to_ov5670(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	mutex_lock(&ov5670->mutex);
	if (ov5670->streaming == enable)
		goto unlock_and_return;

	if (enable) {
		ret = pm_runtime_get_sync(&client->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(&client->dev);
			goto unlock_and_return;
		}

		ret = ov5670_start_streaming(ov5670);
		if (ret)
			goto error;
	} else {
		ret = ov5670_stop_streaming(ov5670);
		pm_runtime_put(&client->dev);
	}
	ov5670->streaming = enable;
	goto unlock_and_return;

error:
	pm_runtime_put(&client->dev);

unlock_and_return:
	mutex_unlock(&ov5670->mutex);

	return ret;
}