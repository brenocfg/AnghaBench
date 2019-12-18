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
struct pci_dev {scalar_t__ devfn; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct pci_dev *cdns3_get_second_fun(struct pci_dev *pdev)
{
	struct pci_dev *func;

	/*
	 * Gets the second function.
	 * It's little tricky, but this platform has two function.
	 * The fist keeps resources for Host/Device while the second
	 * keeps resources for DRD/OTG.
	 */
	func = pci_get_device(pdev->vendor, pdev->device, NULL);
	if (unlikely(!func))
		return NULL;

	if (func->devfn == pdev->devfn) {
		func = pci_get_device(pdev->vendor, pdev->device, func);
		if (unlikely(!func))
			return NULL;
	}

	return func;
}