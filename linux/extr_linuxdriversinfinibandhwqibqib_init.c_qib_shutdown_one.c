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
struct qib_devdata {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 struct qib_devdata* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qib_shutdown_device (struct qib_devdata*) ; 

__attribute__((used)) static void qib_shutdown_one(struct pci_dev *pdev)
{
	struct qib_devdata *dd = pci_get_drvdata(pdev);

	qib_shutdown_device(dd);
}