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
typedef  scalar_t__ u32 ;
struct v4l2_subdev {int dummy; } ;
struct adv7393_state {scalar_t__ output; } ;

/* Variables and functions */
 int adv7393_setoutput (struct v4l2_subdev*,scalar_t__) ; 
 struct adv7393_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int adv7393_s_routing(struct v4l2_subdev *sd,
		u32 input, u32 output, u32 config)
{
	struct adv7393_state *state = to_state(sd);
	int err = 0;

	if (state->output == output)
		return 0;

	err = adv7393_setoutput(sd, output);
	if (!err)
		state->output = output;

	return err;
}