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
struct v4l2_dv_timings_cap {unsigned int pad; } ;
struct adv76xx_state {unsigned int source_pad; } ;

/* Variables and functions */
 int EINVAL ; 
 struct v4l2_dv_timings_cap* adv76xx_get_dv_timings_cap (struct v4l2_subdev*,unsigned int) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv76xx_dv_timings_cap(struct v4l2_subdev *sd,
			struct v4l2_dv_timings_cap *cap)
{
	struct adv76xx_state *state = to_state(sd);
	unsigned int pad = cap->pad;

	if (cap->pad >= state->source_pad)
		return -EINVAL;

	*cap = *adv76xx_get_dv_timings_cap(sd, pad);
	cap->pad = pad;

	return 0;
}