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
struct TYPE_2__ {scalar_t__ bus_type; } ;
struct ov5640_dev {int streaming; int pending_fmt_change; int /*<<< orphan*/  lock; TYPE_1__ ep; int /*<<< orphan*/  fmt; scalar_t__ pending_mode_change; } ;

/* Variables and functions */
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ov5640_set_framefmt (struct ov5640_dev*,int /*<<< orphan*/ *) ; 
 int ov5640_set_mode (struct ov5640_dev*) ; 
 int ov5640_set_stream_dvp (struct ov5640_dev*,int) ; 
 int ov5640_set_stream_mipi (struct ov5640_dev*,int) ; 
 struct ov5640_dev* to_ov5640_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5640_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct ov5640_dev *sensor = to_ov5640_dev(sd);
	int ret = 0;

	mutex_lock(&sensor->lock);

	if (sensor->streaming == !enable) {
		if (enable && sensor->pending_mode_change) {
			ret = ov5640_set_mode(sensor);
			if (ret)
				goto out;
		}

		if (enable && sensor->pending_fmt_change) {
			ret = ov5640_set_framefmt(sensor, &sensor->fmt);
			if (ret)
				goto out;
			sensor->pending_fmt_change = false;
		}

		if (sensor->ep.bus_type == V4L2_MBUS_CSI2_DPHY)
			ret = ov5640_set_stream_mipi(sensor, enable);
		else
			ret = ov5640_set_stream_dvp(sensor, enable);

		if (!ret)
			sensor->streaming = enable;
	}
out:
	mutex_unlock(&sensor->lock);
	return ret;
}