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
struct sp_pci {scalar_t__ msix_count; } ;
struct sp_device {scalar_t__ psp_irq; scalar_t__ ccp_irq; struct device* dev; struct sp_pci* dev_specific; } ;
struct pci_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static void sp_free_irqs(struct sp_device *sp)
{
	struct sp_pci *sp_pci = sp->dev_specific;
	struct device *dev = sp->dev;
	struct pci_dev *pdev = to_pci_dev(dev);

	if (sp_pci->msix_count)
		pci_disable_msix(pdev);
	else if (sp->psp_irq)
		pci_disable_msi(pdev);

	sp->ccp_irq = 0;
	sp->psp_irq = 0;
}