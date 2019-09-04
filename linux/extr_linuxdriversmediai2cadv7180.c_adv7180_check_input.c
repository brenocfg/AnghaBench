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
struct adv7180_state {scalar_t__ input; } ;

/* Variables and functions */
 scalar_t__ adv7180_s_routing (struct v4l2_subdev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dbg_input ; 
 struct adv7180_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void adv7180_check_input(struct v4l2_subdev *sd)
{
	struct adv7180_state *state = to_state(sd);

	if (state->input != dbg_input)
		if (adv7180_s_routing(sd, dbg_input, 0, 0))
			/* Failed - reset dbg_input */
			dbg_input = state->input;
}