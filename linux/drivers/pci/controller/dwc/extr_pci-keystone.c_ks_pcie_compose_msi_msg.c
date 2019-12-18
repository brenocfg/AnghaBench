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
typedef  scalar_t__ u64 ;
struct pcie_port {int dummy; } ;
struct msi_msg {int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ start; } ;
struct keystone_pcie {TYPE_1__ app; } ;
struct irq_data {scalar_t__ hwirq; } ;
struct dw_pcie {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ MSI_IRQ ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcie_port* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 
 struct keystone_pcie* to_keystone_pcie (struct dw_pcie*) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static void ks_pcie_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct pcie_port *pp = irq_data_get_irq_chip_data(data);
	struct keystone_pcie *ks_pcie;
	struct dw_pcie *pci;
	u64 msi_target;

	pci = to_dw_pcie_from_pp(pp);
	ks_pcie = to_keystone_pcie(pci);

	msi_target = ks_pcie->app.start + MSI_IRQ;
	msg->address_lo = lower_32_bits(msi_target);
	msg->address_hi = upper_32_bits(msi_target);
	msg->data = data->hwirq;

	dev_dbg(pci->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(int)data->hwirq, msg->address_hi, msg->address_lo);
}