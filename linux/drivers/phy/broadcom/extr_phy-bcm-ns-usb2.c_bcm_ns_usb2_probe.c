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
struct bcm_ns_usb2 {int /*<<< orphan*/  phy; int /*<<< orphan*/  ref_clk; int /*<<< orphan*/  dmu; struct device* dev; } ;

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
 struct bcm_ns_usb2* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  ops ; 
 int /*<<< orphan*/  phy_set_drvdata (int /*<<< orphan*/ ,struct bcm_ns_usb2*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm_ns_usb2*) ; 

__attribute__((used)) static int bcm_ns_usb2_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm_ns_usb2 *usb2;
	struct resource *res;
	struct phy_provider *phy_provider;

	usb2 = devm_kzalloc(&pdev->dev, sizeof(*usb2), GFP_KERNEL);
	if (!usb2)
		return -ENOMEM;
	usb2->dev = dev;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dmu");
	usb2->dmu = devm_ioremap_resource(dev, res);
	if (IS_ERR(usb2->dmu)) {
		dev_err(dev, "Failed to map DMU regs\n");
		return PTR_ERR(usb2->dmu);
	}

	usb2->ref_clk = devm_clk_get(dev, "phy-ref-clk");
	if (IS_ERR(usb2->ref_clk)) {
		dev_err(dev, "Clock not defined\n");
		return PTR_ERR(usb2->ref_clk);
	}

	usb2->phy = devm_phy_create(dev, NULL, &ops);
	if (IS_ERR(usb2->phy))
		return PTR_ERR(usb2->phy);

	phy_set_drvdata(usb2->phy, usb2);
	platform_set_drvdata(pdev, usb2);

	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	return PTR_ERR_OR_ZERO(phy_provider);
}