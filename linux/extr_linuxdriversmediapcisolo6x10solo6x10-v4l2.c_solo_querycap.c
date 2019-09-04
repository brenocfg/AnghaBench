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
struct v4l2_capability {int device_caps; int capabilities; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct solo_dev {int /*<<< orphan*/  pdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 char* SOLO6X10_NAME ; 
 int V4L2_CAP_DEVICE_CAPS ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 struct solo_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_querycap(struct file *file, void  *priv,
			 struct v4l2_capability *cap)
{
	struct solo_dev *solo_dev = video_drvdata(file);

	strcpy(cap->driver, SOLO6X10_NAME);
	strcpy(cap->card, "Softlogic 6x10");
	snprintf(cap->bus_info, sizeof(cap->bus_info), "PCI:%s",
		 pci_name(solo_dev->pdev));
	cap->device_caps = V4L2_CAP_VIDEO_CAPTURE |
			V4L2_CAP_READWRITE | V4L2_CAP_STREAMING;
	cap->capabilities = cap->device_caps | V4L2_CAP_DEVICE_CAPS;
	return 0;
}