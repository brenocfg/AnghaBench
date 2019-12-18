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
typedef  int u32 ;
struct tegra_pcie {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_111 ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_211 ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_222 ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_401 ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_411 ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_420 ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_DUAL ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_SINGLE ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X2_X1 ; 
 int AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X4_X1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static int tegra_pcie_get_xbar_config(struct tegra_pcie *pcie, u32 lanes,
				      u32 *xbar)
{
	struct device *dev = pcie->dev;
	struct device_node *np = dev->of_node;

	if (of_device_is_compatible(np, "nvidia,tegra186-pcie")) {
		switch (lanes) {
		case 0x010004:
			dev_info(dev, "4x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_401;
			return 0;

		case 0x010102:
			dev_info(dev, "2x1, 1X1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_211;
			return 0;

		case 0x010101:
			dev_info(dev, "1x1, 1x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_111;
			return 0;

		default:
			dev_info(dev, "wrong configuration updated in DT, "
				 "switching to default 2x1, 1x1, 1x1 "
				 "configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_211;
			return 0;
		}
	} else if (of_device_is_compatible(np, "nvidia,tegra124-pcie") ||
		   of_device_is_compatible(np, "nvidia,tegra210-pcie")) {
		switch (lanes) {
		case 0x0000104:
			dev_info(dev, "4x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X4_X1;
			return 0;

		case 0x0000102:
			dev_info(dev, "2x1, 1x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_X2_X1;
			return 0;
		}
	} else if (of_device_is_compatible(np, "nvidia,tegra30-pcie")) {
		switch (lanes) {
		case 0x00000204:
			dev_info(dev, "4x1, 2x1 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_420;
			return 0;

		case 0x00020202:
			dev_info(dev, "2x3 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_222;
			return 0;

		case 0x00010104:
			dev_info(dev, "4x1, 1x2 configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_411;
			return 0;
		}
	} else if (of_device_is_compatible(np, "nvidia,tegra20-pcie")) {
		switch (lanes) {
		case 0x00000004:
			dev_info(dev, "single-mode configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_SINGLE;
			return 0;

		case 0x00000202:
			dev_info(dev, "dual-mode configuration\n");
			*xbar = AFI_PCIE_CONFIG_SM2TMS0_XBAR_CONFIG_DUAL;
			return 0;
		}
	}

	return -EINVAL;
}