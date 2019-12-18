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
struct video_device {scalar_t__ vfl_type; } ;
struct v4l2_tuner {scalar_t__ index; int /*<<< orphan*/  reserved; int /*<<< orphan*/  name; scalar_t__ signal; scalar_t__ afc; scalar_t__ capability; int /*<<< orphan*/  type; } ;
struct file {int dummy; } ;
struct dvb_usb_device {struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {int /*<<< orphan*/  cx25840; int /*<<< orphan*/  tuner; int /*<<< orphan*/  tda9887; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_ANALOG_TV ; 
 int /*<<< orphan*/  V4L2_TUNER_RADIO ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  g_tuner ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,struct v4l2_tuner*,int /*<<< orphan*/ ,struct v4l2_tuner*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct dvb_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int cxusb_medion_g_tuner(struct file *file, void *fh,
				struct v4l2_tuner *tuner)
{
	struct dvb_usb_device *dvbdev = video_drvdata(file);
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	struct video_device *vdev = video_devdata(file);
	int ret;

	if (tuner->index != 0)
		return -EINVAL;

	if (vdev->vfl_type == VFL_TYPE_GRABBER)
		tuner->type = V4L2_TUNER_ANALOG_TV;
	else
		tuner->type = V4L2_TUNER_RADIO;

	tuner->capability = 0;
	tuner->afc = 0;

	/*
	 * fills:
	 * always: capability (static), rangelow (static), rangehigh (static)
	 * radio mode: afc (may fail silently), rxsubchans (static), audmode
	 */
	ret = v4l2_subdev_call(cxdev->tda9887, tuner, g_tuner, tuner);
	if (ret != 0)
		return ret;

	/*
	 * fills:
	 * always: capability (static), rangelow (static), rangehigh (static)
	 * radio mode: rxsubchans (always stereo), audmode,
	 * signal (might be wrong)
	 */
	ret = v4l2_subdev_call(cxdev->tuner, tuner, g_tuner, tuner);
	if (ret != 0)
		return ret;

	tuner->signal = 0;

	/*
	 * fills: TV mode: capability, rxsubchans, audmode, signal
	 */
	ret = v4l2_subdev_call(cxdev->cx25840, tuner, g_tuner, tuner);
	if (ret != 0)
		return ret;

	if (vdev->vfl_type == VFL_TYPE_GRABBER)
		strscpy(tuner->name, "TV tuner", sizeof(tuner->name));
	else
		strscpy(tuner->name, "Radio tuner", sizeof(tuner->name));

	memset(tuner->reserved, 0, sizeof(tuner->reserved));

	return 0;
}