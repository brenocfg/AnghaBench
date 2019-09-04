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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mchip_dev; } ;

/* Variables and functions */
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 TYPE_1__ meye ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void *fh,
				struct v4l2_capability *cap)
{
	strcpy(cap->driver, "meye");
	strcpy(cap->card, "meye");
	sprintf(cap->bus_info, "PCI:%s", pci_name(meye.mchip_dev));

	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE |
			    V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;

	return 0;
}