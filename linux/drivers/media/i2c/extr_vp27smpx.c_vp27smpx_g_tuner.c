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
struct vp27smpx_state {int /*<<< orphan*/  audmode; scalar_t__ radio; } ;
struct v4l2_tuner {int capability; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  audmode; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  V4L2_TUNER_SUB_MONO ; 
 struct vp27smpx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int vp27smpx_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct vp27smpx_state *state = to_state(sd);

	if (state->radio)
		return 0;
	vt->audmode = state->audmode;
	vt->capability = V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;
	vt->rxsubchans = V4L2_TUNER_SUB_MONO;
	return 0;
}