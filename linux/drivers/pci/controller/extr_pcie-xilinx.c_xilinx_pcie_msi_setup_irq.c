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
struct xilinx_pcie_port {scalar_t__ msi_pages; int /*<<< orphan*/  msi_domain; } ;
struct pci_dev {TYPE_1__* bus; } ;
struct msi_msg {unsigned int data; int /*<<< orphan*/  address_lo; scalar_t__ address_hi; } ;
struct msi_desc {int dummy; } ;
struct msi_controller {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {struct xilinx_pcie_port* sysdata; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int irq_create_mapping (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  irq_set_msi_desc (unsigned int,struct msi_desc*) ; 
 int /*<<< orphan*/  pci_write_msi_msg (unsigned int,struct msi_msg*) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 
 int xilinx_pcie_assign_msi () ; 

__attribute__((used)) static int xilinx_pcie_msi_setup_irq(struct msi_controller *chip,
				     struct pci_dev *pdev,
				     struct msi_desc *desc)
{
	struct xilinx_pcie_port *port = pdev->bus->sysdata;
	unsigned int irq;
	int hwirq;
	struct msi_msg msg;
	phys_addr_t msg_addr;

	hwirq = xilinx_pcie_assign_msi();
	if (hwirq < 0)
		return hwirq;

	irq = irq_create_mapping(port->msi_domain, hwirq);
	if (!irq)
		return -EINVAL;

	irq_set_msi_desc(irq, desc);

	msg_addr = virt_to_phys((void *)port->msi_pages);

	msg.address_hi = 0;
	msg.address_lo = msg_addr;
	msg.data = irq;

	pci_write_msi_msg(irq, &msg);

	return 0;
}