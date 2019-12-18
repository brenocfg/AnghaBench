#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct netsec_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  freq; int /*<<< orphan*/  phy_np; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_mdio_parse_addr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netsec_of_probe(struct platform_device *pdev,
			   struct netsec_priv *priv, u32 *phy_addr)
{
	priv->phy_np = of_parse_phandle(pdev->dev.of_node, "phy-handle", 0);
	if (!priv->phy_np) {
		dev_err(&pdev->dev, "missing required property 'phy-handle'\n");
		return -EINVAL;
	}

	*phy_addr = of_mdio_parse_addr(&pdev->dev, priv->phy_np);

	priv->clk = devm_clk_get(&pdev->dev, NULL); /* get by 'phy_ref_clk' */
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev, "phy_ref_clk not found\n");
		return PTR_ERR(priv->clk);
	}
	priv->freq = clk_get_rate(priv->clk);

	return 0;
}