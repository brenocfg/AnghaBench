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
struct uart_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;
struct lpss8250 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_ALL_TYPES ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  qrk_serial_setup_dma (struct lpss8250*,struct uart_port*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qrk_serial_setup(struct lpss8250 *lpss, struct uart_port *port)
{
	struct pci_dev *pdev = to_pci_dev(port->dev);
	int ret;

	pci_set_master(pdev);

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	if (ret < 0)
		return ret;

	port->irq = pci_irq_vector(pdev, 0);

	qrk_serial_setup_dma(lpss, port);
	return 0;
}