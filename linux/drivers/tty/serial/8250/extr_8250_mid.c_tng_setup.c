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
struct uart_port {int /*<<< orphan*/  handle_irq; int /*<<< orphan*/  dev; } ;
struct pci_dev {int /*<<< orphan*/  bus; int /*<<< orphan*/  devfn; } ;
struct mid8250 {int dma_index; int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_DEVFN (int,int /*<<< orphan*/ ) ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tng_handle_irq ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tng_setup(struct mid8250 *mid, struct uart_port *p)
{
	struct pci_dev *pdev = to_pci_dev(p->dev);
	int index = PCI_FUNC(pdev->devfn);

	/*
	 * Device 0000:00:04.0 is not a real HSU port. It provides a global
	 * register set for all HSU ports, although it has the same PCI ID.
	 * Skip it here.
	 */
	if (index-- == 0)
		return -ENODEV;

	mid->dma_index = index;
	mid->dma_dev = pci_get_slot(pdev->bus, PCI_DEVFN(5, 0));

	p->handle_irq = tng_handle_irq;
	return 0;
}