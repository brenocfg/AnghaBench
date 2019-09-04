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
struct v4l2_tuner {scalar_t__ audmode; int /*<<< orphan*/  type; } ;
struct v4l2_subdev {int dummy; } ;
struct tuner {scalar_t__ mode; scalar_t__ audmode; } ;

/* Variables and functions */
 scalar_t__ V4L2_TUNER_MODE_MONO ; 
 scalar_t__ V4L2_TUNER_MODE_STEREO ; 
 scalar_t__ V4L2_TUNER_RADIO ; 
 int /*<<< orphan*/  set_freq (struct tuner*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_mode (struct tuner*,int /*<<< orphan*/ ) ; 
 struct tuner* to_tuner (struct v4l2_subdev*) ; 

__attribute__((used)) static int tuner_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct tuner *t = to_tuner(sd);

	if (set_mode(t, vt->type))
		return 0;

	if (t->mode == V4L2_TUNER_RADIO) {
		t->audmode = vt->audmode;
		/*
		 * For radio audmode can only be mono or stereo. Map any
		 * other values to stereo. The actual tuner driver that is
		 * called in set_radio_freq can decide to limit the audmode to
		 * mono if only mono is supported.
		 */
		if (t->audmode != V4L2_TUNER_MODE_MONO &&
		    t->audmode != V4L2_TUNER_MODE_STEREO)
			t->audmode = V4L2_TUNER_MODE_STEREO;
	}
	set_freq(t, 0);

	return 0;
}