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
struct s5k6aa {int /*<<< orphan*/  lock; TYPE_1__* fiv; } ;
struct TYPE_2__ {int /*<<< orphan*/  interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k6aa_g_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *fi)
{
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);

	mutex_lock(&s5k6aa->lock);
	fi->interval = s5k6aa->fiv->interval;
	mutex_unlock(&s5k6aa->lock);

	return 0;
}