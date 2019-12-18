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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct au8522_state {scalar_t__ operational_mode; int /*<<< orphan*/  aud_input; } ;

/* Variables and functions */
 scalar_t__ AU8522_ANALOG_MODE ; 
 int /*<<< orphan*/  set_audio_input (struct au8522_state*) ; 
 struct au8522_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int au8522_s_audio_routing(struct v4l2_subdev *sd,
					u32 input, u32 output, u32 config)
{
	struct au8522_state *state = to_state(sd);

	state->aud_input = input;

	if (state->operational_mode == AU8522_ANALOG_MODE)
		set_audio_input(state);

	return 0;
}