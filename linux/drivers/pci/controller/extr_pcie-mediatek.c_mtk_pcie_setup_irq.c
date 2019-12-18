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
struct platform_device {int dummy; } ;
struct mtk_pcie_port {int /*<<< orphan*/  irq; int /*<<< orphan*/  slot; struct mtk_pcie* pcie; } ;
struct mtk_pcie {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mtk_pcie_port*) ; 
 int mtk_pcie_init_irq_domain (struct mtk_pcie_port*,struct device_node*) ; 
 int /*<<< orphan*/  mtk_pcie_intr_handler ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int mtk_pcie_setup_irq(struct mtk_pcie_port *port,
			      struct device_node *node)
{
	struct mtk_pcie *pcie = port->pcie;
	struct device *dev = pcie->dev;
	struct platform_device *pdev = to_platform_device(dev);
	int err;

	err = mtk_pcie_init_irq_domain(port, node);
	if (err) {
		dev_err(dev, "failed to init PCIe IRQ domain\n");
		return err;
	}

	port->irq = platform_get_irq(pdev, port->slot);
	irq_set_chained_handler_and_data(port->irq,
					 mtk_pcie_intr_handler, port);

	return 0;
}