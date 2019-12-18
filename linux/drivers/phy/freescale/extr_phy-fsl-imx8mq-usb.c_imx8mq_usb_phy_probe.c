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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct imx8mq_usb_phy {int /*<<< orphan*/  phy; int /*<<< orphan*/  vbus; int /*<<< orphan*/  base; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct imx8mq_usb_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  imx8mq_usb_phy_ops ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ ,struct imx8mq_usb_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx8mq_usb_phy_probe(struct platform_device *pdev)
{
	struct phy_provider *phy_provider;
	struct device *dev = &pdev->dev;
	struct imx8mq_usb_phy *imx_phy;
	struct resource *res;

	imx_phy = devm_kzalloc(dev, sizeof(*imx_phy), GFP_KERNEL);
	if (!imx_phy)
		return -ENOMEM;

	imx_phy->clk = devm_clk_get(dev, "phy");
	if (IS_ERR(imx_phy->clk)) {
		dev_err(dev, "failed to get imx8mq usb phy clock\n");
		return PTR_ERR(imx_phy->clk);
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	imx_phy->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(imx_phy->base))
		return PTR_ERR(imx_phy->base);

	imx_phy->phy = devm_phy_create(dev, NULL, &imx8mq_usb_phy_ops);
	if (IS_ERR(imx_phy->phy))
		return PTR_ERR(imx_phy->phy);

	imx_phy->vbus = devm_regulator_get(dev, "vbus");
	if (IS_ERR(imx_phy->vbus))
		return PTR_ERR(imx_phy->vbus);

	phy_set_drvdata(imx_phy->phy, imx_phy);

	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}