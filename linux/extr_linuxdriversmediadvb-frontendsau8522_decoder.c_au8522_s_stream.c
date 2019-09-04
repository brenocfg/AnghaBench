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
struct au8522_state {int /*<<< orphan*/  operational_mode; scalar_t__ current_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU8522_ANALOG_MODE ; 
 int /*<<< orphan*/  AU8522_SUSPEND_MODE ; 
 int /*<<< orphan*/  AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H ; 
 int /*<<< orphan*/  au8522_video_set (struct au8522_state*) ; 
 int /*<<< orphan*/  au8522_writereg (struct au8522_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  set_audio_input (struct au8522_state*) ; 
 struct au8522_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int au8522_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct au8522_state *state = to_state(sd);

	if (enable) {
		/*
		 * Clear out any state associated with the digital side of the
		 * chip, so that when it gets powered back up it won't think
		 * that it is already tuned
		 */
		state->current_frequency = 0;

		au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
				0x01);
		msleep(10);

		au8522_video_set(state);
		set_audio_input(state);

		state->operational_mode = AU8522_ANALOG_MODE;
	} else {
		/* This does not completely power down the device
		   (it only reduces it from around 140ma to 80ma) */
		au8522_writereg(state, AU8522_SYSTEM_MODULE_CONTROL_0_REG0A4H,
				1 << 5);
		state->operational_mode = AU8522_SUSPEND_MODE;
	}
	return 0;
}