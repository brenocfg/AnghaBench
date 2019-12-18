#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct saa7146_pci_extension_data {int dummy; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct mxb {int /*<<< orphan*/  vbi_dev; int /*<<< orphan*/  video_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  vidioc_s_register; int /*<<< orphan*/  vidioc_g_register; int /*<<< orphan*/  vidioc_s_audio; int /*<<< orphan*/  vidioc_g_audio; int /*<<< orphan*/  vidioc_enumaudio; int /*<<< orphan*/  vidioc_s_frequency; int /*<<< orphan*/  vidioc_g_frequency; int /*<<< orphan*/  vidioc_s_tuner; int /*<<< orphan*/  vidioc_g_tuner; int /*<<< orphan*/  vidioc_querystd; int /*<<< orphan*/  vidioc_s_input; int /*<<< orphan*/  vidioc_g_input; int /*<<< orphan*/  vidioc_enum_input; } ;
struct TYPE_5__ {TYPE_1__ vid_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB_EE (char*,struct saa7146_dev*) ; 
 int /*<<< orphan*/  ERR (char*) ; 
 scalar_t__ MXB_BOARD_CAN_DO_VBI (struct saa7146_dev*) ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  VFL_TYPE_VBI ; 
 int /*<<< orphan*/  mxb_init_done (struct saa7146_dev*) ; 
 int /*<<< orphan*/  mxb_num ; 
 scalar_t__ mxb_probe (struct saa7146_dev*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ saa7146_register_device (int /*<<< orphan*/ *,struct saa7146_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_vv_init (struct saa7146_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  saa7146_vv_release (struct saa7146_dev*) ; 
 int /*<<< orphan*/  vidioc_enum_input ; 
 int /*<<< orphan*/  vidioc_enumaudio ; 
 int /*<<< orphan*/  vidioc_g_audio ; 
 int /*<<< orphan*/  vidioc_g_frequency ; 
 int /*<<< orphan*/  vidioc_g_input ; 
 int /*<<< orphan*/  vidioc_g_register ; 
 int /*<<< orphan*/  vidioc_g_tuner ; 
 int /*<<< orphan*/  vidioc_querystd ; 
 int /*<<< orphan*/  vidioc_s_audio ; 
 int /*<<< orphan*/  vidioc_s_frequency ; 
 int /*<<< orphan*/  vidioc_s_input ; 
 int /*<<< orphan*/  vidioc_s_register ; 
 int /*<<< orphan*/  vidioc_s_tuner ; 
 TYPE_2__ vv_data ; 

__attribute__((used)) static int mxb_attach(struct saa7146_dev *dev, struct saa7146_pci_extension_data *info)
{
	struct mxb *mxb;

	DEB_EE("dev:%p\n", dev);

	saa7146_vv_init(dev, &vv_data);
	if (mxb_probe(dev)) {
		saa7146_vv_release(dev);
		return -1;
	}
	mxb = (struct mxb *)dev->ext_priv;

	vv_data.vid_ops.vidioc_enum_input = vidioc_enum_input;
	vv_data.vid_ops.vidioc_g_input = vidioc_g_input;
	vv_data.vid_ops.vidioc_s_input = vidioc_s_input;
	vv_data.vid_ops.vidioc_querystd = vidioc_querystd;
	vv_data.vid_ops.vidioc_g_tuner = vidioc_g_tuner;
	vv_data.vid_ops.vidioc_s_tuner = vidioc_s_tuner;
	vv_data.vid_ops.vidioc_g_frequency = vidioc_g_frequency;
	vv_data.vid_ops.vidioc_s_frequency = vidioc_s_frequency;
	vv_data.vid_ops.vidioc_enumaudio = vidioc_enumaudio;
	vv_data.vid_ops.vidioc_g_audio = vidioc_g_audio;
	vv_data.vid_ops.vidioc_s_audio = vidioc_s_audio;
#ifdef CONFIG_VIDEO_ADV_DEBUG
	vv_data.vid_ops.vidioc_g_register = vidioc_g_register;
	vv_data.vid_ops.vidioc_s_register = vidioc_s_register;
#endif
	if (saa7146_register_device(&mxb->video_dev, dev, "mxb", VFL_TYPE_GRABBER)) {
		ERR("cannot register capture v4l2 device. skipping.\n");
		saa7146_vv_release(dev);
		return -1;
	}

	/* initialization stuff (vbi) (only for revision > 0 and for extensions which want it)*/
	if (MXB_BOARD_CAN_DO_VBI(dev)) {
		if (saa7146_register_device(&mxb->vbi_dev, dev, "mxb", VFL_TYPE_VBI)) {
			ERR("cannot register vbi v4l2 device. skipping.\n");
		}
	}

	pr_info("found Multimedia eXtension Board #%d\n", mxb_num);

	mxb_num++;
	mxb_init_done(dev);
	return 0;
}