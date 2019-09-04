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
struct video_device {scalar_t__ vfl_dir; } ;
struct v4l2_frequency {int tuner; int /*<<< orphan*/  frequency; int /*<<< orphan*/  type; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct hackrf_dev {int /*<<< orphan*/  f_tx; int /*<<< orphan*/  f_rx; int /*<<< orphan*/  f_dac; int /*<<< orphan*/  f_adc; int /*<<< orphan*/  dev; struct usb_interface* intf; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_TUNER_RF ; 
 int /*<<< orphan*/  V4L2_TUNER_SDR ; 
 scalar_t__ VFL_DIR_RX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct hackrf_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int hackrf_g_frequency(struct file *file, void *priv,
		struct v4l2_frequency *f)
{
	struct hackrf_dev *dev = video_drvdata(file);
	struct usb_interface *intf = dev->intf;
	struct video_device *vdev = video_devdata(file);
	int ret;

	dev_dbg(dev->dev, "tuner=%d type=%d\n", f->tuner, f->type);

	if (f->tuner == 0) {
		f->type = V4L2_TUNER_SDR;
		if (vdev->vfl_dir == VFL_DIR_RX)
			f->frequency = dev->f_adc;
		else
			f->frequency = dev->f_dac;
	} else if (f->tuner == 1) {
		f->type = V4L2_TUNER_RF;
		if (vdev->vfl_dir == VFL_DIR_RX)
			f->frequency = dev->f_rx;
		else
			f->frequency = dev->f_tx;
	} else {
		ret = -EINVAL;
		goto err;
	}

	return 0;
err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);
	return ret;
}