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
struct mvebu_comphy_priv {int /*<<< orphan*/ * axi_clk; int /*<<< orphan*/ * mg_core_clk; int /*<<< orphan*/ * mg_domain_clk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 void* devm_clk_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int mvebu_comphy_init_clks(struct mvebu_comphy_priv *priv)
{
	int ret;

	priv->mg_domain_clk = devm_clk_get(priv->dev, "mg_clk");
	if (IS_ERR(priv->mg_domain_clk))
		return PTR_ERR(priv->mg_domain_clk);

	ret = clk_prepare_enable(priv->mg_domain_clk);
	if (ret < 0)
		return ret;

	priv->mg_core_clk = devm_clk_get(priv->dev, "mg_core_clk");
	if (IS_ERR(priv->mg_core_clk)) {
		ret = PTR_ERR(priv->mg_core_clk);
		goto dis_mg_domain_clk;
	}

	ret = clk_prepare_enable(priv->mg_core_clk);
	if (ret < 0)
		goto dis_mg_domain_clk;

	priv->axi_clk = devm_clk_get(priv->dev, "axi_clk");
	if (IS_ERR(priv->axi_clk)) {
		ret = PTR_ERR(priv->axi_clk);
		goto dis_mg_core_clk;
	}

	ret = clk_prepare_enable(priv->axi_clk);
	if (ret < 0)
		goto dis_mg_core_clk;

	return 0;

dis_mg_core_clk:
	clk_disable_unprepare(priv->mg_core_clk);

dis_mg_domain_clk:
	clk_disable_unprepare(priv->mg_domain_clk);

	priv->mg_domain_clk = NULL;
	priv->mg_core_clk = NULL;
	priv->axi_clk = NULL;

	return ret;
}