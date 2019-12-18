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
struct s2250 {scalar_t__ std; int input; int audio_input; } ;

/* Variables and functions */
 scalar_t__ V4L2_STD_NTSC ; 
 scalar_t__ V4L2_STD_PAL ; 
 scalar_t__ V4L2_STD_SECAM ; 
 struct s2250* to_state (struct v4l2_subdev*) ; 
 int v4l2_ctrl_subdev_log_status (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_info (struct v4l2_subdev*,char*,char*) ; 

__attribute__((used)) static int s2250_log_status(struct v4l2_subdev *sd)
{
	struct s2250 *state = to_state(sd);

	v4l2_info(sd, "Standard: %s\n", state->std == V4L2_STD_NTSC ? "NTSC" :
					state->std == V4L2_STD_PAL ? "PAL" :
					state->std == V4L2_STD_SECAM ? "SECAM" :
					"unknown");
	v4l2_info(sd, "Input: %s\n", state->input == 0 ? "Composite" :
					state->input == 1 ? "S-video" :
					"error");
	v4l2_info(sd, "Audio input: %s\n", state->audio_input == 0 ? "Line In" :
					state->audio_input == 1 ? "Mic" :
					state->audio_input == 2 ? "Mic Boost" :
					"error");
	return v4l2_ctrl_subdev_log_status(sd);
}