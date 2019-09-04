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
struct video_device {int /*<<< orphan*/  name; int /*<<< orphan*/ * lock; int /*<<< orphan*/  release; int /*<<< orphan*/ * dev_parent; int /*<<< orphan*/ * v4l2_dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {char* name; } ;
struct cx88_core {char* name; TYPE_1__ board; int /*<<< orphan*/  lock; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char const*,char*) ; 
 int /*<<< orphan*/  video_device_release_empty ; 

void cx88_vdev_init(struct cx88_core *core,
		    struct pci_dev *pci,
		    struct video_device *vfd,
		    const struct video_device *template_,
		    const char *type)
{
	*vfd = *template_;

	/*
	 * The dev pointer of v4l2_device is NULL, instead we set the
	 * video_device dev_parent pointer to the correct PCI bus device.
	 * This driver is a rare example where there is one v4l2_device,
	 * but the video nodes have different parent (PCI) devices.
	 */
	vfd->v4l2_dev = &core->v4l2_dev;
	vfd->dev_parent = &pci->dev;
	vfd->release = video_device_release_empty;
	vfd->lock = &core->lock;
	snprintf(vfd->name, sizeof(vfd->name), "%s %s (%s)",
		 core->name, type, core->board.name);
}