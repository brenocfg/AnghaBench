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
struct rockchip_pcie {void* vpcie0v9; void* vpcie1v8; void* vpcie3v3; void* vpcie12v; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 void* devm_regulator_get_optional (struct device*,char*) ; 
 int rockchip_pcie_parse_dt (struct rockchip_pcie*) ; 
 int rockchip_pcie_setup_irq (struct rockchip_pcie*) ; 

__attribute__((used)) static int rockchip_pcie_parse_host_dt(struct rockchip_pcie *rockchip)
{
	struct device *dev = rockchip->dev;
	int err;

	err = rockchip_pcie_parse_dt(rockchip);
	if (err)
		return err;

	err = rockchip_pcie_setup_irq(rockchip);
	if (err)
		return err;

	rockchip->vpcie12v = devm_regulator_get_optional(dev, "vpcie12v");
	if (IS_ERR(rockchip->vpcie12v)) {
		if (PTR_ERR(rockchip->vpcie12v) != -ENODEV)
			return PTR_ERR(rockchip->vpcie12v);
		dev_info(dev, "no vpcie12v regulator found\n");
	}

	rockchip->vpcie3v3 = devm_regulator_get_optional(dev, "vpcie3v3");
	if (IS_ERR(rockchip->vpcie3v3)) {
		if (PTR_ERR(rockchip->vpcie3v3) != -ENODEV)
			return PTR_ERR(rockchip->vpcie3v3);
		dev_info(dev, "no vpcie3v3 regulator found\n");
	}

	rockchip->vpcie1v8 = devm_regulator_get_optional(dev, "vpcie1v8");
	if (IS_ERR(rockchip->vpcie1v8)) {
		if (PTR_ERR(rockchip->vpcie1v8) != -ENODEV)
			return PTR_ERR(rockchip->vpcie1v8);
		dev_info(dev, "no vpcie1v8 regulator found\n");
	}

	rockchip->vpcie0v9 = devm_regulator_get_optional(dev, "vpcie0v9");
	if (IS_ERR(rockchip->vpcie0v9)) {
		if (PTR_ERR(rockchip->vpcie0v9) != -ENODEV)
			return PTR_ERR(rockchip->vpcie0v9);
		dev_info(dev, "no vpcie0v9 regulator found\n");
	}

	return 0;
}