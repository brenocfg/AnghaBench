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
struct v4l2_subdev_frame_interval {int /*<<< orphan*/  interval; } ;
struct v4l2_subdev {int dummy; } ;
struct ov7251 {int /*<<< orphan*/  lock; TYPE_1__* current_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeperframe; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ov7251* to_ov7251 (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7251_get_frame_interval(struct v4l2_subdev *subdev,
				     struct v4l2_subdev_frame_interval *fi)
{
	struct ov7251 *ov7251 = to_ov7251(subdev);

	mutex_lock(&ov7251->lock);
	fi->interval = ov7251->current_mode->timeperframe;
	mutex_unlock(&ov7251->lock);

	return 0;
}