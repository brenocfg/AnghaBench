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

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_ats (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pasid (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pri (struct pci_dev*) ; 

__attribute__((used)) static void pdev_iommuv2_disable(struct pci_dev *pdev)
{
	pci_disable_ats(pdev);
	pci_disable_pri(pdev);
	pci_disable_pasid(pdev);
}