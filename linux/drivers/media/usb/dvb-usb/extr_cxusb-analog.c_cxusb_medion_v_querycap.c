#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct dvb_usb_device {TYPE_3__* udev; } ;
struct TYPE_5__ {TYPE_1__* driver; } ;
struct TYPE_6__ {TYPE_2__ dev; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int radiocaps ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct dvb_usb_device* video_drvdata (struct file*) ; 
 int videocaps ; 

__attribute__((used)) static int cxusb_medion_v_querycap(struct file *file, void *fh,
				   struct v4l2_capability *cap)
{
	struct dvb_usb_device *dvbdev = video_drvdata(file);

	strscpy(cap->driver, dvbdev->udev->dev.driver->name,
		sizeof(cap->driver));
	strscpy(cap->card, "Medion 95700", sizeof(cap->card));
	usb_make_path(dvbdev->udev, cap->bus_info, sizeof(cap->bus_info));

	cap->capabilities = videocaps | radiocaps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}