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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct cx25821_dev {size_t board; int /*<<< orphan*/  pci; } ;
struct cx25821_channel {scalar_t__ id; struct cx25821_dev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int const V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 scalar_t__ VID_CHANNEL_NUM ; 
 TYPE_1__* cx25821_boards ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cx25821_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int cx25821_vidioc_querycap(struct file *file, void *priv,
			    struct v4l2_capability *cap)
{
	struct cx25821_channel *chan = video_drvdata(file);
	struct cx25821_dev *dev = chan->dev;
	const u32 cap_input = V4L2_CAP_VIDEO_CAPTURE |
			V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	const u32 cap_output = V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_READWRITE;

	strcpy(cap->driver, "cx25821");
	strlcpy(cap->card, cx25821_boards[dev->board].name, sizeof(cap->card));
	sprintf(cap->bus_info, "PCIe:%s", pci_name(dev->pci));
	if (chan->id >= VID_CHANNEL_NUM)
		cap->device_caps = cap_output;
	else
		cap->device_caps = cap_input;
	cap->capabilities = cap_input | cap_output | V4L2_CAP_DEVICE_CAPS;
	return 0;
}