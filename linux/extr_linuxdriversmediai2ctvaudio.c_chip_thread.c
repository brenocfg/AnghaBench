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
struct v4l2_subdev {int dummy; } ;
struct CHIPSTATE {int prevmode; int audmode; int /*<<< orphan*/  wt; scalar_t__ radio; struct v4l2_subdev sd; struct CHIPDESC* desc; } ;
struct CHIPDESC {int (* getrxsubchans ) (struct CHIPSTATE*) ;int /*<<< orphan*/  (* setaudmode ) (struct CHIPSTATE*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
#define  V4L2_TUNER_MODE_LANG1 132 
#define  V4L2_TUNER_MODE_LANG1_LANG2 131 
#define  V4L2_TUNER_MODE_LANG2 130 
#define  V4L2_TUNER_MODE_MONO 129 
#define  V4L2_TUNER_MODE_STEREO 128 
 int V4L2_TUNER_SUB_LANG1 ; 
 int V4L2_TUNER_SUB_LANG2 ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ jiffies ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int stub1 (struct CHIPSTATE*) ; 
 int /*<<< orphan*/  stub2 (struct CHIPSTATE*,int) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*) ; 

__attribute__((used)) static int chip_thread(void *data)
{
	struct CHIPSTATE *chip = data;
	struct CHIPDESC  *desc = chip->desc;
	struct v4l2_subdev *sd = &chip->sd;
	int mode, selected;

	v4l2_dbg(1, debug, sd, "thread started\n");
	set_freezable();
	for (;;) {
		set_current_state(TASK_INTERRUPTIBLE);
		if (!kthread_should_stop())
			schedule();
		set_current_state(TASK_RUNNING);
		try_to_freeze();
		if (kthread_should_stop())
			break;
		v4l2_dbg(1, debug, sd, "thread wakeup\n");

		/* don't do anything for radio */
		if (chip->radio)
			continue;

		/* have a look what's going on */
		mode = desc->getrxsubchans(chip);
		if (mode == chip->prevmode)
			continue;

		/* chip detected a new audio mode - set it */
		v4l2_dbg(1, debug, sd, "thread checkmode\n");

		chip->prevmode = mode;

		selected = V4L2_TUNER_MODE_MONO;
		switch (chip->audmode) {
		case V4L2_TUNER_MODE_MONO:
			if (mode & V4L2_TUNER_SUB_LANG1)
				selected = V4L2_TUNER_MODE_LANG1;
			break;
		case V4L2_TUNER_MODE_STEREO:
		case V4L2_TUNER_MODE_LANG1:
			if (mode & V4L2_TUNER_SUB_LANG1)
				selected = V4L2_TUNER_MODE_LANG1;
			else if (mode & V4L2_TUNER_SUB_STEREO)
				selected = V4L2_TUNER_MODE_STEREO;
			break;
		case V4L2_TUNER_MODE_LANG2:
			if (mode & V4L2_TUNER_SUB_LANG2)
				selected = V4L2_TUNER_MODE_LANG2;
			else if (mode & V4L2_TUNER_SUB_STEREO)
				selected = V4L2_TUNER_MODE_STEREO;
			break;
		case V4L2_TUNER_MODE_LANG1_LANG2:
			if (mode & V4L2_TUNER_SUB_LANG2)
				selected = V4L2_TUNER_MODE_LANG1_LANG2;
			else if (mode & V4L2_TUNER_SUB_STEREO)
				selected = V4L2_TUNER_MODE_STEREO;
		}
		desc->setaudmode(chip, selected);

		/* schedule next check */
		mod_timer(&chip->wt, jiffies+msecs_to_jiffies(2000));
	}

	v4l2_dbg(1, debug, sd, "thread exiting\n");
	return 0;
}