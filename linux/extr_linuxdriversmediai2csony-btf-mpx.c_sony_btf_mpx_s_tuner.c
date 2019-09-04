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
struct v4l2_tuner {scalar_t__ type; scalar_t__ audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct sony_btf_mpx {scalar_t__ audmode; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  mpx_setup (struct sony_btf_mpx*) ; 
 struct sony_btf_mpx* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int sony_btf_mpx_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct sony_btf_mpx *t = to_state(sd);

	if (vt->type != V4L2_TUNER_ANALOG_TV)
		return -EINVAL;

	if (vt->audmode != t->audmode) {
		t->audmode = vt->audmode;
		mpx_setup(t);
	}
	return 0;
}