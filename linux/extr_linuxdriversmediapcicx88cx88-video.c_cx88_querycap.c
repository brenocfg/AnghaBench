#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct video_device {int vfl_type; } ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  card; } ;
struct file {int dummy; } ;
struct TYPE_3__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ tuner_type; TYPE_1__ radio; int /*<<< orphan*/  name; } ;
struct cx88_core {TYPE_2__ board; } ;

/* Variables and functions */
 scalar_t__ CX88_RADIO ; 
 int EINVAL ; 
 scalar_t__ UNSET ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_RADIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
#define  VFL_TYPE_GRABBER 130 
#define  VFL_TYPE_RADIO 129 
#define  VFL_TYPE_VBI 128 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_device* video_devdata (struct file*) ; 

int cx88_querycap(struct file *file, struct cx88_core *core,
		  struct v4l2_capability *cap)
{
	struct video_device *vdev = video_devdata(file);

	strlcpy(cap->card, core->board.name, sizeof(cap->card));
	cap->device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	if (core->board.tuner_type != UNSET)
		cap->device_caps |= V4L2_CAP_TUNER;
	switch (vdev->vfl_type) {
	case VFL_TYPE_RADIO:
		cap->device_caps = V4L2_CAP_RADIO | V4L2_CAP_TUNER;
		break;
	case VFL_TYPE_GRABBER:
		cap->device_caps |= V4L2_CAP_VIDEO_CAPTURE;
		break;
	case VFL_TYPE_VBI:
		cap->device_caps |= V4L2_CAP_VBI_CAPTURE;
		break;
	default:
		return -EINVAL;
	}
	cap->capabilities = cap->device_caps | V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_VBI_CAPTURE | V4L2_CAP_DEVICE_CAPS;
	if (core->board.radio.type == CX88_RADIO)
		cap->capabilities |= V4L2_CAP_RADIO;
	return 0;
}