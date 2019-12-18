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
struct solo_dev {int /*<<< orphan*/  pdev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 char* SOLO6X10_NAME ; 
 char* pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct solo_dev* video_drvdata (struct file*) ; 

__attribute__((used)) static int solo_querycap(struct file *file, void  *priv,
			 struct v4l2_capability *cap)
{
	struct solo_dev *solo_dev = video_drvdata(file);

	strscpy(cap->driver, SOLO6X10_NAME, sizeof(cap->driver));
	strscpy(cap->card, "Softlogic 6x10", sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info), "PCI:%s",
		 pci_name(solo_dev->pdev));
	return 0;
}