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
struct v4l2_subdev_frame_interval {int /*<<< orphan*/  interval; } ;
struct v4l2_subdev {int dummy; } ;
struct mt9m032 {int /*<<< orphan*/  lock; int /*<<< orphan*/  frame_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct v4l2_subdev_frame_interval*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct mt9m032* to_mt9m032 (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9m032_get_frame_interval(struct v4l2_subdev *subdev,
				      struct v4l2_subdev_frame_interval *fi)
{
	struct mt9m032 *sensor = to_mt9m032(subdev);

	mutex_lock(&sensor->lock);
	memset(fi, 0, sizeof(*fi));
	fi->interval = sensor->frame_interval;
	mutex_unlock(&sensor->lock);

	return 0;
}