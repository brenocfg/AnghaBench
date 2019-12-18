#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tegra_pcie {int num_supplies; TYPE_1__* supplies; struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct TYPE_3__ {char* supply; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct device_node*) ; 
 TYPE_1__* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int devm_regulator_bulk_get (struct device*,int,TYPE_1__*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 

__attribute__((used)) static int tegra_pcie_get_legacy_regulators(struct tegra_pcie *pcie)
{
	struct device *dev = pcie->dev;
	struct device_node *np = dev->of_node;

	if (of_device_is_compatible(np, "nvidia,tegra30-pcie"))
		pcie->num_supplies = 3;
	else if (of_device_is_compatible(np, "nvidia,tegra20-pcie"))
		pcie->num_supplies = 2;

	if (pcie->num_supplies == 0) {
		dev_err(dev, "device %pOF not supported in legacy mode\n", np);
		return -ENODEV;
	}

	pcie->supplies = devm_kcalloc(dev, pcie->num_supplies,
				      sizeof(*pcie->supplies),
				      GFP_KERNEL);
	if (!pcie->supplies)
		return -ENOMEM;

	pcie->supplies[0].supply = "pex-clk";
	pcie->supplies[1].supply = "vdd";

	if (pcie->num_supplies > 2)
		pcie->supplies[2].supply = "avdd";

	return devm_regulator_bulk_get(dev, pcie->num_supplies, pcie->supplies);
}