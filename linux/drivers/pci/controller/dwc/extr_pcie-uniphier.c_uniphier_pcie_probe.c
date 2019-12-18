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
struct TYPE_2__ {int /*<<< orphan*/  dbi_base; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct uniphier_pcie_priv {int /*<<< orphan*/  phy; int /*<<< orphan*/  rst; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; TYPE_1__ pci; } ;
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct uniphier_pcie_priv* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pci_remap_cfg_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  devm_phy_optional_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_reset_control_get_shared (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dw_pcie_ops ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct uniphier_pcie_priv*) ; 
 int uniphier_add_pcie_port (struct uniphier_pcie_priv*,struct platform_device*) ; 
 int uniphier_pcie_host_enable (struct uniphier_pcie_priv*) ; 

__attribute__((used)) static int uniphier_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct uniphier_pcie_priv *priv;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->pci.dev = dev;
	priv->pci.ops = &dw_pcie_ops;

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	priv->pci.dbi_base = devm_pci_remap_cfg_resource(dev, res);
	if (IS_ERR(priv->pci.dbi_base))
		return PTR_ERR(priv->pci.dbi_base);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "link");
	priv->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	priv->rst = devm_reset_control_get_shared(dev, NULL);
	if (IS_ERR(priv->rst))
		return PTR_ERR(priv->rst);

	priv->phy = devm_phy_optional_get(dev, "pcie-phy");
	if (IS_ERR(priv->phy))
		return PTR_ERR(priv->phy);

	platform_set_drvdata(pdev, priv);

	ret = uniphier_pcie_host_enable(priv);
	if (ret)
		return ret;

	return uniphier_add_pcie_port(priv, pdev);
}