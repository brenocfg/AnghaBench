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
struct ov8856 {int streaming; int /*<<< orphan*/  mutex; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov8856_start_streaming (struct ov8856*) ; 
 int /*<<< orphan*/  ov8856_stop_streaming (struct ov8856*) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 struct ov8856* to_ov8856 (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov8856_set_stream(struct v4l2_subdev *sd, int enable)
{
	struct ov8856 *ov8856 = to_ov8856(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = 0;

	if (ov8856->streaming == enable)
		return 0;

	mutex_lock(&ov8856->mutex);
	if (enable) {
		ret = pm_runtime_get_sync(&client->dev);
		if (ret < 0) {
			pm_runtime_put_noidle(&client->dev);
			mutex_unlock(&ov8856->mutex);
			return ret;
		}

		ret = ov8856_start_streaming(ov8856);
		if (ret) {
			enable = 0;
			ov8856_stop_streaming(ov8856);
			pm_runtime_put(&client->dev);
		}
	} else {
		ov8856_stop_streaming(ov8856);
		pm_runtime_put(&client->dev);
	}

	ov8856->streaming = enable;
	mutex_unlock(&ov8856->mutex);

	return ret;
}