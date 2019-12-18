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
struct v4l2_frequency {scalar_t__ tuner; } ;
struct file {int dummy; } ;
struct dvb_usb_device {struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {int /*<<< orphan*/  cx25840; struct v4l2_frequency const* norm; int /*<<< orphan*/  tuner; int /*<<< orphan*/  tda9887; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  s_frequency ; 
 int /*<<< orphan*/  s_radio ; 
 int /*<<< orphan*/  s_std ; 
 int /*<<< orphan*/  tuner ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  video ; 
 struct video_device* video_devdata (struct file*) ; 
 struct dvb_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int cxusb_medion_s_frequency(struct file *file, void *fh,
				    const struct v4l2_frequency *freq)
{
	struct dvb_usb_device *dvbdev = video_drvdata(file);
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	struct video_device *vdev = video_devdata(file);
	int ret;

	if (freq->tuner != 0)
		return -EINVAL;

	ret = v4l2_subdev_call(cxdev->tda9887, tuner, s_frequency, freq);
	if (ret != 0)
		return ret;

	ret = v4l2_subdev_call(cxdev->tuner, tuner, s_frequency, freq);
	if (ret != 0)
		return ret;

	/*
	 * make sure that cx25840 is in a correct TV / radio mode,
	 * since calls above may have changed it for tuner / IF demod
	 */
	if (vdev->vfl_type == VFL_TYPE_GRABBER)
		v4l2_subdev_call(cxdev->cx25840, video, s_std, cxdev->norm);
	else
		v4l2_subdev_call(cxdev->cx25840, tuner, s_radio);

	return v4l2_subdev_call(cxdev->cx25840, tuner, s_frequency, freq);
}