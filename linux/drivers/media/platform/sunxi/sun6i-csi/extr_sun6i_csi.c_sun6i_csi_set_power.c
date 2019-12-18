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
struct sun6i_csi_dev {int /*<<< orphan*/  clk_mod; int /*<<< orphan*/  clk_ram; struct device* dev; int /*<<< orphan*/  rstc_bus; struct regmap* regmap; } ;
struct sun6i_csi {int dummy; } ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI_EN_CSI_EN ; 
 int /*<<< orphan*/  CSI_EN_REG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_rate_exclusive_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_set_rate_exclusive (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 struct sun6i_csi_dev* sun6i_csi_to_dev (struct sun6i_csi*) ; 

int sun6i_csi_set_power(struct sun6i_csi *csi, bool enable)
{
	struct sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);
	struct device *dev = sdev->dev;
	struct regmap *regmap = sdev->regmap;
	int ret;

	if (!enable) {
		regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN, 0);

		clk_disable_unprepare(sdev->clk_ram);
		if (of_device_is_compatible(dev->of_node,
					    "allwinner,sun50i-a64-csi"))
			clk_rate_exclusive_put(sdev->clk_mod);
		clk_disable_unprepare(sdev->clk_mod);
		reset_control_assert(sdev->rstc_bus);
		return 0;
	}

	ret = clk_prepare_enable(sdev->clk_mod);
	if (ret) {
		dev_err(sdev->dev, "Enable csi clk err %d\n", ret);
		return ret;
	}

	if (of_device_is_compatible(dev->of_node, "allwinner,sun50i-a64-csi"))
		clk_set_rate_exclusive(sdev->clk_mod, 300000000);

	ret = clk_prepare_enable(sdev->clk_ram);
	if (ret) {
		dev_err(sdev->dev, "Enable clk_dram_csi clk err %d\n", ret);
		goto clk_mod_disable;
	}

	ret = reset_control_deassert(sdev->rstc_bus);
	if (ret) {
		dev_err(sdev->dev, "reset err %d\n", ret);
		goto clk_ram_disable;
	}

	regmap_update_bits(regmap, CSI_EN_REG, CSI_EN_CSI_EN, CSI_EN_CSI_EN);

	return 0;

clk_ram_disable:
	clk_disable_unprepare(sdev->clk_ram);
clk_mod_disable:
	if (of_device_is_compatible(dev->of_node, "allwinner,sun50i-a64-csi"))
		clk_rate_exclusive_put(sdev->clk_mod);
	clk_disable_unprepare(sdev->clk_mod);
	return ret;
}