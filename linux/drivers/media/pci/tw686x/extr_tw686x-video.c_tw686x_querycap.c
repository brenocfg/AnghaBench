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
struct tw686x_video_channel {struct tw686x_dev* dev; } ;
struct tw686x_dev {char* name; int /*<<< orphan*/  pci_dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct tw686x_video_channel* video_drvdata (struct file*) ; 

__attribute__((used)) static int tw686x_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	struct tw686x_video_channel *vc = video_drvdata(file);
	struct tw686x_dev *dev = vc->dev;

	strscpy(cap->driver, "tw686x", sizeof(cap->driver));
	strscpy(cap->card, dev->name, sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
		 "PCI:%s", pci_name(dev->pci_dev));
	return 0;
}