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
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/ * xcv ; 

__attribute__((used)) static void xcv_remove(struct pci_dev *pdev)
{
	struct device *dev = &pdev->dev;

	if (xcv) {
		devm_kfree(dev, xcv);
		xcv = NULL;
	}

	pci_release_regions(pdev);
	pci_disable_device(pdev);
}