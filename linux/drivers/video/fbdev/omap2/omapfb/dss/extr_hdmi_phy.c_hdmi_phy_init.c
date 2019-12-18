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
struct hdmi_phy_data {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSSERR (char*) ; 
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  hdmi_phy_get_features () ; 
 int /*<<< orphan*/  phy_feat ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 

int hdmi_phy_init(struct platform_device *pdev, struct hdmi_phy_data *phy)
{
	struct resource *res;

	phy_feat = hdmi_phy_get_features();
	if (!phy_feat)
		return -ENODEV;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	if (!res) {
		DSSERR("can't get PHY mem resource\n");
		return -EINVAL;
	}

	phy->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(phy->base)) {
		DSSERR("can't ioremap TX PHY\n");
		return PTR_ERR(phy->base);
	}

	return 0;
}