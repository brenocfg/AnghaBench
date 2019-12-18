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
struct v4l2_subdev {int dummy; } ;
struct v4l2_dv_timings_cap {scalar_t__ pad; } ;

/* Variables and functions */
 int EINVAL ; 
 struct v4l2_dv_timings_cap adv7511_timings_cap ; 

__attribute__((used)) static int adv7511_dv_timings_cap(struct v4l2_subdev *sd,
				  struct v4l2_dv_timings_cap *cap)
{
	if (cap->pad != 0)
		return -EINVAL;

	*cap = adv7511_timings_cap;
	return 0;
}