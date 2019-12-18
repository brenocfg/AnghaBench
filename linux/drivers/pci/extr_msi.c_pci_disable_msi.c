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
struct pci_dev {int /*<<< orphan*/  msi_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_msi_irqs (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_msi_enable ; 
 int /*<<< orphan*/  pci_msi_shutdown (struct pci_dev*) ; 

void pci_disable_msi(struct pci_dev *dev)
{
	if (!pci_msi_enable || !dev || !dev->msi_enabled)
		return;

	pci_msi_shutdown(dev);
	free_msi_irqs(dev);
}