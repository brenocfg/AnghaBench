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
struct i2c_client {int dummy; } ;
struct cx25840_state {scalar_t__ aud_input; int /*<<< orphan*/  audclk_freq; } ;

/* Variables and functions */
 scalar_t__ CX25840_AUDIO_SERIAL ; 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ is_cx231xx (struct cx25840_state*) ; 
 scalar_t__ is_cx2388x (struct cx25840_state*) ; 
 int /*<<< orphan*/  is_cx2583x (struct cx25840_state*) ; 
 int /*<<< orphan*/  set_audclk_freq (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 

void cx25840_audio_set_path(struct i2c_client *client)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));

	if (!is_cx2583x(state)) {
		/* assert soft reset */
		cx25840_and_or(client, 0x810, ~0x1, 0x01);

		/* stop microcontroller */
		cx25840_and_or(client, 0x803, ~0x10, 0);

		/* Mute everything to prevent the PFFT! */
		cx25840_write(client, 0x8d3, 0x1f);

		if (state->aud_input == CX25840_AUDIO_SERIAL) {
			/* Set Path1 to Serial Audio Input */
			cx25840_write4(client, 0x8d0, 0x01011012);

			/* The microcontroller should not be started for the
			 * non-tuner inputs: autodetection is specific for
			 * TV audio. */
		} else {
			/* Set Path1 to Analog Demod Main Channel */
			cx25840_write4(client, 0x8d0, 0x1f063870);
		}
	}

	set_audclk_freq(client, state->audclk_freq);

	if (!is_cx2583x(state)) {
		if (state->aud_input != CX25840_AUDIO_SERIAL) {
			/* When the microcontroller detects the
			 * audio format, it will unmute the lines */
			cx25840_and_or(client, 0x803, ~0x10, 0x10);
		}

		/* deassert soft reset */
		cx25840_and_or(client, 0x810, ~0x1, 0x00);

		/* Ensure the controller is running when we exit */
		if (is_cx2388x(state) || is_cx231xx(state))
			cx25840_and_or(client, 0x803, ~0x10, 0x10);
	}
}