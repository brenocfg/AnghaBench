#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_ctrl {int id; int /*<<< orphan*/  val; } ;
struct tda7432 {TYPE_4__* treble; TYPE_3__* bass; TYPE_2__* mute; TYPE_1__* balance; } ;
struct TYPE_8__ {int val; } ;
struct TYPE_7__ {int val; } ;
struct TYPE_6__ {int /*<<< orphan*/  val; } ;
struct TYPE_5__ {int val; } ;

/* Variables and functions */
 int EINVAL ; 
 int TDA7432_ATTEN_0DB ; 
 int TDA7432_LD_ON ; 
 int /*<<< orphan*/  TDA7432_LF ; 
 int /*<<< orphan*/  TDA7432_LR ; 
 int TDA7432_MUTE ; 
 int /*<<< orphan*/  TDA7432_RF ; 
 int /*<<< orphan*/  TDA7432_RR ; 
 int /*<<< orphan*/  TDA7432_TN ; 
 int /*<<< orphan*/  TDA7432_VL ; 
#define  V4L2_CID_AUDIO_BASS 130 
#define  V4L2_CID_AUDIO_MUTE 129 
#define  V4L2_CID_AUDIO_VOLUME 128 
 int /*<<< orphan*/  loudness ; 
 int /*<<< orphan*/  tda7432_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_subdev* to_sd (struct v4l2_ctrl*) ; 
 struct tda7432* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tda7432_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct v4l2_subdev *sd = to_sd(ctrl);
	struct tda7432 *t = to_state(sd);
	u8 bass, treble, volume;
	u8 lf, lr, rf, rr;

	switch (ctrl->id) {
	case V4L2_CID_AUDIO_MUTE:
		if (t->balance->val < 0) {
			/* shifted to left, attenuate right */
			rr = rf = -t->balance->val;
			lr = lf = TDA7432_ATTEN_0DB;
		} else if (t->balance->val > 0) {
			/* shifted to right, attenuate left */
			rr = rf = TDA7432_ATTEN_0DB;
			lr = lf = t->balance->val;
		} else {
			/* centered */
			rr = rf = TDA7432_ATTEN_0DB;
			lr = lf = TDA7432_ATTEN_0DB;
		}
		if (t->mute->val) {
			lf |= TDA7432_MUTE;
			lr |= TDA7432_MUTE;
			rf |= TDA7432_MUTE;
			rr |= TDA7432_MUTE;
		}
		/* Mute & update balance*/
		tda7432_write(sd, TDA7432_LF, lf);
		tda7432_write(sd, TDA7432_LR, lr);
		tda7432_write(sd, TDA7432_RF, rf);
		tda7432_write(sd, TDA7432_RR, rr);
		return 0;
	case V4L2_CID_AUDIO_VOLUME:
		volume = 0x6f - ctrl->val;
		if (loudness)		/* Turn on the loudness bit */
			volume |= TDA7432_LD_ON;

		tda7432_write(sd, TDA7432_VL, volume);
		return 0;
	case V4L2_CID_AUDIO_BASS:
		bass = t->bass->val;
		treble = t->treble->val;
		if (bass >= 0x8)
			bass = 14 - (bass - 8);
		if (treble >= 0x8)
			treble = 14 - (treble - 8);

		tda7432_write(sd, TDA7432_TN, 0x10 | (bass << 4) | treble);
		return 0;
	}
	return -EINVAL;
}