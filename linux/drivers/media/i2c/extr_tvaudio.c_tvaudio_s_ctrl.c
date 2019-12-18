#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u32 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct CHIPSTATE {size_t input; TYPE_2__* balance; TYPE_1__* volume; int /*<<< orphan*/  muted; struct CHIPDESC* desc; } ;
struct CHIPDESC {int /*<<< orphan*/  (* treblefunc ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  treblereg; int /*<<< orphan*/  (* bassfunc ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  bassreg; int /*<<< orphan*/  (* volfunc ) (unsigned int) ;int /*<<< orphan*/  rightreg; int /*<<< orphan*/  leftreg; int /*<<< orphan*/  inputmask; int /*<<< orphan*/ * inputmap; int /*<<< orphan*/  inputreg; int /*<<< orphan*/  inputmute; } ;
struct TYPE_4__ {unsigned int val; } ;
struct TYPE_3__ {unsigned int val; } ;

/* Variables and functions */
 int EINVAL ; 
#define  V4L2_CID_AUDIO_BASS 131 
#define  V4L2_CID_AUDIO_MUTE 130 
#define  V4L2_CID_AUDIO_TREBLE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  chip_write (struct CHIPSTATE*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chip_write_masked (struct CHIPSTATE*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  stub1 (unsigned int) ; 
 int /*<<< orphan*/  stub2 (unsigned int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvaudio_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		chip->muted = ctrl->val;
		if (chip->muted)
			chip_write_masked(chip,desc->inputreg,desc->inputmute,desc->inputmask);
		else
			chip_write_masked(chip,desc->inputreg,
					desc->inputmap[chip->input],desc->inputmask);
		return 0;
	case V4L2_CID_AUDIO_VOLUME: {
		u32 volume, balance;
		u32 left, right;

		volume = chip->volume->val;
		balance = chip->balance->val;
		left = (min(65536U - balance, 32768U) * volume) / 32768U;
		right = (min(balance, 32768U) * volume) / 32768U;

		chip_write(chip, desc->leftreg, desc->volfunc(left));
		chip_write(chip, desc->rightreg, desc->volfunc(right));
		return 0;
	}
	case V4L2_CID_AUDIO_BASS:
		chip_write(chip, desc->bassreg, desc->bassfunc(ctrl->val));
		return 0;
	case V4L2_CID_AUDIO_TREBLE:
		chip_write(chip, desc->treblereg, desc->treblefunc(ctrl->val));
		return 0;
	}
	return -EINVAL;
}