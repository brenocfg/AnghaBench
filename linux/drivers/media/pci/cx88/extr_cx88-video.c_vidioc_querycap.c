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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct cx88_core {int dummy; } ;
struct cx8800_dev {int /*<<< orphan*/  pci; struct cx88_core* core; } ;

/* Variables and functions */
 int cx88_querycap (struct file*,struct cx88_core*,struct v4l2_capability*) ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct cx8800_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
			   struct v4l2_capability *cap)
{
	struct cx8800_dev *dev = video_drvdata(file);
	struct cx88_core *core = dev->core;

	strscpy(cap->driver, "cx8800", sizeof(cap->driver));
	sprintf(cap->bus_info, "PCI:%s", pci_name(dev->pci));
	return cx88_querycap(file, core, cap);
}