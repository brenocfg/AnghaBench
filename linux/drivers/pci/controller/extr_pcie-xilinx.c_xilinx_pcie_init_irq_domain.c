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
struct xilinx_pcie_port {void* msi_domain; void* leg_domain; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 int ENODEV ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_NUM_INTX ; 
 int /*<<< orphan*/  XILINX_NUM_MSI_IRQS ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  intx_domain_ops ; 
 void* irq_domain_add_linear (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct xilinx_pcie_port*) ; 
 int /*<<< orphan*/  msi_domain_ops ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int xilinx_pcie_enable_msi (struct xilinx_pcie_port*) ; 
 struct xilinx_pcie_port xilinx_pcie_msi_chip ; 

__attribute__((used)) static int xilinx_pcie_init_irq_domain(struct xilinx_pcie_port *port)
{
	struct device *dev = port->dev;
	struct device_node *node = dev->of_node;
	struct device_node *pcie_intc_node;
	int ret;

	/* Setup INTx */
	pcie_intc_node = of_get_next_child(node, NULL);
	if (!pcie_intc_node) {
		dev_err(dev, "No PCIe Intc node found\n");
		return -ENODEV;
	}

	port->leg_domain = irq_domain_add_linear(pcie_intc_node, PCI_NUM_INTX,
						 &intx_domain_ops,
						 port);
	of_node_put(pcie_intc_node);
	if (!port->leg_domain) {
		dev_err(dev, "Failed to get a INTx IRQ domain\n");
		return -ENODEV;
	}

	/* Setup MSI */
	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		port->msi_domain = irq_domain_add_linear(node,
							 XILINX_NUM_MSI_IRQS,
							 &msi_domain_ops,
							 &xilinx_pcie_msi_chip);
		if (!port->msi_domain) {
			dev_err(dev, "Failed to get a MSI IRQ domain\n");
			return -ENODEV;
		}

		ret = xilinx_pcie_enable_msi(port);
		if (ret)
			return ret;
	}

	return 0;
}