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
struct ov5695 {int streaming; int /*<<< orphan*/  mutex; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int __ov5695_start_stream (struct ov5695*) ; 
 int /*<<< orphan*/  __ov5695_stop_stream (struct ov5695*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 struct ov5695* to_ov5695 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int ov5695_s_stream(struct v4l2_subdev *sd, int on)
{
	struct ov5695 *ov5695 = to_ov5695(sd);
	struct i2c_client *client = ov5695->client;
	int ret = 0;

	mutex_lock(&ov5695->mutex);
	on = !!on;
	if (on == ov5695->streaming)
		goto unlock_and_return;

	if (on) {
		ret = pm_runtime_get_sync(&client->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(&client->dev);
			goto unlock_and_return;
		}

		ret = __ov5695_start_stream(ov5695);
		if (ret) {
			v4l2_err(sd, "start stream failed while write regs\n");
			pm_runtime_put(&client->dev);
			goto unlock_and_return;
		}
	} else {
		__ov5695_stop_stream(ov5695);
		pm_runtime_put(&client->dev);
	}

	ov5695->streaming = on;

unlock_and_return:
	mutex_unlock(&ov5695->mutex);

	return ret;
}