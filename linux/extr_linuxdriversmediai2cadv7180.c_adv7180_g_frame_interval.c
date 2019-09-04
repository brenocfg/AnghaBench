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
struct TYPE_2__ {int numerator; int denominator; } ;
struct v4l2_subdev_frame_interval {TYPE_1__ interval; } ;
struct v4l2_subdev {int dummy; } ;
struct adv7180_state {int curr_norm; } ;

/* Variables and functions */
 int V4L2_STD_525_60 ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7180_g_frame_interval(struct v4l2_subdev *sd,
				    struct v4l2_subdev_frame_interval *fi)
{
	struct adv7180_state *state = to_state(sd);

	if (state->curr_norm & V4L2_STD_525_60) {
		fi->interval.numerator = 1001;
		fi->interval.denominator = 30000;
	} else {
		fi->interval.numerator = 1;
		fi->interval.denominator = 25;
	}

	return 0;
}