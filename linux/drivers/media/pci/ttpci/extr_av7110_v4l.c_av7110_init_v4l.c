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
struct TYPE_4__ {int /*<<< orphan*/  vidioc_s_fmt_sliced_vbi_out; int /*<<< orphan*/  vidioc_g_fmt_sliced_vbi_out; int /*<<< orphan*/  vidioc_g_sliced_vbi_cap; int /*<<< orphan*/ * vidioc_g_fmt_vbi_cap; void* vidioc_s_frequency; void* vidioc_g_frequency; void* vidioc_s_tuner; void* vidioc_g_tuner; } ;
struct TYPE_3__ {int /*<<< orphan*/ * vidioc_g_fmt_vbi_cap; int /*<<< orphan*/  vidioc_s_audio; int /*<<< orphan*/  vidioc_g_audio; int /*<<< orphan*/  vidioc_enumaudio; void* vidioc_s_frequency; void* vidioc_g_frequency; void* vidioc_s_tuner; void* vidioc_g_tuner; int /*<<< orphan*/  vidioc_s_input; int /*<<< orphan*/  vidioc_g_input; int /*<<< orphan*/  vidioc_enum_input; } ;
struct saa7146_ext_vv {int /*<<< orphan*/  capabilities; TYPE_2__ vbi_ops; TYPE_1__ vid_ops; } ;
struct saa7146_dev {int dummy; } ;
struct av7110 {int /*<<< orphan*/  vbi_dev; int /*<<< orphan*/  arm_app; int /*<<< orphan*/  v4l_dev; scalar_t__ analog_tuner_flags; struct saa7146_dev* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int FW_VERSION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CAP_SLICED_VBI_OUTPUT ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VFL_TYPE_VBI ; 
 struct saa7146_ext_vv av7110_vv_data_c ; 
 struct saa7146_ext_vv av7110_vv_data_st ; 
 scalar_t__ saa7146_register_device (int /*<<< orphan*/ *,struct saa7146_dev*,char*,int /*<<< orphan*/ ) ; 
 int saa7146_vv_init (struct saa7146_dev*,struct saa7146_ext_vv*) ; 
 int /*<<< orphan*/  saa7146_vv_release (struct saa7146_dev*) ; 
 int /*<<< orphan*/  vidioc_enum_input ; 
 int /*<<< orphan*/  vidioc_enumaudio ; 
 int /*<<< orphan*/  vidioc_g_audio ; 
 int /*<<< orphan*/  vidioc_g_fmt_sliced_vbi_out ; 
 void* vidioc_g_frequency ; 
 int /*<<< orphan*/  vidioc_g_input ; 
 int /*<<< orphan*/  vidioc_g_sliced_vbi_cap ; 
 void* vidioc_g_tuner ; 
 int /*<<< orphan*/  vidioc_s_audio ; 
 int /*<<< orphan*/  vidioc_s_fmt_sliced_vbi_out ; 
 void* vidioc_s_frequency ; 
 int /*<<< orphan*/  vidioc_s_input ; 
 void* vidioc_s_tuner ; 

int av7110_init_v4l(struct av7110 *av7110)
{
	struct saa7146_dev* dev = av7110->dev;
	struct saa7146_ext_vv *vv_data;
	int ret;

	/* special case DVB-C: these cards have an analog tuner
	   plus need some special handling, so we have separate
	   saa7146_ext_vv data for these... */
	if (av7110->analog_tuner_flags)
		vv_data = &av7110_vv_data_c;
	else
		vv_data = &av7110_vv_data_st;
	ret = saa7146_vv_init(dev, vv_data);

	if (ret) {
		ERR("cannot init capture device. skipping\n");
		return -ENODEV;
	}
	vv_data->vid_ops.vidioc_enum_input = vidioc_enum_input;
	vv_data->vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data->vid_ops.vidioc_s_input = vidioc_s_input;
	vv_data->vid_ops.vidioc_g_tuner = vidioc_g_tuner;
	vv_data->vid_ops.vidioc_s_tuner = vidioc_s_tuner;
	vv_data->vid_ops.vidioc_g_frequency = vidioc_g_frequency;
	vv_data->vid_ops.vidioc_s_frequency = vidioc_s_frequency;
	vv_data->vid_ops.vidioc_enumaudio = vidioc_enumaudio;
	vv_data->vid_ops.vidioc_g_audio = vidioc_g_audio;
	vv_data->vid_ops.vidioc_s_audio = vidioc_s_audio;
	vv_data->vid_ops.vidioc_g_fmt_vbi_cap = NULL;

	vv_data->vbi_ops.vidioc_g_tuner = vidioc_g_tuner;
	vv_data->vbi_ops.vidioc_s_tuner = vidioc_s_tuner;
	vv_data->vbi_ops.vidioc_g_frequency = vidioc_g_frequency;
	vv_data->vbi_ops.vidioc_s_frequency = vidioc_s_frequency;
	vv_data->vbi_ops.vidioc_g_fmt_vbi_cap = NULL;
	vv_data->vbi_ops.vidioc_g_sliced_vbi_cap = vidioc_g_sliced_vbi_cap;
	vv_data->vbi_ops.vidioc_g_fmt_sliced_vbi_out = vidioc_g_fmt_sliced_vbi_out;
	vv_data->vbi_ops.vidioc_s_fmt_sliced_vbi_out = vidioc_s_fmt_sliced_vbi_out;

	if (FW_VERSION(av7110->arm_app) < 0x2623)
		vv_data->capabilities &= ~V4L2_CAP_SLICED_VBI_OUTPUT;

	if (saa7146_register_device(&av7110->v4l_dev, dev, "av7110", VFL_TYPE_GRABBER)) {
		ERR("cannot register capture device. skipping\n");
		saa7146_vv_release(dev);
		return -ENODEV;
	}
	if (FW_VERSION(av7110->arm_app) >= 0x2623) {
		if (saa7146_register_device(&av7110->vbi_dev, dev, "av7110", VFL_TYPE_VBI))
			ERR("cannot register vbi v4l2 device. skipping\n");
	}
	return 0;
}