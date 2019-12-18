#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int device_caps; TYPE_4__* ctrl_handler; TYPE_9__* fops; TYPE_3__* v4l2_dev; int /*<<< orphan*/ * lock; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int error; } ;
struct TYPE_13__ {struct module* owner; } ;
struct radio_tea5777 {long long write_reg; int freq; TYPE_1__ vd; TYPE_3__* v4l2_dev; TYPE_4__ ctrl_handler; TYPE_9__ fops; int /*<<< orphan*/  mutex; int /*<<< orphan*/  audmode; } ;
struct module {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 long long TEA5777_W_CHP0_SHIFT ; 
 long long TEA5777_W_IFCE_SHIFT ; 
 long long TEA5777_W_IFW_SHIFT ; 
 long long TEA5777_W_INTEXT_SHIFT ; 
 long long TEA5777_W_SLEV_SHIFT ; 
 int V4L2_CAP_HW_FREQ_SEEK ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_TUNER_MODE_STEREO ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int radio_tea5777_set_freq (struct radio_tea5777*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tea575x_ctrl_ops ; 
 TYPE_9__ tea575x_fops ; 
 TYPE_1__ tea575x_radio ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_err (TYPE_3__*,char*,...) ; 
 int video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct radio_tea5777*) ; 

int radio_tea5777_init(struct radio_tea5777 *tea, struct module *owner)
{
	int res;

	tea->write_reg = (1LL << TEA5777_W_IFCE_SHIFT) |
			 (1LL << TEA5777_W_IFW_SHIFT) |
			 (1LL << TEA5777_W_INTEXT_SHIFT) |
			 (1LL << TEA5777_W_CHP0_SHIFT) |
			 (1LL << TEA5777_W_SLEV_SHIFT);
	tea->freq = 90500 * 16;	/* 90.5Mhz default */
	tea->audmode = V4L2_TUNER_MODE_STEREO;
	res = radio_tea5777_set_freq(tea);
	if (res) {
		v4l2_err(tea->v4l2_dev, "can't set initial freq (%d)\n", res);
		return res;
	}

	tea->vd = tea575x_radio;
	video_set_drvdata(&tea->vd, tea);
	mutex_init(&tea->mutex);
	strscpy(tea->vd.name, tea->v4l2_dev->name, sizeof(tea->vd.name));
	tea->vd.lock = &tea->mutex;
	tea->vd.v4l2_dev = tea->v4l2_dev;
	tea->vd.device_caps = V4L2_CAP_TUNER | V4L2_CAP_RADIO |
			      V4L2_CAP_HW_FREQ_SEEK;
	tea->fops = tea575x_fops;
	tea->fops.owner = owner;
	tea->vd.fops = &tea->fops;

	tea->vd.ctrl_handler = &tea->ctrl_handler;
	v4l2_ctrl_handler_init(&tea->ctrl_handler, 1);
	v4l2_ctrl_new_std(&tea->ctrl_handler, &tea575x_ctrl_ops,
			  V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);
	res = tea->ctrl_handler.error;
	if (res) {
		v4l2_err(tea->v4l2_dev, "can't initialize controls\n");
		v4l2_ctrl_handler_free(&tea->ctrl_handler);
		return res;
	}
	v4l2_ctrl_handler_setup(&tea->ctrl_handler);

	res = video_register_device(&tea->vd, VFL_TYPE_RADIO, -1);
	if (res) {
		v4l2_err(tea->v4l2_dev, "can't register video device!\n");
		v4l2_ctrl_handler_free(tea->vd.ctrl_handler);
		return res;
	}

	return 0;
}