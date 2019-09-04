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
struct cx18_av_state {int /*<<< orphan*/  vid_input; } ;
struct cx18 {int dummy; } ;

/* Variables and functions */
 int set_input (struct cx18*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cx18_av_state* to_cx18_av_state (struct v4l2_subdev*) ; 
 struct cx18* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx18_av_s_audio_routing(struct v4l2_subdev *sd,
				   u32 input, u32 output, u32 config)
{
	struct cx18_av_state *state = to_cx18_av_state(sd);
	struct cx18 *cx = v4l2_get_subdevdata(sd);
	return set_input(cx, state->vid_input, input);
}