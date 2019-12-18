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
struct v4l2_enum_dv_timings {scalar_t__ pad; } ;
struct adv76xx_state {scalar_t__ source_pad; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  adv76xx_check_dv_timings ; 
 int /*<<< orphan*/  adv76xx_get_dv_timings_cap (struct v4l2_subdev*,scalar_t__) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 
 int v4l2_enum_dv_timings_cap (struct v4l2_enum_dv_timings*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adv76xx_enum_dv_timings(struct v4l2_subdev *sd,
			struct v4l2_enum_dv_timings *timings)
{
	struct adv76xx_state *state = to_state(sd);

	if (timings->pad >= state->source_pad)
		return -EINVAL;

	return v4l2_enum_dv_timings_cap(timings,
		adv76xx_get_dv_timings_cap(sd, timings->pad),
		adv76xx_check_dv_timings, NULL);
}