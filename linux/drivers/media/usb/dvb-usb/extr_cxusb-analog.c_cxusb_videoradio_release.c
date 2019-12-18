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
struct file {int dummy; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  cxusb_medion_put (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*) ; 
 int v4l2_fh_release (struct file*) ; 
 int vb2_fop_release (struct file*) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct dvb_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int cxusb_videoradio_release(struct file *f)
{
	struct video_device *vdev = video_devdata(f);
	struct dvb_usb_device *dvbdev = video_drvdata(f);
	int ret;

	cxusb_vprintk(dvbdev, OPS, "got release\n");

	if (vdev->vfl_type == VFL_TYPE_GRABBER)
		ret = vb2_fop_release(f);
	else
		ret = v4l2_fh_release(f);

	cxusb_medion_put(dvbdev);

	return ret;
}