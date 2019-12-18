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
struct resource {int dummy; } ;
struct rcar_gen3_usb3 {int usb3s_clk; int usb_extal; struct phy_provider* phy; int /*<<< orphan*/  ssc_range; struct phy_provider* base; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
typedef  struct phy_provider clk ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct phy_provider*) ; 
 int /*<<< orphan*/  clk_get_rate (struct phy_provider*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct phy_provider* devm_clk_get (struct device*,char*) ; 
 struct phy_provider* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct rcar_gen3_usb3* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct rcar_gen3_usb3*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rcar_gen3_usb3*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  rcar_gen3_phy_usb3_ops ; 

__attribute__((used)) static int rcar_gen3_phy_usb3_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rcar_gen3_usb3 *r;
	struct phy_provider *provider;
	struct resource *res;
	int ret = 0;
	struct clk *clk;

	if (!dev->of_node) {
		dev_err(dev, "This driver needs device tree\n");
		return -EINVAL;
	}

	r = devm_kzalloc(dev, sizeof(*r), GFP_KERNEL);
	if (!r)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	r->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(r->base))
		return PTR_ERR(r->base);

	clk = devm_clk_get(dev, "usb3s_clk");
	if (!IS_ERR(clk) && !clk_prepare_enable(clk)) {
		r->usb3s_clk = !!clk_get_rate(clk);
		clk_disable_unprepare(clk);
	}
	clk = devm_clk_get(dev, "usb_extal");
	if (!IS_ERR(clk) && !clk_prepare_enable(clk)) {
		r->usb_extal = !!clk_get_rate(clk);
		clk_disable_unprepare(clk);
	}

	if (!r->usb3s_clk && !r->usb_extal) {
		dev_err(dev, "This driver needs usb3s_clk and/or usb_extal\n");
		ret = -EINVAL;
		goto error;
	}

	/*
	 * devm_phy_create() will call pm_runtime_enable(&phy->dev);
	 * And then, phy-core will manage runtime pm for this device.
	 */
	pm_runtime_enable(dev);

	r->phy = devm_phy_create(dev, NULL, &rcar_gen3_phy_usb3_ops);
	if (IS_ERR(r->phy)) {
		dev_err(dev, "Failed to create USB3 PHY\n");
		ret = PTR_ERR(r->phy);
		goto error;
	}

	of_property_read_u32(dev->of_node, "renesas,ssc-range", &r->ssc_range);

	platform_set_drvdata(pdev, r);
	phy_set_drvdata(r->phy, r);

	provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	if (IS_ERR(provider)) {
		dev_err(dev, "Failed to register PHY provider\n");
		ret = PTR_ERR(provider);
		goto error;
	}

	return 0;

error:
	pm_runtime_disable(dev);

	return ret;
}