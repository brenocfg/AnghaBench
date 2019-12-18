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
struct ralink_usb_phy {uintptr_t clk; int /*<<< orphan*/ * phy; int /*<<< orphan*/ * rstdev; int /*<<< orphan*/ * rsthost; int /*<<< orphan*/ * base; int /*<<< orphan*/ * sysctl; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct ralink_usb_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* devm_reset_control_get (struct device*,char*) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ *,struct ralink_usb_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ralink_usb_phy_of_match ; 
 int /*<<< orphan*/  ralink_usb_phy_ops ; 
 int /*<<< orphan*/ * syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ralink_usb_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *res;
	struct phy_provider *phy_provider;
	const struct of_device_id *match;
	struct ralink_usb_phy *phy;

	match = of_match_device(ralink_usb_phy_of_match, &pdev->dev);
	if (!match)
		return -ENODEV;

	phy = devm_kzalloc(dev, sizeof(*phy), GFP_KERNEL);
	if (!phy)
		return -ENOMEM;

	phy->clk = (uintptr_t)match->data;
	phy->base = NULL;

	phy->sysctl = syscon_regmap_lookup_by_phandle(dev->of_node, "ralink,sysctl");
	if (IS_ERR(phy->sysctl)) {
		dev_err(dev, "failed to get sysctl registers\n");
		return PTR_ERR(phy->sysctl);
	}

	/* The MT7628 and MT7688 require extra setup of PHY registers. */
	if (of_device_is_compatible(dev->of_node, "mediatek,mt7628-usbphy")) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		phy->base = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(phy->base)) {
			dev_err(dev, "failed to remap register memory\n");
			return PTR_ERR(phy->base);
		}
	}

	phy->rsthost = devm_reset_control_get(&pdev->dev, "host");
	if (IS_ERR(phy->rsthost)) {
		dev_err(dev, "host reset is missing\n");
		return PTR_ERR(phy->rsthost);
	}

	phy->rstdev = devm_reset_control_get(&pdev->dev, "device");
	if (IS_ERR(phy->rstdev)) {
		dev_err(dev, "device reset is missing\n");
		return PTR_ERR(phy->rstdev);
	}

	phy->phy = devm_phy_create(dev, NULL, &ralink_usb_phy_ops);
	if (IS_ERR(phy->phy)) {
		dev_err(dev, "failed to create PHY\n");
		return PTR_ERR(phy->phy);
	}
	phy_set_drvdata(phy->phy, phy);

	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}