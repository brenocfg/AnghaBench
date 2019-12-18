#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct mvebu_a3700_utmi {int /*<<< orphan*/  phy; TYPE_1__* caps; int /*<<< orphan*/  usb_misc; int /*<<< orphan*/  regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* power_off ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__* ops; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct mvebu_a3700_utmi* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_create (struct device*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_1__* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ ,struct mvebu_a3700_utmi*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mvebu_a3700_utmi_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct mvebu_a3700_utmi *utmi;
	struct phy_provider *provider;
	struct resource *res;

	utmi = devm_kzalloc(dev, sizeof(*utmi), GFP_KERNEL);
	if (!utmi)
		return -ENOMEM;

	/* Get UTMI memory region */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(dev, "Missing UTMI PHY memory resource\n");
		return -ENODEV;
	}

	utmi->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(utmi->regs))
		return PTR_ERR(utmi->regs);

	/* Get miscellaneous Host/PHY region */
	utmi->usb_misc = syscon_regmap_lookup_by_phandle(dev->of_node,
							 "marvell,usb-misc-reg");
	if (IS_ERR(utmi->usb_misc)) {
		dev_err(dev,
			"Missing USB misc purpose system controller\n");
		return PTR_ERR(utmi->usb_misc);
	}

	/* Retrieve PHY capabilities */
	utmi->caps = of_device_get_match_data(dev);

	/* Instantiate the PHY */
	utmi->phy = devm_phy_create(dev, NULL, utmi->caps->ops);
	if (IS_ERR(utmi->phy)) {
		dev_err(dev, "Failed to create the UTMI PHY\n");
		return PTR_ERR(utmi->phy);
	}

	phy_set_drvdata(utmi->phy, utmi);

	/* Ensure the PHY is powered off */
	utmi->caps->ops->power_off(utmi->phy);

	provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(provider);
}