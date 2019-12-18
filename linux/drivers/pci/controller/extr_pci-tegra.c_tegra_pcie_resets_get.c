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
struct tegra_pcie {void* pcie_xrst; void* afi_rst; void* pex_rst; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 void* devm_reset_control_get_exclusive (struct device*,char*) ; 

__attribute__((used)) static int tegra_pcie_resets_get(struct tegra_pcie *pcie)
{
	struct device *dev = pcie->dev;

	pcie->pex_rst = devm_reset_control_get_exclusive(dev, "pex");
	if (IS_ERR(pcie->pex_rst))
		return PTR_ERR(pcie->pex_rst);

	pcie->afi_rst = devm_reset_control_get_exclusive(dev, "afi");
	if (IS_ERR(pcie->afi_rst))
		return PTR_ERR(pcie->afi_rst);

	pcie->pcie_xrst = devm_reset_control_get_exclusive(dev, "pcie_x");
	if (IS_ERR(pcie->pcie_xrst))
		return PTR_ERR(pcie->pcie_xrst);

	return 0;
}