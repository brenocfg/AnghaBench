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
struct v4l2_subdev_frame_interval {int dummy; } ;
struct v4l2_subdev {int dummy; } ;
struct s5k5baf {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  s5k5baf_set_frame_interval (struct s5k5baf*,struct v4l2_subdev_frame_interval*) ; 
 struct s5k5baf* to_s5k5baf (struct v4l2_subdev*) ; 

__attribute__((used)) static int s5k5baf_s_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *fi)
{
	struct s5k5baf *state = to_s5k5baf(sd);

	mutex_lock(&state->lock);
	s5k5baf_set_frame_interval(state, fi);
	mutex_unlock(&state->lock);
	return 0;
}