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
struct regmap {int dummy; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PCIE_B0_B1_TSYNCEN ; 
 int PCIE_B1C0_MODE_SEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ of_property_read_u32_index (struct device_node*,char*,int,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,unsigned int,int,int) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int dra7xx_pcie_configure_two_lane(struct device *dev,
					  u32 b1co_mode_sel_mask)
{
	struct device_node *np = dev->of_node;
	struct regmap *pcie_syscon;
	unsigned int pcie_reg;
	u32 mask;
	u32 val;

	pcie_syscon = syscon_regmap_lookup_by_phandle(np, "ti,syscon-lane-sel");
	if (IS_ERR(pcie_syscon)) {
		dev_err(dev, "unable to get ti,syscon-lane-sel\n");
		return -EINVAL;
	}

	if (of_property_read_u32_index(np, "ti,syscon-lane-sel", 1,
				       &pcie_reg)) {
		dev_err(dev, "couldn't get lane selection reg offset\n");
		return -EINVAL;
	}

	mask = b1co_mode_sel_mask | PCIE_B0_B1_TSYNCEN;
	val = PCIE_B1C0_MODE_SEL | PCIE_B0_B1_TSYNCEN;
	regmap_update_bits(pcie_syscon, pcie_reg, mask, val);

	return 0;
}