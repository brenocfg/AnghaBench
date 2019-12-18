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
struct imx355 {int streaming; int /*<<< orphan*/  mutex; int /*<<< orphan*/  hflip; int /*<<< orphan*/  vflip; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __v4l2_ctrl_grab (int /*<<< orphan*/ ,int) ; 
 int imx355_start_streaming (struct imx355*) ; 
 int /*<<< orphan*/  imx355_stop_streaming (struct imx355*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 struct imx355* to_imx355 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int imx355_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct imx355 *imx355 = to_imx355(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	mutex_lock(&imx355->mutex);
	if (imx355->streaming == enable) {
		mutex_unlock(&imx355->mutex);
		return 0;
	}

	if (enable) {
		ret = pm_runtime_get_sync(&client->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(&client->dev);
			goto err_unlock;
		}

		/*
		 * Apply default & customized values
		 * and then start streaming.
		 */
		ret = imx355_start_streaming(imx355);
		if (ret)
			goto err_rpm_put;
	} else {
		imx355_stop_streaming(imx355);
		pm_runtime_put(&client->dev);
	}

	imx355->streaming = enable;

	/* vflip and hflip cannot change during streaming */
	__v4l2_ctrl_grab(imx355->vflip, enable);
	__v4l2_ctrl_grab(imx355->hflip, enable);

	mutex_unlock(&imx355->mutex);

	return ret;

err_rpm_put:
	pm_runtime_put(&client->dev);
err_unlock:
	mutex_unlock(&imx355->mutex);

	return ret;
}