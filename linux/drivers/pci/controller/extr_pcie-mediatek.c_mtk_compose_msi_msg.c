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
struct mtk_pcie_port {TYPE_1__* pcie; scalar_t__ base; } ;
struct msi_msg {int /*<<< orphan*/  address_lo; int /*<<< orphan*/  address_hi; scalar_t__ data; } ;
struct irq_data {scalar_t__ hwirq; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PCIE_MSI_VECTOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mtk_pcie_port* irq_data_get_irq_chip_data (struct irq_data*) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (scalar_t__) ; 

__attribute__((used)) static void mtk_compose_msi_msg(struct irq_data *data, struct msi_msg *msg)
{
	struct mtk_pcie_port *port = irq_data_get_irq_chip_data(data);
	phys_addr_t addr;

	/* MT2712/MT7622 only support 32-bit MSI addresses */
	addr = virt_to_phys(port->base + PCIE_MSI_VECTOR);
	msg->address_hi = 0;
	msg->address_lo = lower_32_bits(addr);

	msg->data = data->hwirq;

	dev_dbg(port->pcie->dev, "msi#%d address_hi %#x address_lo %#x\n",
		(int)data->hwirq, msg->address_hi, msg->address_lo);
}