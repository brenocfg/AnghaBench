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
struct ov2685 {int streaming; int /*<<< orphan*/  mutex; struct i2c_client* client; int /*<<< orphan*/  ctrl_handler; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV2685_REG_VALUE_08BIT ; 
 int /*<<< orphan*/  REG_SC_CTRL_MODE ; 
 int /*<<< orphan*/  SC_CTRL_MODE_STANDBY ; 
 int /*<<< orphan*/  SC_CTRL_MODE_STREAMING ; 
 int __v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov2685_write_reg (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 struct ov2685* to_ov2685 (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov2685_s_stream(struct v4l2_subdev *sd, int on)
{
	struct ov2685 *ov2685 = to_ov2685(sd);
	struct i2c_client *client = ov2685->client;
	int ret = 0;

	mutex_lock(&ov2685->mutex);

	on = !!on;
	if (on == ov2685->streaming)
		goto unlock_and_return;

	if (on) {
		ret = pm_runtime_get_sync(&ov2685->client->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(&client->dev);
			goto unlock_and_return;
		}
		ret = __v4l2_ctrl_handler_setup(&ov2685->ctrl_handler);
		if (ret) {
			pm_runtime_put(&client->dev);
			goto unlock_and_return;
		}
		ret = ov2685_write_reg(client, REG_SC_CTRL_MODE,
				OV2685_REG_VALUE_08BIT, SC_CTRL_MODE_STREAMING);
		if (ret) {
			pm_runtime_put(&client->dev);
			goto unlock_and_return;
		}
	} else {
		ov2685_write_reg(client, REG_SC_CTRL_MODE,
				OV2685_REG_VALUE_08BIT, SC_CTRL_MODE_STANDBY);
		pm_runtime_put(&ov2685->client->dev);
	}

	ov2685->streaming = on;

unlock_and_return:
	mutex_unlock(&ov2685->mutex);

	return ret;
}