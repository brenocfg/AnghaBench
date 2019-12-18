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
struct rcar_msi {int /*<<< orphan*/  used; int /*<<< orphan*/  domain; } ;
struct rcar_pcie {struct device* dev; struct rcar_msi msi; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  PCIEMSIFR ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 unsigned int find_first_bit (unsigned long*,int) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned long rcar_pci_read_reg (struct rcar_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcar_pci_write_reg (struct rcar_pcie*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t rcar_pcie_msi_irq(int irq, void *data)
{
	struct rcar_pcie *pcie = data;
	struct rcar_msi *msi = &pcie->msi;
	struct device *dev = pcie->dev;
	unsigned long reg;

	reg = rcar_pci_read_reg(pcie, PCIEMSIFR);

	/* MSI & INTx share an interrupt - we only handle MSI here */
	if (!reg)
		return IRQ_NONE;

	while (reg) {
		unsigned int index = find_first_bit(&reg, 32);
		unsigned int msi_irq;

		/* clear the interrupt */
		rcar_pci_write_reg(pcie, 1 << index, PCIEMSIFR);

		msi_irq = irq_find_mapping(msi->domain, index);
		if (msi_irq) {
			if (test_bit(index, msi->used))
				generic_handle_irq(msi_irq);
			else
				dev_info(dev, "unhandled MSI\n");
		} else {
			/* Unknown MSI, just clear it */
			dev_dbg(dev, "unexpected MSI\n");
		}

		/* see if there's any more pending in this vector */
		reg = rcar_pci_read_reg(pcie, PCIEMSIFR);
	}

	return IRQ_HANDLED;
}