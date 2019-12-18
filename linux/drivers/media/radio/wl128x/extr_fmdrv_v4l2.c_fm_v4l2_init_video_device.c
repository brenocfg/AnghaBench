#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct v4l2_ctrl {int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct fmdev {int /*<<< orphan*/  ctrl_handler; TYPE_4__ v4l2_dev; TYPE_1__* radio_dev; int /*<<< orphan*/  mutex; } ;
struct TYPE_8__ {int /*<<< orphan*/ * ctrl_handler; TYPE_4__* v4l2_dev; int /*<<< orphan*/ * lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FM_DRV_NAME ; 
 int FM_PWR_LVL_HIGH ; 
 int /*<<< orphan*/  FM_PWR_LVL_LOW ; 
 int FM_RX_VOLUME_MAX ; 
 int /*<<< orphan*/  FM_RX_VOLUME_MIN ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_MUTE ; 
 int /*<<< orphan*/  V4L2_CID_AUDIO_VOLUME ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_ANTENNA_CAPACITOR ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_POWER_LEVEL ; 
 int /*<<< orphan*/  V4L2_CID_TUNE_PREEMPHASIS ; 
 int /*<<< orphan*/  V4L2_CTRL_FLAG_VOLATILE ; 
 int /*<<< orphan*/  V4L2_PREEMPHASIS_75_uS ; 
 int /*<<< orphan*/  VFL_TYPE_RADIO ; 
 int /*<<< orphan*/  fm_ctrl_ops ; 
 TYPE_1__ fm_viddev_template ; 
 int /*<<< orphan*/  fmerr (char*) ; 
 TYPE_1__ gradio_dev ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int v4l2_ctrl_handler_init (int /*<<< orphan*/ *,int) ; 
 struct v4l2_ctrl* v4l2_ctrl_new_std (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int v4l2_device_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (TYPE_4__*) ; 
 scalar_t__ video_register_device (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_1__*,struct fmdev*) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

int fm_v4l2_init_video_device(struct fmdev *fmdev, int radio_nr)
{
	struct v4l2_ctrl *ctrl;
	int ret;

	strscpy(fmdev->v4l2_dev.name, FM_DRV_NAME,
		sizeof(fmdev->v4l2_dev.name));
	ret = v4l2_device_register(NULL, &fmdev->v4l2_dev);
	if (ret < 0)
		return ret;

	/* Init mutex for core locking */
	mutex_init(&fmdev->mutex);

	/* Setup FM driver's V4L2 properties */
	gradio_dev = fm_viddev_template;

	video_set_drvdata(&gradio_dev, fmdev);

	gradio_dev.lock = &fmdev->mutex;
	gradio_dev.v4l2_dev = &fmdev->v4l2_dev;

	/* Register with V4L2 subsystem as RADIO device */
	if (video_register_device(&gradio_dev, VFL_TYPE_RADIO, radio_nr)) {
		v4l2_device_unregister(&fmdev->v4l2_dev);
		fmerr("Could not register video device\n");
		return -ENOMEM;
	}

	fmdev->radio_dev = &gradio_dev;

	/* Register to v4l2 ctrl handler framework */
	fmdev->radio_dev->ctrl_handler = &fmdev->ctrl_handler;

	ret = v4l2_ctrl_handler_init(&fmdev->ctrl_handler, 5);
	if (ret < 0) {
		fmerr("(fmdev): Can't init ctrl handler\n");
		v4l2_ctrl_handler_free(&fmdev->ctrl_handler);
		video_unregister_device(fmdev->radio_dev);
		v4l2_device_unregister(&fmdev->v4l2_dev);
		return -EBUSY;
	}

	/*
	 * Following controls are handled by V4L2 control framework.
	 * Added in ascending ID order.
	 */
	v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_AUDIO_VOLUME, FM_RX_VOLUME_MIN,
			FM_RX_VOLUME_MAX, 1, FM_RX_VOLUME_MAX);

	v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_AUDIO_MUTE, 0, 1, 1, 1);

	v4l2_ctrl_new_std_menu(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_TUNE_PREEMPHASIS, V4L2_PREEMPHASIS_75_uS,
			0, V4L2_PREEMPHASIS_75_uS);

	v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_TUNE_POWER_LEVEL, FM_PWR_LVL_LOW,
			FM_PWR_LVL_HIGH, 1, FM_PWR_LVL_HIGH);

	ctrl = v4l2_ctrl_new_std(&fmdev->ctrl_handler, &fm_ctrl_ops,
			V4L2_CID_TUNE_ANTENNA_CAPACITOR, 0,
			255, 1, 255);

	if (ctrl)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;

	return 0;
}