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
struct wm8739_state {int /*<<< orphan*/  hdl; int /*<<< orphan*/  clock_freq; } ;
struct v4l2_subdev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct wm8739_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8739_log_status(struct v4l2_subdev *sd)
{
	struct wm8739_state *state = to_state(sd);

	v4l2_info(sd, "Frequency: %u Hz\n", state->clock_freq);
	v4l2_ctrl_handler_log_status(&state->hdl, sd->name);
	return 0;
}