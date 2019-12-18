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
struct keystone_pcie {int /*<<< orphan*/  msi_host_irq; scalar_t__ is_am6; struct device_node* np; TYPE_1__* pci; } ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 struct irq_data* irq_get_irq_data (int) ; 
 int irq_of_parse_and_map (struct device_node*,int) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct keystone_pcie*) ; 
 int /*<<< orphan*/  ks_pcie_msi_irq_handler ; 
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int of_irq_count (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int ks_pcie_config_msi_irq(struct keystone_pcie *ks_pcie)
{
	struct device *dev = ks_pcie->pci->dev;
	struct device_node *np = ks_pcie->np;
	struct device_node *intc_np;
	struct irq_data *irq_data;
	int irq_count, irq, ret, i;

	if (!IS_ENABLED(CONFIG_PCI_MSI))
		return 0;

	intc_np = of_get_child_by_name(np, "msi-interrupt-controller");
	if (!intc_np) {
		if (ks_pcie->is_am6)
			return 0;
		dev_warn(dev, "msi-interrupt-controller node is absent\n");
		return -EINVAL;
	}

	irq_count = of_irq_count(intc_np);
	if (!irq_count) {
		dev_err(dev, "No IRQ entries in msi-interrupt-controller\n");
		ret = -EINVAL;
		goto err;
	}

	for (i = 0; i < irq_count; i++) {
		irq = irq_of_parse_and_map(intc_np, i);
		if (!irq) {
			ret = -EINVAL;
			goto err;
		}

		if (!ks_pcie->msi_host_irq) {
			irq_data = irq_get_irq_data(irq);
			if (!irq_data) {
				ret = -EINVAL;
				goto err;
			}
			ks_pcie->msi_host_irq = irq_data->hwirq;
		}

		irq_set_chained_handler_and_data(irq, ks_pcie_msi_irq_handler,
						 ks_pcie);
	}

	of_node_put(intc_np);
	return 0;

err:
	of_node_put(intc_np);
	return ret;
}