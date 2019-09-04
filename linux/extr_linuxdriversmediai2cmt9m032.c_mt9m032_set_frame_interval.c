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
struct TYPE_2__ {int denominator; } ;
struct v4l2_subdev_frame_interval {TYPE_1__ interval; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9m032 {int /*<<< orphan*/  lock; TYPE_1__ frame_interval; scalar_t__ streaming; } ;

/* Variables and functions */
 int EBUSY ; 
 int mt9m032_update_timing (struct mt9m032*,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9m032* to_mt9m032 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m032_set_frame_interval(struct v4l2_subdev *subdev,
				      struct v4l2_subdev_frame_interval *fi)
{
	struct mt9m032 *sensor = to_mt9m032(subdev);
	int ret;

	mutex_lock(&sensor->lock);

	if (sensor->streaming) {
		ret = -EBUSY;
		goto done;
	}

	/* Avoid divisions by 0. */
	if (fi->interval.denominator == 0)
		fi->interval.denominator = 1;

	ret = mt9m032_update_timing(sensor, &fi->interval);
	if (!ret)
		sensor->frame_interval = fi->interval;

done:
	mutex_unlock(&sensor->lock);
	return ret;
}