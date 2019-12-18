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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy {int dummy; } ;
struct exynos_pcie_phy_data {int /*<<< orphan*/  ops; } ;
struct exynos_pcie_phy {struct exynos_pcie_phy_data const* drv_data; struct phy* blk_base; struct phy* phy_base; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int PTR_ERR_OR_ZERO (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct exynos_pcie_phy* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy* devm_phy_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct exynos_pcie_phy_data* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy*,struct exynos_pcie_phy*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int exynos_pcie_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct exynos_pcie_phy *exynos_phy;
	struct phy *generic_phy;
	struct phy_provider *phy_provider;
	struct resource *res;
	const struct exynos_pcie_phy_data *drv_data;

	drv_data = of_device_get_match_data(dev);
	if (!drv_data)
		return -ENODEV;

	exynos_phy = devm_kzalloc(dev, sizeof(*exynos_phy), GFP_KERNEL);
	if (!exynos_phy)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	exynos_phy->phy_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(exynos_phy->phy_base))
		return PTR_ERR(exynos_phy->phy_base);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	exynos_phy->blk_base = devm_ioremap_resource(dev, res);
	if (IS_ERR(exynos_phy->blk_base))
		return PTR_ERR(exynos_phy->blk_base);

	exynos_phy->drv_data = drv_data;

	generic_phy = devm_phy_create(dev, dev->of_node, drv_data->ops);
	if (IS_ERR(generic_phy)) {
		dev_err(dev, "failed to create PHY\n");
		return PTR_ERR(generic_phy);
	}

	phy_set_drvdata(generic_phy, exynos_phy);
	phy_provider = devm_of_phy_provider_register(dev, of_phy_simple_xlate);

	return PTR_ERR_OR_ZERO(phy_provider);
}