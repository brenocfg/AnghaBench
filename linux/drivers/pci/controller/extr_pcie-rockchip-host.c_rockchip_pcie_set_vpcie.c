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
struct rockchip_pcie {int /*<<< orphan*/  vpcie12v; int /*<<< orphan*/  vpcie3v3; int /*<<< orphan*/  vpcie1v8; int /*<<< orphan*/  vpcie0v9; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_pcie_set_vpcie(struct rockchip_pcie *rockchip)
{
	struct device *dev = rockchip->dev;
	int err;

	if (!IS_ERR(rockchip->vpcie12v)) {
		err = regulator_enable(rockchip->vpcie12v);
		if (err) {
			dev_err(dev, "fail to enable vpcie12v regulator\n");
			goto err_out;
		}
	}

	if (!IS_ERR(rockchip->vpcie3v3)) {
		err = regulator_enable(rockchip->vpcie3v3);
		if (err) {
			dev_err(dev, "fail to enable vpcie3v3 regulator\n");
			goto err_disable_12v;
		}
	}

	if (!IS_ERR(rockchip->vpcie1v8)) {
		err = regulator_enable(rockchip->vpcie1v8);
		if (err) {
			dev_err(dev, "fail to enable vpcie1v8 regulator\n");
			goto err_disable_3v3;
		}
	}

	if (!IS_ERR(rockchip->vpcie0v9)) {
		err = regulator_enable(rockchip->vpcie0v9);
		if (err) {
			dev_err(dev, "fail to enable vpcie0v9 regulator\n");
			goto err_disable_1v8;
		}
	}

	return 0;

err_disable_1v8:
	if (!IS_ERR(rockchip->vpcie1v8))
		regulator_disable(rockchip->vpcie1v8);
err_disable_3v3:
	if (!IS_ERR(rockchip->vpcie3v3))
		regulator_disable(rockchip->vpcie3v3);
err_disable_12v:
	if (!IS_ERR(rockchip->vpcie12v))
		regulator_disable(rockchip->vpcie12v);
err_out:
	return err;
}