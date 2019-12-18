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
typedef  int u32 ;
struct imx6_pcie {int /*<<< orphan*/  iomuxc_gpr; TYPE_1__* pci; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int IMX7D_GPR22_PCIE_PHY_PLL_LOCKED ; 
 int /*<<< orphan*/  IOMUXC_GPR22 ; 
 int /*<<< orphan*/  PHY_PLL_LOCK_WAIT_TIMEOUT ; 
 int /*<<< orphan*/  PHY_PLL_LOCK_WAIT_USLEEP_MAX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void imx7d_pcie_wait_for_phy_pll_lock(struct imx6_pcie *imx6_pcie)
{
	u32 val;
	struct device *dev = imx6_pcie->pci->dev;

	if (regmap_read_poll_timeout(imx6_pcie->iomuxc_gpr,
				     IOMUXC_GPR22, val,
				     val & IMX7D_GPR22_PCIE_PHY_PLL_LOCKED,
				     PHY_PLL_LOCK_WAIT_USLEEP_MAX,
				     PHY_PLL_LOCK_WAIT_TIMEOUT))
		dev_err(dev, "PCIe PLL lock timeout\n");
}