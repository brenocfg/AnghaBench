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
struct v4l2_subdev_pad_config {int dummy; } ;
struct v4l2_subdev_format {int /*<<< orphan*/  which; int /*<<< orphan*/  format; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9m032 {int /*<<< orphan*/  lock; scalar_t__ streaming; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FORMAT_ACTIVE ; 
 int /*<<< orphan*/ * __mt9m032_get_pad_format (struct mt9m032*,struct v4l2_subdev_pad_config*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9m032* to_mt9m032 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m032_set_pad_format(struct v4l2_subdev *subdev,
				  struct v4l2_subdev_pad_config *cfg,
				  struct v4l2_subdev_format *fmt)
{
	struct mt9m032 *sensor = to_mt9m032(subdev);
	int ret;

	mutex_lock(&sensor->lock);

	if (sensor->streaming && fmt->which == V4L2_SUBDEV_FORMAT_ACTIVE) {
		ret = -EBUSY;
		goto done;
	}

	/* Scaling is not supported, the format is thus fixed. */
	fmt->format = *__mt9m032_get_pad_format(sensor, cfg, fmt->which);
	ret = 0;

done:
	mutex_unlock(&sensor->lock);
	return ret;
}