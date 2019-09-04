#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * queue; int /*<<< orphan*/ * ctrl_handler; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdl; } ;
struct cx8802_dev {TYPE_2__ mpeg_dev; int /*<<< orphan*/  vb2_mpegq; TYPE_1__ cxhdl; int /*<<< orphan*/  pci; int /*<<< orphan*/  core; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFL_TYPE_GRABBER ; 
 int /*<<< orphan*/  cx8802_mpeg_template ; 
 int /*<<< orphan*/  cx88_vdev_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int /*<<< orphan*/  video_device_node_name (TYPE_2__*) ; 
 int video_register_device (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_2__*,struct cx8802_dev*) ; 

__attribute__((used)) static int blackbird_register_video(struct cx8802_dev *dev)
{
	int err;

	cx88_vdev_init(dev->core, dev->pci, &dev->mpeg_dev,
		       &cx8802_mpeg_template, "mpeg");
	dev->mpeg_dev.ctrl_handler = &dev->cxhdl.hdl;
	video_set_drvdata(&dev->mpeg_dev, dev);
	dev->mpeg_dev.queue = &dev->vb2_mpegq;
	err = video_register_device(&dev->mpeg_dev, VFL_TYPE_GRABBER, -1);
	if (err < 0) {
		pr_info("can't register mpeg device\n");
		return err;
	}
	pr_info("registered device %s [mpeg]\n",
		video_device_node_name(&dev->mpeg_dev));
	return 0;
}