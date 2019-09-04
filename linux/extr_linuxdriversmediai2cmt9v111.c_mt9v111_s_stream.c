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
struct mt9v111_dev {int streaming; int pending; int /*<<< orphan*/  stream_mutex; } ;

/* Variables and functions */
 int mt9v111_hw_config (struct mt9v111_dev*) ; 
 int mt9v111_s_power (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9v111_dev* sd_to_mt9v111 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9v111_s_stream(struct v4l2_subdev *subdev, int enable)
{
	struct mt9v111_dev *mt9v111 = sd_to_mt9v111(subdev);
	int ret;

	mutex_lock(&mt9v111->stream_mutex);

	if (mt9v111->streaming == enable) {
		mutex_unlock(&mt9v111->stream_mutex);
		return 0;
	}

	ret = mt9v111_s_power(subdev, enable);
	if (ret)
		goto error_unlock;

	if (enable && mt9v111->pending) {
		ret = mt9v111_hw_config(mt9v111);
		if (ret)
			goto error_unlock;

		/*
		 * No need to update control here as far as only H/VBLANK are
		 * supported and immediately programmed to registers in .s_ctrl
		 */

		mt9v111->pending = false;
	}

	mt9v111->streaming = enable ? true : false;
	mutex_unlock(&mt9v111->stream_mutex);

	return 0;

error_unlock:
	mutex_unlock(&mt9v111->stream_mutex);

	return ret;
}