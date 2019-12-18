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
struct xilinx_pcie_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  reg_base; struct device* dev; } ;
struct resource {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int IRQF_NO_THREAD ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_pci_remap_cfg_resource (struct device*,struct resource*) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,struct xilinx_pcie_port*) ; 
 int /*<<< orphan*/  irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  xilinx_pcie_intr_handler ; 

__attribute__((used)) static int xilinx_pcie_parse_dt(struct xilinx_pcie_port *port)
{
	struct device *dev = port->dev;
	struct device_node *node = dev->of_node;
	struct resource regs;
	int err;

	err = of_address_to_resource(node, 0, &regs);
	if (err) {
		dev_err(dev, "missing \"reg\" property\n");
		return err;
	}

	port->reg_base = devm_pci_remap_cfg_resource(dev, &regs);
	if (IS_ERR(port->reg_base))
		return PTR_ERR(port->reg_base);

	port->irq = irq_of_parse_and_map(node, 0);
	err = devm_request_irq(dev, port->irq, xilinx_pcie_intr_handler,
			       IRQF_SHARED | IRQF_NO_THREAD,
			       "xilinx-pcie", port);
	if (err) {
		dev_err(dev, "unable to request irq %d\n", port->irq);
		return err;
	}

	return 0;
}