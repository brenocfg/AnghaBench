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
struct v4l2_subdev_frame_interval {TYPE_1__ interval; } ;
struct v4l2_subdev {int dummy; } ;
struct s5k6aa {int apply_cfg; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __s5k6aa_set_frame_interval (struct s5k6aa*,struct v4l2_subdev_frame_interval*) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct s5k6aa* to_s5k6aa (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int s5k6aa_s_frame_interval(struct v4l2_subdev *sd,
				   struct v4l2_subdev_frame_interval *fi)
{
	struct s5k6aa *s5k6aa = to_s5k6aa(sd);
	int ret;

	v4l2_dbg(1, debug, sd, "Setting %d/%d frame interval\n",
		 fi->interval.numerator, fi->interval.denominator);

	mutex_lock(&s5k6aa->lock);
	ret = __s5k6aa_set_frame_interval(s5k6aa, fi);
	s5k6aa->apply_cfg = 1;

	mutex_unlock(&s5k6aa->lock);
	return ret;
}