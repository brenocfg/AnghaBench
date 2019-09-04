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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hdmi_phy_data {int /*<<< orphan*/  base; int /*<<< orphan*/ * features; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  omap44xx_phy_feats ; 
 int /*<<< orphan*/  omap54xx_phy_feats ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

int hdmi_phy_init(struct platform_device *pdev, struct hdmi_phy_data *phy,
		  unsigned int version)
{
	struct resource *res;

	if (version == 4)
		phy->features = &omap44xx_phy_feats;
	else
		phy->features = &omap54xx_phy_feats;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	phy->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(phy->base))
		return PTR_ERR(phy->base);

	return 0;
}