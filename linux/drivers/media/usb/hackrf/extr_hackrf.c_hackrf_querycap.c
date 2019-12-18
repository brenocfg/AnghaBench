#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct hackrf_dev {int /*<<< orphan*/  udev; TYPE_1__ rx_vdev; struct usb_interface* intf; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KBUILD_MODNAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_MODULATOR ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_SDR_CAPTURE ; 
 int V4L2_CAP_SDR_OUTPUT ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct hackrf_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int hackrf_querycap(struct file *file, void *fh,
		struct v4l2_capability *cap)
{
	struct hackrf_dev *dev = video_drvdata(file);
	struct usb_interface *intf = dev->intf;

	dev_dbg(&intf->dev, "\n");

	cap->capabilities = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER |
			    V4L2_CAP_SDR_OUTPUT | V4L2_CAP_MODULATOR |
			    V4L2_CAP_STREAMING | V4L2_CAP_READWRITE |
			    V4L2_CAP_DEVICE_CAPS;
	strscpy(cap->driver, KBUILD_MODNAME, sizeof(cap->driver));
	strscpy(cap->card, dev->rx_vdev.name, sizeof(cap->card));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));

	return 0;
}