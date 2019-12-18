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
struct vp27smpx_state {int /*<<< orphan*/  radio; } ;
struct v4l2_tuner {int /*<<< orphan*/  audmode; } ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 struct vp27smpx_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  vp27smpx_set_audmode (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vp27smpx_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct vp27smpx_state *state = to_state(sd);

	if (!state->radio)
		vp27smpx_set_audmode(sd, vt->audmode);
	return 0;
}