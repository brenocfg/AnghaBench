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
struct rockchip_dp_phy {struct device* dev; struct phy* grf; struct phy* phy_24m; } ;
struct device {TYPE_1__* parent; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GRF_EDP_REF_CLK_SEL_INTER ; 
 int GRF_EDP_REF_CLK_SEL_INTER_HIWORD_MASK ; 
 int /*<<< orphan*/  GRF_SOC_CON12 ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int clk_set_rate (struct phy*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct phy* devm_clk_get (struct device*,char*) ; 
 struct rockchip_dp_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct rockchip_dp_phy*) ; 
 int regmap_write (struct phy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rockchip_dp_phy_ops ; 
 struct phy* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_dp_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct phy_provider *phy_provider;
	struct rockchip_dp_phy *dp;
	struct phy *phy;
	int ret;

	if (!np)
		return -ENODEV;

	if (!dev->parent || !dev->parent->of_node)
		return -ENODEV;

	dp = devm_kzalloc(dev, sizeof(*dp), GFP_KERNEL);
	if (!dp)
		return -ENOMEM;

	dp->dev = dev;

	dp->phy_24m = devm_clk_get(dev, "24m");
	if (IS_ERR(dp->phy_24m)) {
		dev_err(dev, "cannot get clock 24m\n");
		return PTR_ERR(dp->phy_24m);
	}

	ret = clk_set_rate(dp->phy_24m, 24000000);
	if (ret < 0) {
		dev_err(dp->dev, "cannot set clock phy_24m %d\n", ret);
		return ret;
	}

	dp->grf = syscon_node_to_regmap(dev->parent->of_node);
	if (IS_ERR(dp->grf)) {
		dev_err(dev, "rk3288-dp needs the General Register Files syscon\n");
		return PTR_ERR(dp->grf);
	}

	ret = regmap_write(dp->grf, GRF_SOC_CON12, GRF_EDP_REF_CLK_SEL_INTER |
			   GRF_EDP_REF_CLK_SEL_INTER_HIWORD_MASK);
	if (ret != 0) {
		dev_err(dp->dev, "Could not config GRF edp ref clk: %d\n", ret);
		return ret;
	}

	phy = devm_phy_create(dev, np, &rockchip_dp_phy_ops);
	if (IS_ERR(phy)) {
		dev_err(dev, "failed to create phy\n");
		return PTR_ERR(phy);
	}
	phy_set_drvdata(phy, dp);

	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}