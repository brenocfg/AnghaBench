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
struct video_device {scalar_t__ vfl_dir; } ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
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
 scalar_t__ VFL_DIR_RX ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct hackrf_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int hackrf_querycap(struct file *file, void *fh,
		struct v4l2_capability *cap)
{
	struct hackrf_dev *dev = video_drvdata(file);
	struct usb_interface *intf = dev->intf;
	struct video_device *vdev = video_devdata(file);

	dev_dbg(&intf->dev, "\n");

	cap->device_caps = V4L2_CAP_STREAMING | V4L2_CAP_READWRITE;
	if (vdev->vfl_dir == VFL_DIR_RX)
		cap->device_caps |= V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER;
	else
		cap->device_caps |= V4L2_CAP_SDR_OUTPUT | V4L2_CAP_MODULATOR;

	cap->capabilities = V4L2_CAP_SDR_CAPTURE | V4L2_CAP_TUNER |
			    V4L2_CAP_SDR_OUTPUT | V4L2_CAP_MODULATOR |
			    V4L2_CAP_DEVICE_CAPS | cap->device_caps;
	strlcpy(cap->driver, KBUILD_MODNAME, sizeof(cap->driver));
	strlcpy(cap->card, dev->rx_vdev.name, sizeof(cap->card));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));

	return 0;
}