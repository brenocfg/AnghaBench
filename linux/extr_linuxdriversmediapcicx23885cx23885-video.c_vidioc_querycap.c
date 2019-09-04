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
struct file {int dummy; } ;
struct cx23885_dev {size_t board; scalar_t__ tuner_type; int /*<<< orphan*/  pci; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ TUNER_ABSENT ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 scalar_t__ VFL_TYPE_VBI ; 
 TYPE_1__* cx23885_boards ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct cx23885_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
	struct v4l2_capability *cap)
{
	struct cx23885_dev *dev = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);

	strcpy(cap->driver, "cx23885");
	strlcpy(cap->card, cx23885_boards[dev->board].name,
		sizeof(cap->card));
	sprintf(cap->bus_info, "PCIe:%s", pci_name(dev->pci));
	cap->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING | V4L2_CAP_AUDIO;
	if (dev->tuner_type != TUNER_ABSENT)
		cap->device_caps |= V4L2_CAP_TUNER;
	if (vdev->vfl_type == VFL_TYPE_VBI)
		cap->device_caps |= V4L2_CAP_VBI_CAPTURE;
	else
		cap->device_caps |= V4L2_CAP_VIDEO_CAPTURE;
	cap->capabilities = cap->device_caps | V4L2_CAP_VBI_CAPTURE |
		V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_DEVICE_CAPS;
	return 0;
}