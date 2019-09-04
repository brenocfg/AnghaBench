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
struct sp_device {int /*<<< orphan*/  psp_irq; int /*<<< orphan*/  ccp_irq; struct device* dev; } ;
struct pci_dev {int /*<<< orphan*/  irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int pci_enable_msi (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static int sp_get_msi_irq(struct sp_device *sp)
{
	struct device *dev = sp->dev;
	struct pci_dev *pdev = to_pci_dev(dev);
	int ret;

	ret = pci_enable_msi(pdev);
	if (ret)
		return ret;

	sp->ccp_irq = pdev->irq;
	sp->psp_irq = pdev->irq;

	return 0;
}