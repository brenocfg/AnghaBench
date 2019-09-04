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
struct video_device {scalar_t__ vfl_type; } ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct usb_usbvision {size_t dev_model; scalar_t__ have_tuner; int /*<<< orphan*/  dev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {char* model_string; scalar_t__ radio; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* usbvision_device_data ; 
 struct video_device* video_devdata (struct file*) ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *vc)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);

	strlcpy(vc->driver, "USBVision", sizeof(vc->driver));
	strlcpy(vc->card,
		usbvision_device_data[usbvision->dev_model].model_string,
		sizeof(vc->card));
	usb_make_path(usbvision->dev, vc->bus_info, sizeof(vc->bus_info));
	vc->device_caps = usbvision->have_tuner ? V4L2_CAP_TUNER : 0;
	if (vdev->vfl_type == VFL_TYPE_GRABBER)
		vc->device_caps |= V4L2_CAP_VIDEO_CAPTURE |
			V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	else
		vc->device_caps |= V4L2_CAP_RADIO;

	vc->capabilities = vc->device_caps | V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_READWRITE | V4L2_CAP_STREAMING | V4L2_CAP_DEVICE_CAPS;
	if (usbvision_device_data[usbvision->dev_model].radio)
		vc->capabilities |= V4L2_CAP_RADIO;
	return 0;
}