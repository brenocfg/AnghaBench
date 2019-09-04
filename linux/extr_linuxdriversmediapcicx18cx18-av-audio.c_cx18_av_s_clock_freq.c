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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;
struct cx18_av_state {scalar_t__ aud_input; } ;
struct cx18 {struct cx18_av_state av_state; } ;

/* Variables and functions */
 scalar_t__ CX18_AV_AUDIO_SERIAL2 ; 
 int cx18_av_read (struct cx18*,int) ; 
 int /*<<< orphan*/  cx18_av_write (struct cx18*,int,int) ; 
 int /*<<< orphan*/  cx18_av_write_expect (struct cx18*,int,int,int,int) ; 
 int set_audclk_freq (struct cx18*,int /*<<< orphan*/ ) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

int cx18_av_s_clock_freq(struct v4l2_subdev *sd, u32 freq)
{
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	struct cx18_av_state *state = &cx->av_state;
	int retval;
	u8 v;

	if (state->aud_input > CX18_AV_AUDIO_SERIAL2) {
		v = cx18_av_read(cx, 0x803) & ~0x10;
		cx18_av_write_expect(cx, 0x803, v, v, 0x1f);
		cx18_av_write(cx, 0x8d3, 0x1f);
	}
	v = cx18_av_read(cx, 0x810) | 0x1;
	cx18_av_write_expect(cx, 0x810, v, v, 0x0f);

	retval = set_audclk_freq(cx, freq);

	v = cx18_av_read(cx, 0x810) & ~0x1;
	cx18_av_write_expect(cx, 0x810, v, v, 0x0f);
	if (state->aud_input > CX18_AV_AUDIO_SERIAL2) {
		v = cx18_av_read(cx, 0x803) | 0x10;
		cx18_av_write_expect(cx, 0x803, v, v, 0x1f);
	}
	return retval;
}