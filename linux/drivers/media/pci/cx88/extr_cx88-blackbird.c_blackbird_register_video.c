#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int device_caps; int /*<<< orphan*/ * queue; int /*<<< orphan*/ * ctrl_handler; } ;
struct TYPE_8__ {int /*<<< orphan*/  hdl; } ;
struct cx8802_dev {TYPE_3__ mpeg_dev; TYPE_6__* core; int /*<<< orphan*/  vb2_mpegq; TYPE_1__ cxhdl; int /*<<< orphan*/  pci; } ;
struct TYPE_9__ {scalar_t__ tuner_type; } ;
struct TYPE_11__ {TYPE_2__ board; } ;

/* Variables and functions */
 scalar_t__ UNSET ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  cx8802_mpeg_template ; 
 int /*<<< orphan*/  cx88_vdev_init (TYPE_6__*,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_3__*) ; 
 int video_register_device (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_3__*,struct cx8802_dev*) ; 

__attribute__((used)) static int blackbird_register_video(struct cx8802_dev *dev)
{
	int err;

	cx88_vdev_init(dev->core, dev->pci, &dev->mpeg_dev,
		       &cx8802_mpeg_template, "mpeg");
	dev->mpeg_dev.ctrl_handler = &dev->cxhdl.hdl;
	video_set_drvdata(&dev->mpeg_dev, dev);
	dev->mpeg_dev.queue = &dev->vb2_mpegq;
	dev->mpeg_dev.device_caps = V4L2_CAP_READWRITE | V4L2_CAP_STREAMING |
				    V4L2_CAP_VIDEO_CAPTURE;
	if (dev->core->board.tuner_type != UNSET)
		dev->mpeg_dev.device_caps |= V4L2_CAP_TUNER;
	err = video_register_device(&dev->mpeg_dev, VFL_TYPE_GRABBER, -1);
	if (err < 0) {
		pr_info("can't register mpeg device\n");
		return err;
	}
	pr_info("registered device %s [mpeg]\n",
		video_device_node_name(&dev->mpeg_dev));
	return 0;
}