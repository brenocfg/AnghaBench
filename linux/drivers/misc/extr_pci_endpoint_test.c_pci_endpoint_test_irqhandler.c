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
typedef  int u32 ;
struct pci_endpoint_test {int last_irq; int /*<<< orphan*/  irq_raised; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PCI_ENDPOINT_TEST_STATUS ; 
 int STATUS_IRQ_RAISED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int pci_endpoint_test_readl (struct pci_endpoint_test*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_endpoint_test_writel (struct pci_endpoint_test*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t pci_endpoint_test_irqhandler(int irq, void *dev_id)
{
	struct pci_endpoint_test *test = dev_id;
	u32 reg;

	reg = pci_endpoint_test_readl(test, PCI_ENDPOINT_TEST_STATUS);
	if (reg & STATUS_IRQ_RAISED) {
		test->last_irq = irq;
		complete(&test->irq_raised);
		reg &= ~STATUS_IRQ_RAISED;
	}
	pci_endpoint_test_writel(test, PCI_ENDPOINT_TEST_STATUS,
				 reg);

	return IRQ_HANDLED;
}