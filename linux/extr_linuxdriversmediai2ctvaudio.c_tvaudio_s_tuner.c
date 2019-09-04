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
struct v4l2_tuner {int /*<<< orphan*/  audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct CHIPSTATE {scalar_t__ thread; int /*<<< orphan*/  audmode; scalar_t__ radio; struct CHIPDESC* desc; } ;
struct CHIPDESC {int /*<<< orphan*/  (* setaudmode ) (struct CHIPSTATE*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int /*<<< orphan*/  stub1 (struct CHIPSTATE*,int /*<<< orphan*/ ) ; 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

__attribute__((used)) static int tvaudio_s_tuner(struct v4l2_subdev *sd, const struct v4l2_tuner *vt)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;

	if (!desc->setaudmode)
		return 0;
	if (chip->radio)
		return 0;

	switch (vt->audmode) {
	case V4L2_TUNER_MODE_MONO:
	case V4L2_TUNER_MODE_STEREO:
	case V4L2_TUNER_MODE_LANG1:
	case V4L2_TUNER_MODE_LANG2:
	case V4L2_TUNER_MODE_LANG1_LANG2:
		break;
	default:
		return -EINVAL;
	}
	chip->audmode = vt->audmode;

	if (chip->thread)
		wake_up_process(chip->thread);
	else
		desc->setaudmode(chip, vt->audmode);

	return 0;
}