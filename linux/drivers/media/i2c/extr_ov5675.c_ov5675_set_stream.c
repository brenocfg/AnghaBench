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
struct ov5675 {int streaming; int /*<<< orphan*/  mutex; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov5675_start_streaming (struct ov5675*) ; 
 int /*<<< orphan*/  ov5675_stop_streaming (struct ov5675*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 struct ov5675* to_ov5675 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5675_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct ov5675 *ov5675 = to_ov5675(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	if (ov5675->streaming == enable)
		return 0;

	mutex_lock(&ov5675->mutex);
	if (enable) {
		ret = pm_runtime_get_sync(&client->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(&client->dev);
			mutex_unlock(&ov5675->mutex);
			return ret;
		}

		ret = ov5675_start_streaming(ov5675);
		if (ret) {
			enable = 0;
			ov5675_stop_streaming(ov5675);
			pm_runtime_put(&client->dev);
		}
	} else {
		ov5675_stop_streaming(ov5675);
		pm_runtime_put(&client->dev);
	}

	ov5675->streaming = enable;
	mutex_unlock(&ov5675->mutex);

	return ret;
}