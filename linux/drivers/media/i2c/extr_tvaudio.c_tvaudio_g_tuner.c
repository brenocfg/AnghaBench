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
struct v4l2_tuner {int capability; int /*<<< orphan*/  rxsubchans; int /*<<< orphan*/  audmode; } ;
struct v4l2_subdev {int dummy; } ;
struct CHIPSTATE {int /*<<< orphan*/  audmode; scalar_t__ radio; struct CHIPDESC* desc; } ;
struct CHIPDESC {int /*<<< orphan*/  (* getrxsubchans ) (struct CHIPSTATE*) ;} ;

/* Variables and functions */
 int V4L2_TUNER_CAP_LANG1 ; 
 int V4L2_TUNER_CAP_LANG2 ; 
 int V4L2_TUNER_CAP_STEREO ; 
 int /*<<< orphan*/  stub1 (struct CHIPSTATE*) ; 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvaudio_g_tuner(struct v4l2_subdev *sd, struct v4l2_tuner *vt)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;

	if (!desc->getrxsubchans)
		return 0;
	if (chip->radio)
		return 0;

	vt->audmode = chip->audmode;
	vt->rxsubchans = desc->getrxsubchans(chip);
	vt->capability |= V4L2_TUNER_CAP_STEREO |
		V4L2_TUNER_CAP_LANG1 | V4L2_TUNER_CAP_LANG2;

	return 0;
}