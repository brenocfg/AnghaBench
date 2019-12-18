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
struct video_device {int /*<<< orphan*/  queue; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPS ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vb2_queue_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 struct dvb_usb_device* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static void cxusb_medion_videodev_release(struct video_device *vdev)
{
	struct dvb_usb_device *dvbdev = video_get_drvdata(vdev);

	cxusb_vprintk(dvbdev, OPS, "video device release\n");

	vb2_queue_release(vdev->queue);

	video_device_release(vdev);
}