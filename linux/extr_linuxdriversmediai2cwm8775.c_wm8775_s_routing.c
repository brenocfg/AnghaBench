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
typedef  int u32 ;
struct wm8775_state {int input; int /*<<< orphan*/  vol; int /*<<< orphan*/  mute; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct wm8775_state* to_state (struct v4l2_subdev*) ; 
 scalar_t__ v4l2_ctrl_g_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 
 int /*<<< orphan*/  wm8775_set_audio (struct v4l2_subdev*,int) ; 

__attribute__((used)) static int wm8775_s_routing(struct v4l2_subdev *sd,
			    u32 input, u32 output, u32 config)
{
	struct wm8775_state *state = to_state(sd);

	/* There are 4 inputs and one output. Zero or more inputs
	   are multiplexed together to the output. Hence there are
	   16 combinations.
	   If only one input is active (the normal case) then the
	   input values 1, 2, 4 or 8 should be used. */
	if (input > 15) {
		v4l2_err(sd, "Invalid input %d.\n", input);
		return -EINVAL;
	}
	state->input = input;
	if (v4l2_ctrl_g_ctrl(state->mute))
		return 0;
	if (!v4l2_ctrl_g_ctrl(state->vol))
		return 0;
	wm8775_set_audio(sd, 1);
	return 0;
}