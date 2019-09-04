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
struct TYPE_2__ {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_subdev_frame_interval {scalar_t__ pad; TYPE_1__ interval; } ;
struct v4l2_subdev {int dummy; } ;
struct s5c73m3 {int apply_fiv; int /*<<< orphan*/  lock; scalar_t__ streaming; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ OIF_SOURCE_PAD ; 
 int __s5c73m3_set_frame_interval (struct s5c73m3*,struct v4l2_subdev_frame_interval*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  s5c73m3_dbg ; 
 int s5c73m3_set_frame_rate (struct s5c73m3*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5c73m3_oif_s_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *fi)
{
	struct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	int ret;

	if (fi->pad != OIF_SOURCE_PAD)
		return -EINVAL;

	v4l2_dbg(1, s5c73m3_dbg, sd, "Setting %d/%d frame interval\n",
		 fi->interval.numerator, fi->interval.denominator);

	mutex_lock(&state->lock);

	ret = __s5c73m3_set_frame_interval(state, fi);
	if (!ret) {
		if (state->streaming)
			ret = s5c73m3_set_frame_rate(state);
		else
			state->apply_fiv = 1;
	}
	mutex_unlock(&state->lock);
	return ret;
}