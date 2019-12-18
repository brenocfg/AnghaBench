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
struct pcie_port {int /*<<< orphan*/  msi_irq; } ;
struct TYPE_2__ {struct pcie_port pp; } ;
struct tegra_pcie_dw {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  link_state; TYPE_1__ pci; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PCI_MSI ; 
 int ENODEV ; 
 int ENOMEDIUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugfs_create_dir (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 char* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_debugfs (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  of_irq_get_byname (int /*<<< orphan*/ ,char*) ; 
 int pinctrl_pm_select_default_state (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  tegra_pcie_deinit_controller (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  tegra_pcie_dw_link_up (TYPE_1__*) ; 
 int /*<<< orphan*/  tegra_pcie_init_controller (struct tegra_pcie_dw*) ; 

__attribute__((used)) static int tegra_pcie_config_rp(struct tegra_pcie_dw *pcie)
{
	struct pcie_port *pp = &pcie->pci.pp;
	struct device *dev = pcie->dev;
	char *name;
	int ret;

	if (IS_ENABLED(CONFIG_PCI_MSI)) {
		pp->msi_irq = of_irq_get_byname(dev->of_node, "msi");
		if (!pp->msi_irq) {
			dev_err(dev, "Failed to get MSI interrupt\n");
			return -ENODEV;
		}
	}

	pm_runtime_enable(dev);

	ret = pm_runtime_get_sync(dev);
	if (ret < 0) {
		dev_err(dev, "Failed to get runtime sync for PCIe dev: %d\n",
			ret);
		goto fail_pm_get_sync;
	}

	ret = pinctrl_pm_select_default_state(dev);
	if (ret < 0) {
		dev_err(dev, "Failed to configure sideband pins: %d\n", ret);
		goto fail_pinctrl;
	}

	tegra_pcie_init_controller(pcie);

	pcie->link_state = tegra_pcie_dw_link_up(&pcie->pci);
	if (!pcie->link_state) {
		ret = -ENOMEDIUM;
		goto fail_host_init;
	}

	name = devm_kasprintf(dev, GFP_KERNEL, "%pOFP", dev->of_node);
	if (!name) {
		ret = -ENOMEM;
		goto fail_host_init;
	}

	pcie->debugfs = debugfs_create_dir(name, NULL);
	if (!pcie->debugfs)
		dev_err(dev, "Failed to create debugfs\n");
	else
		init_debugfs(pcie);

	return ret;

fail_host_init:
	tegra_pcie_deinit_controller(pcie);
fail_pinctrl:
	pm_runtime_put_sync(dev);
fail_pm_get_sync:
	pm_runtime_disable(dev);
	return ret;
}