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
struct pci_dev {int /*<<< orphan*/  current_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  isp_set_power (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int isp_pci_resume(struct device *dev)
{
	struct pci_dev *pdev = to_pci_dev(dev);

	isp_set_power(pdev, true);
	pdev->current_state = PCI_D0;
	pci_restore_state(pdev);

	return 0;
}