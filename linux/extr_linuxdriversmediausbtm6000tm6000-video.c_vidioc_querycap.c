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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct tm6000_fh {struct tm6000_core* dev; } ;
struct tm6000_core {scalar_t__ tuner_type; int /*<<< orphan*/  udev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 scalar_t__ TUNER_ABSENT ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 scalar_t__ VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  usb_make_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_device* video_devdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *cap)
{
	struct tm6000_core *dev = ((struct tm6000_fh *)priv)->dev;
	struct video_device *vdev = video_devdata(file);

	strlcpy(cap->driver, "tm6000", sizeof(cap->driver));
	strlcpy(cap->card, "Trident TVMaster TM5600/6000/6010", sizeof(cap->card));
	usb_make_path(dev->udev, cap->bus_info, sizeof(cap->bus_info));
	if (dev->tuner_type != TUNER_ABSENT)
		cap->device_caps |= V4L2_CAP_TUNER;
	if (vdev->vfl_type == VFL_TYPE_GRABBER)
		cap->device_caps |= V4L2_CAP_VIDEO_CAPTURE |
				V4L2_CAP_STREAMING |
				V4L2_CAP_READWRITE;
	else
		cap->device_caps |= V4L2_CAP_RADIO;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS |
		V4L2_CAP_RADIO | V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE;

	return 0;
}