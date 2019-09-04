#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ngpio; } ;
struct thunderx_gpio {int /*<<< orphan*/  irqd; TYPE_2__* msix_entries; TYPE_1__ chip; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_pop_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct thunderx_gpio* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thunderx_gpio_remove(struct pci_dev *pdev)
{
	int i;
	struct thunderx_gpio *txgpio = pci_get_drvdata(pdev);

	for (i = 0; i < txgpio->chip.ngpio; i++)
		irq_domain_pop_irq(txgpio->irqd,
				   txgpio->msix_entries[i].vector);

	irq_domain_remove(txgpio->irqd);

	pci_set_drvdata(pdev, NULL);
}