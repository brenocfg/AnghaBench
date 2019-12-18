#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  handle_irq; int /*<<< orphan*/  membase; void* irq; int /*<<< orphan*/  dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hsu_dma_chip {int /*<<< orphan*/  offset; int /*<<< orphan*/  length; int /*<<< orphan*/  regs; void* irq; int /*<<< orphan*/ * dev; } ;
struct mid8250 {struct pci_dev* dma_dev; TYPE_1__* board; struct hsu_dma_chip dma_chip; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNV_DMA_CHAN_OFFSET ; 
 unsigned int FL_GET_BASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_IRQ_ALL_TYPES ; 
 int /*<<< orphan*/  dnv_handle_irq ; 
 int hsu_dma_probe (struct hsu_dma_chip*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 void* pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (struct pci_dev*,unsigned int) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dnv_setup(struct mid8250 *mid, struct uart_port *p)
{
	struct hsu_dma_chip *chip = &mid->dma_chip;
	struct pci_dev *pdev = to_pci_dev(p->dev);
	unsigned int bar = FL_GET_BASE(mid->board->flags);
	int ret;

	pci_set_master(pdev);

	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_ALL_TYPES);
	if (ret < 0)
		return ret;

	p->irq = pci_irq_vector(pdev, 0);

	chip->dev = &pdev->dev;
	chip->irq = pci_irq_vector(pdev, 0);
	chip->regs = p->membase;
	chip->length = pci_resource_len(pdev, bar);
	chip->offset = DNV_DMA_CHAN_OFFSET;

	/* Falling back to PIO mode if DMA probing fails */
	ret = hsu_dma_probe(chip);
	if (ret)
		return 0;

	mid->dma_dev = pdev;

	p->handle_irq = dnv_handle_irq;
	return 0;
}