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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct cio2_device {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIO2_DEVICE_NAME ; 
 int /*<<< orphan*/  CIO2_NAME ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cio2_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int cio2_v4l2_querycap(struct file *file, void *fh,
			      struct v4l2_capability *cap)
{
	struct cio2_device *cio2 = video_drvdata(file);

	strscpy(cap->driver, CIO2_NAME, sizeof(cap->driver));
	strscpy(cap->card, CIO2_DEVICE_NAME, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "PCI:%s", pci_name(cio2->pci_dev));

	return 0;
}