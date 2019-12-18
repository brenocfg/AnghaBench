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
struct v4l2_tuner {int audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_state {int audmode; scalar_t__ radio; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  cx25840_and_or (struct i2c_client*,int,int,int) ; 
 scalar_t__ is_cx2583x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct cx25840_state *state = to_state(sd);
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	if (state->radio || is_cx2583x(state))
		return 0;

	switch (vt->audmode) {
	case V4L2_TUNER_MODE_MONO:
		/*
		 * mono      -> mono
		 * stereo    -> mono
		 * bilingual -> lang1
		 */
		cx25840_and_or(client, 0x809, ~0xf, 0x00);
		break;
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1:
		/*
		 * mono      -> mono
		 * stereo    -> stereo
		 * bilingual -> lang1
		 */
		cx25840_and_or(client, 0x809, ~0xf, 0x04);
		break;
	case V4L2_TUNER_MODE_LANG1_LANG2:
		/*
		 * mono      -> mono
		 * stereo    -> stereo
		 * bilingual -> lang1/lang2
		 */
		cx25840_and_or(client, 0x809, ~0xf, 0x07);
		break;
	case V4L2_TUNER_MODE_LANG2:
		/*
		 * mono      -> mono
		 * stereo    -> stereo
		 * bilingual -> lang2
		 */
		cx25840_and_or(client, 0x809, ~0xf, 0x01);
		break;
	default:
		return -EINVAL;
	}
	state->audmode = vt->audmode;
	return 0;
}