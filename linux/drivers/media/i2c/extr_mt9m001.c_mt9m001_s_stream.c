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
struct mt9m001 {int streaming; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hdl; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9M001_OUTPUT_CONTROL ; 
 int __v4l2_ctrl_handler_setup (int /*<<< orphan*/ *) ; 
 int mt9m001_apply_selection (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int reg_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct mt9m001* to_mt9m001 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m001_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct mt9m001 *mt9m001 = to_mt9m001(client);
	int ret = 0;

	mutex_lock(&mt9m001->mutex);

	if (mt9m001->streaming == enable)
		goto done;

	if (enable) {
		ret = pm_runtime_get_sync(&client->dev);
		if (ret < 0)
			goto put_unlock;

		ret = mt9m001_apply_selection(sd);
		if (ret)
			goto put_unlock;

		ret = __v4l2_ctrl_handler_setup(&mt9m001->hdl);
		if (ret)
			goto put_unlock;

		/* Switch to master "normal" mode */
		ret = reg_write(client, MT9M001_OUTPUT_CONTROL, 2);
		if (ret < 0)
			goto put_unlock;
	} else {
		/* Switch to master stop sensor readout */
		reg_write(client, MT9M001_OUTPUT_CONTROL, 0);
		pm_runtime_put(&client->dev);
	}

	mt9m001->streaming = enable;
done:
	mutex_unlock(&mt9m001->mutex);

	return 0;

put_unlock:
	pm_runtime_put(&client->dev);
	mutex_unlock(&mt9m001->mutex);

	return ret;
}