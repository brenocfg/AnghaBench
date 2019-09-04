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
typedef  int u8 ;
struct cx18_av_state {scalar_t__ aud_input; int /*<<< orphan*/  audclk_freq; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
 scalar_t__ CX18_AV_AUDIO_SERIAL2 ; 
 int cx18_av_read (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_av_write4 (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_av_write_expect (struct cx18*,int,int,int,int) ; 
 int /*<<< orphan*/  set_audclk_freq (struct cx18*,int /*<<< orphan*/ ) ; 

void cx18_av_audio_set_path(struct cx18 *cx)
{
	struct cx18_av_state *state = &cx->av_state;
	u8 v;

	/* stop microcontroller */
	v = cx18_av_read(cx, 0x803) & ~0x10;
	cx18_av_write_expect(cx, 0x803, v, v, 0x1f);

	/* assert soft reset */
	v = cx18_av_read(cx, 0x810) | 0x01;
	cx18_av_write_expect(cx, 0x810, v, v, 0x0f);

	/* Mute everything to prevent the PFFT! */
	cx18_av_write(cx, 0x8d3, 0x1f);

	if (state->aud_input <= CX18_AV_AUDIO_SERIAL2) {
		/* Set Path1 to Serial Audio Input */
		cx18_av_write4(cx, 0x8d0, 0x01011012);

		/* The microcontroller should not be started for the
		 * non-tuner inputs: autodetection is specific for
		 * TV audio. */
	} else {
		/* Set Path1 to Analog Demod Main Channel */
		cx18_av_write4(cx, 0x8d0, 0x1f063870);
	}

	set_audclk_freq(cx, state->audclk_freq);

	/* deassert soft reset */
	v = cx18_av_read(cx, 0x810) & ~0x01;
	cx18_av_write_expect(cx, 0x810, v, v, 0x0f);

	if (state->aud_input > CX18_AV_AUDIO_SERIAL2) {
		/* When the microcontroller detects the
		 * audio format, it will unmute the lines */
		v = cx18_av_read(cx, 0x803) | 0x10;
		cx18_av_write_expect(cx, 0x803, v, v, 0x1f);
	}
}