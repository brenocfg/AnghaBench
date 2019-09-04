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
typedef  int u32 ;
struct video_device {int vfl_type; } ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct saa7134_dev {unsigned int tuner_type; size_t board; scalar_t__ has_rds; int /*<<< orphan*/  pci; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TUNER_ABSENT ; 
 unsigned int UNSET ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_RDS_CAPTURE ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int V4L2_CAP_VIDEO_OVERLAY ; 
#define  VFL_TYPE_GRABBER 130 
#define  VFL_TYPE_RADIO 129 
#define  VFL_TYPE_VBI 128 
 int /*<<< orphan*/  is_empress (struct file*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* saa7134_boards ; 
 scalar_t__ saa7134_no_overlay ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_device* video_devdata (struct file*) ; 
 struct saa7134_dev* video_drvdata (struct file*) ; 

int saa7134_querycap(struct file *file, void *priv,
					struct v4l2_capability *cap)
{
	struct saa7134_dev *dev = video_drvdata(file);
	struct video_device *vdev = video_devdata(file);
	u32 radio_caps, video_caps, vbi_caps;

	unsigned int tuner_type = dev->tuner_type;

	strcpy(cap->driver, "saa7134");
	strlcpy(cap->card, saa7134_boards[dev->board].name,
		sizeof(cap->card));
	sprintf(cap->bus_info, "PCI:%s", pci_name(dev->pci));

	cap->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	if ((tuner_type != TUNER_ABSENT) && (tuner_type != UNSET))
		cap->device_caps |= V4L2_CAP_TUNER;

	radio_caps = V4L2_CAP_RADIO;
	if (dev->has_rds)
		radio_caps |= V4L2_CAP_RDS_CAPTURE;

	video_caps = V4L2_CAP_VIDEO_CAPTURE;
	if (saa7134_no_overlay <= 0 && !is_empress(file))
		video_caps |= V4L2_CAP_VIDEO_OVERLAY;

	vbi_caps = V4L2_CAP_VBI_CAPTURE;

	switch (vdev->vfl_type) {
	case VFL_TYPE_RADIO:
		cap->device_caps |= radio_caps;
		break;
	case VFL_TYPE_GRABBER:
		cap->device_caps |= video_caps;
		break;
	case VFL_TYPE_VBI:
		cap->device_caps |= vbi_caps;
		break;
	default:
		return -EINVAL;
	}
	cap->capabilities = radio_caps | video_caps | vbi_caps |
		cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	if (vdev->vfl_type == VFL_TYPE_RADIO) {
		cap->device_caps &= ~V4L2_CAP_STREAMING;
		if (!dev->has_rds)
			cap->device_caps &= ~V4L2_CAP_READWRITE;
	}

	return 0;
}