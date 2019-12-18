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
struct pxa_usb_phy {int version; struct phy_provider* phy; struct phy_provider* base; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct of_device_id {scalar_t__ data; } ;
typedef  enum pxa_usb_phy_version { ____Placeholder_pxa_usb_phy_version } pxa_usb_phy_version ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int PXA_USB_PHY_MMP2 ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct phy_provider* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct pxa_usb_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_create_lookup (struct phy_provider*,char*,char*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct pxa_usb_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pxa_usb_phy_of_match ; 
 int /*<<< orphan*/  pxa_usb_phy_ops ; 

__attribute__((used)) static int pxa_usb_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct resource *resource;
	struct pxa_usb_phy *pxa_usb_phy;
	struct phy_provider *provider;
	const struct of_device_id *of_id;

	pxa_usb_phy = devm_kzalloc(dev, sizeof(struct pxa_usb_phy), GFP_KERNEL);
	if (!pxa_usb_phy)
		return -ENOMEM;

	of_id = of_match_node(pxa_usb_phy_of_match, dev->of_node);
	if (of_id)
		pxa_usb_phy->version = (enum pxa_usb_phy_version)of_id->data;
	else
		pxa_usb_phy->version = PXA_USB_PHY_MMP2;

	resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pxa_usb_phy->base = devm_ioremap_resource(dev, resource);
	if (IS_ERR(pxa_usb_phy->base)) {
		dev_err(dev, "failed to remap PHY regs\n");
		return PTR_ERR(pxa_usb_phy->base);
	}

	pxa_usb_phy->phy = devm_phy_create(dev, NULL, &pxa_usb_phy_ops);
	if (IS_ERR(pxa_usb_phy->phy)) {
		dev_err(dev, "failed to create PHY\n");
		return PTR_ERR(pxa_usb_phy->phy);
	}

	phy_set_drvdata(pxa_usb_phy->phy, pxa_usb_phy);
	provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);
	if (IS_ERR(provider)) {
		dev_err(dev, "failed to register PHY provider\n");
		return PTR_ERR(provider);
	}

	if (!dev->of_node) {
		phy_create_lookup(pxa_usb_phy->phy, "usb", "mv-udc");
		phy_create_lookup(pxa_usb_phy->phy, "usb", "pxa-u2oehci");
		phy_create_lookup(pxa_usb_phy->phy, "usb", "mv-otg");
	}

	dev_info(dev, "Marvell PXA USB PHY");
	return 0;
}