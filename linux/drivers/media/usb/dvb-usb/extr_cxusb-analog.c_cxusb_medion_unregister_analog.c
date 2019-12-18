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
struct dvb_usb_device {struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {int /*<<< orphan*/  v4l2_release; int /*<<< orphan*/  v4l2dev; int /*<<< orphan*/  videodev; int /*<<< orphan*/  radiodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  v4l2_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

void cxusb_medion_unregister_analog(struct dvb_usb_device *dvbdev)
{
	struct cxusb_medion_dev *cxdev = dvbdev->priv;

	cxusb_vprintk(dvbdev, OPS, "unregistering analog\n");

	video_unregister_device(cxdev->radiodev);
	video_unregister_device(cxdev->videodev);

	v4l2_device_put(&cxdev->v4l2dev);
	wait_for_completion(&cxdev->v4l2_release);

	cxusb_vprintk(dvbdev, OPS, "analog unregistered\n");
}