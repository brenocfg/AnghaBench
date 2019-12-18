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
struct TYPE_2__ {int /*<<< orphan*/  pp; } ;
struct tegra_pcie_dw {int /*<<< orphan*/  msi_ctrl_int; TYPE_1__ pci; int /*<<< orphan*/  link_state; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_LOGIC_MSI_CTRL_INT_0_EN ; 
 int __deinit_controller (struct tegra_pcie_dw*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct tegra_pcie_dw* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dw_pcie_writel_dbi (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tegra_pcie_config_controller (struct tegra_pcie_dw*,int) ; 
 int tegra_pcie_dw_host_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tegra_pcie_dw_resume_noirq(struct device *dev)
{
	struct tegra_pcie_dw *pcie = dev_get_drvdata(dev);
	int ret;

	if (!pcie->link_state)
		return 0;

	ret = tegra_pcie_config_controller(pcie, true);
	if (ret < 0)
		return ret;

	ret = tegra_pcie_dw_host_init(&pcie->pci.pp);
	if (ret < 0) {
		dev_err(dev, "Failed to init host: %d\n", ret);
		goto fail_host_init;
	}

	/* Restore MSI interrupt vector */
	dw_pcie_writel_dbi(&pcie->pci, PORT_LOGIC_MSI_CTRL_INT_0_EN,
			   pcie->msi_ctrl_int);

	return 0;

fail_host_init:
	return __deinit_controller(pcie);
}