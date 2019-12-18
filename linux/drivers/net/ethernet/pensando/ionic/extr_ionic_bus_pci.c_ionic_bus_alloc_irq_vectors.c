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
struct ionic {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

int ionic_bus_alloc_irq_vectors(struct ionic *ionic, unsigned int nintrs)
{
	return pci_alloc_irq_vectors(ionic->pdev, nintrs, nintrs,
				     PCI_IRQ_MSIX);
}