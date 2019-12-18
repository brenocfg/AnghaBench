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
struct pcie_port {int dummy; } ;
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 unsigned int MAX_MSI_IRQS_PER_CTRL ; 
 unsigned int MSI_REG_CTRL_BLOCK_SIZE ; 
 scalar_t__ PCIE_MSI_INTR0_STATUS ; 
 int /*<<< orphan*/  dw_pcie_wr_own_conf (struct pcie_port*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct pcie_port* irq_data_get_irq_chip_data (struct irq_data*) ; 

__attribute__((used)) static void dw_pci_bottom_ack(struct irq_data *d)
{
	struct pcie_port *pp  = irq_data_get_irq_chip_data(d);
	unsigned int res, bit, ctrl;

	ctrl = d->hwirq / MAX_MSI_IRQS_PER_CTRL;
	res = ctrl * MSI_REG_CTRL_BLOCK_SIZE;
	bit = d->hwirq % MAX_MSI_IRQS_PER_CTRL;

	dw_pcie_wr_own_conf(pp, PCIE_MSI_INTR0_STATUS + res, 4, BIT(bit));
}