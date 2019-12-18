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
struct pci_dev {int dummy; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*) ; 
 int /*<<< orphan*/  hfi1_init (struct hfi1_devdata*,int) ; 
 struct hfi1_devdata* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void
pci_resume(struct pci_dev *pdev)
{
	struct hfi1_devdata *dd = pci_get_drvdata(pdev);

	dd_dev_info(dd, "HFI1 resume function called\n");
	/*
	 * Running jobs will fail, since it's asynchronous
	 * unlike sysfs-requested reset.   Better than
	 * doing nothing.
	 */
	hfi1_init(dd, 1); /* same as re-init after reset */
}