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
 struct hfi1_devdata* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  shutdown_device (struct hfi1_devdata*) ; 

__attribute__((used)) static void shutdown_one(struct pci_dev *pdev)
{
	struct hfi1_devdata *dd = pci_get_drvdata(pdev);

	shutdown_device(dd);
}