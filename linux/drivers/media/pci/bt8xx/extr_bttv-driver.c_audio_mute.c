#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int dummy; } ;
struct bttv {TYPE_2__* sd_tda7432; TYPE_1__* sd_tvaudio; TYPE_3__* sd_msp34xx; int /*<<< orphan*/  audio_input; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl_handler; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  audio_mux_gpio (struct bttv*,int /*<<< orphan*/ ,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_s_ctrl (struct v4l2_ctrl*,int) ; 

__attribute__((used)) static int
audio_mute(struct bttv *btv, int mute)
{
	struct v4l2_ctrl *ctrl;

	audio_mux_gpio(btv, btv->audio_input, mute);

	if (btv->sd_msp34xx) {
		ctrl = v4l2_ctrl_find(btv->sd_msp34xx->ctrl_handler, V4L2_CID_AUDIO_MUTE);
		if (ctrl)
			v4l2_ctrl_s_ctrl(ctrl, mute);
	}
	if (btv->sd_tvaudio) {
		ctrl = v4l2_ctrl_find(btv->sd_tvaudio->ctrl_handler, V4L2_CID_AUDIO_MUTE);
		if (ctrl)
			v4l2_ctrl_s_ctrl(ctrl, mute);
	}
	if (btv->sd_tda7432) {
		ctrl = v4l2_ctrl_find(btv->sd_tda7432->ctrl_handler, V4L2_CID_AUDIO_MUTE);
		if (ctrl)
			v4l2_ctrl_s_ctrl(ctrl, mute);
	}
	return 0;
}