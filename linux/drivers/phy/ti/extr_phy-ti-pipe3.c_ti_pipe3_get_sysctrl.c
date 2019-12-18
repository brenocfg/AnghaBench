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
struct ti_pipe3 {scalar_t__ mode; int /*<<< orphan*/  dpll_reset_reg; int /*<<< orphan*/ * dpll_reset_syscon; int /*<<< orphan*/  pcie_pcs_reg; int /*<<< orphan*/ * pcs_syscon; int /*<<< orphan*/ * control_dev; int /*<<< orphan*/ * phy_power_syscon; int /*<<< orphan*/  power_reg; struct device* dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 scalar_t__ PIPE3_MODE_PCIE ; 
 scalar_t__ PIPE3_MODE_SATA ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,int /*<<< orphan*/ *) ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int ti_pipe3_get_sysctrl(struct ti_pipe3 *phy)
{
	struct device *dev = phy->dev;
	struct device_node *node = dev->of_node;
	struct device_node *control_node;
	struct platform_device *control_pdev;

	phy->phy_power_syscon = syscon_regmap_lookup_by_phandle(node,
							"syscon-phy-power");
	if (IS_ERR(phy->phy_power_syscon)) {
		dev_dbg(dev,
			"can't get syscon-phy-power, using control device\n");
		phy->phy_power_syscon = NULL;
	} else {
		if (of_property_read_u32_index(node,
					       "syscon-phy-power", 1,
					       &phy->power_reg)) {
			dev_err(dev, "couldn't get power reg. offset\n");
			return -EINVAL;
		}
	}

	if (!phy->phy_power_syscon) {
		control_node = of_parse_phandle(node, "ctrl-module", 0);
		if (!control_node) {
			dev_err(dev, "Failed to get control device phandle\n");
			return -EINVAL;
		}

		control_pdev = of_find_device_by_node(control_node);
		if (!control_pdev) {
			dev_err(dev, "Failed to get control device\n");
			return -EINVAL;
		}

		phy->control_dev = &control_pdev->dev;
	}

	if (phy->mode == PIPE3_MODE_PCIE) {
		phy->pcs_syscon = syscon_regmap_lookup_by_phandle(node,
								  "syscon-pcs");
		if (IS_ERR(phy->pcs_syscon)) {
			dev_dbg(dev,
				"can't get syscon-pcs, using omap control\n");
			phy->pcs_syscon = NULL;
		} else {
			if (of_property_read_u32_index(node,
						       "syscon-pcs", 1,
						       &phy->pcie_pcs_reg)) {
				dev_err(dev,
					"couldn't get pcie pcs reg. offset\n");
				return -EINVAL;
			}
		}
	}

	if (phy->mode == PIPE3_MODE_SATA) {
		phy->dpll_reset_syscon = syscon_regmap_lookup_by_phandle(node,
							"syscon-pllreset");
		if (IS_ERR(phy->dpll_reset_syscon)) {
			dev_info(dev,
				 "can't get syscon-pllreset, sata dpll won't idle\n");
			phy->dpll_reset_syscon = NULL;
		} else {
			if (of_property_read_u32_index(node,
						       "syscon-pllreset", 1,
						       &phy->dpll_reset_reg)) {
				dev_err(dev,
					"couldn't get pllreset reg. offset\n");
				return -EINVAL;
			}
		}
	}

	return 0;
}