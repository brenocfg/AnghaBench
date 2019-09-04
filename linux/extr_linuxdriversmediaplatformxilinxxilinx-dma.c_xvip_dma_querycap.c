#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; } ;
struct TYPE_6__ {scalar_t__ type; } ;
struct xvip_dma {int port; TYPE_5__* xdev; TYPE_2__ video; TYPE_1__ queue; } ;
struct v4l2_fh {int /*<<< orphan*/  vdev; } ;
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {struct v4l2_fh* private_data; } ;
struct TYPE_10__ {int v4l2_caps; TYPE_4__* dev; } ;
struct TYPE_9__ {TYPE_3__* of_node; } ;
struct TYPE_8__ {char* name; } ;

/* Variables and functions */
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int V4L2_CAP_VIDEO_OUTPUT ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct xvip_dma* to_xvip_dma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xvip_dma_querycap(struct file *file, void *fh, struct v4l2_capability *cap)
{
	struct v4l2_fh *vfh = file->private_data;
	struct xvip_dma *dma = to_xvip_dma(vfh->vdev);

	cap->device_caps = V4L2_CAP_STREAMING;

	if (dma->queue.type == V4L2_BUF_TYPE_VIDEO_CAPTURE)
		cap->device_caps |= V4L2_CAP_VIDEO_CAPTURE;
	else
		cap->device_caps |= V4L2_CAP_VIDEO_OUTPUT;

	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS
			  | dma->xdev->v4l2_caps;

	strlcpy(cap->driver, "xilinx-vipp", sizeof(cap->driver));
	strlcpy(cap->card, dma->video.name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "platform:%s:%u",
		 dma->xdev->dev->of_node->name, dma->port);

	return 0;
}