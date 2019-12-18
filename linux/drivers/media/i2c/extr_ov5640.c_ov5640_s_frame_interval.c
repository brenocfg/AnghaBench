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
struct v4l2_subdev_frame_interval {scalar_t__ pad; int /*<<< orphan*/  interval; } ;
struct v4l2_subdev {int dummy; } ;
typedef  struct ov5640_mode_info {int /*<<< orphan*/  vact; int /*<<< orphan*/  hact; } const ov5640_mode_info ;
struct ov5640_dev {int current_fr; int pending_mode_change; int /*<<< orphan*/  lock; struct ov5640_mode_info const* current_mode; int /*<<< orphan*/  frame_interval; scalar_t__ streaming; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ov5640_mode_info const* ov5640_find_mode (struct ov5640_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ov5640_try_frame_interval (struct ov5640_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ov5640_dev* to_ov5640_dev (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5640_s_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *fi)
{
	struct ov5640_dev *sensor = to_ov5640_dev(sd);
	const struct ov5640_mode_info *mode;
	int frame_rate, ret = 0;

	if (fi->pad != 0)
		return -EINVAL;

	mutex_lock(&sensor->lock);

	if (sensor->streaming) {
		ret = -EBUSY;
		goto out;
	}

	mode = sensor->current_mode;

	frame_rate = ov5640_try_frame_interval(sensor, &fi->interval,
					       mode->hact, mode->vact);
	if (frame_rate < 0) {
		/* Always return a valid frame interval value */
		fi->interval = sensor->frame_interval;
		goto out;
	}

	mode = ov5640_find_mode(sensor, frame_rate, mode->hact,
				mode->vact, true);
	if (!mode) {
		ret = -EINVAL;
		goto out;
	}

	if (mode != sensor->current_mode ||
	    frame_rate != sensor->current_fr) {
		sensor->current_fr = frame_rate;
		sensor->frame_interval = fi->interval;
		sensor->current_mode = mode;
		sensor->pending_mode_change = true;
	}
out:
	mutex_unlock(&sensor->lock);
	return ret;
}