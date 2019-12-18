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
typedef  scalar_t__ v4l2_std_id ;
struct file {int dummy; } ;
struct dvb_usb_device {struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {scalar_t__ input; int /*<<< orphan*/  cx25840; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS ; 
 scalar_t__ V4L2_STD_ALL ; 
 scalar_t__ V4L2_STD_PAL ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 int /*<<< orphan*/  querystd ; 
 int v4l2_subdev_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  video ; 
 struct dvb_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int cxusb_medion_querystd(struct file *file, void *fh,
				 v4l2_std_id *norm)
{
	struct dvb_usb_device *dvbdev = video_drvdata(file);
	struct cxusb_medion_dev *cxdev = dvbdev->priv;
	v4l2_std_id norm_mask;
	int ret;

	/*
	 * make sure we don't have improper std bits set for the TV tuner
	 * (could happen when no signal was present yet after reset)
	 */
	if (cxdev->input == 0)
		norm_mask = V4L2_STD_PAL;
	else
		norm_mask = V4L2_STD_ALL;

	ret = v4l2_subdev_call(cxdev->cx25840, video, querystd, norm);
	if (ret != 0) {
		cxusb_vprintk(dvbdev, OPS,
			      "cannot get detected standard for input %u\n",
			      (unsigned int)cxdev->input);
		return ret;
	}

	cxusb_vprintk(dvbdev, OPS, "input %u detected standard is %lx\n",
		      (unsigned int)cxdev->input, (unsigned long)*norm);
	*norm &= norm_mask;

	return 0;
}