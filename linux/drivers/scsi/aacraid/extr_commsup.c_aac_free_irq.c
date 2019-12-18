#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct aac_dev {int max_msix; TYPE_1__* pdev; scalar_t__ msi; struct aac_dev* aac_msix; } ;
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 scalar_t__ aac_is_src (struct aac_dev*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct aac_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int) ; 

void aac_free_irq(struct aac_dev *dev)
{
	int i;

	if (aac_is_src(dev)) {
		if (dev->max_msix > 1) {
			for (i = 0; i < dev->max_msix; i++)
				free_irq(pci_irq_vector(dev->pdev, i),
					 &(dev->aac_msix[i]));
		} else {
			free_irq(dev->pdev->irq, &(dev->aac_msix[0]));
		}
	} else {
		free_irq(dev->pdev->irq, dev);
	}
	if (dev->msi)
		pci_disable_msi(dev->pdev);
	else if (dev->max_msix > 1)
		pci_disable_msix(dev->pdev);
}