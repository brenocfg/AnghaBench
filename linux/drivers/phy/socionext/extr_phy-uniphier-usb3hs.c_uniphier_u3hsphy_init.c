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
typedef  scalar_t__ u32 ;
struct uniphier_u3hsphy_priv {int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  rst_parent; TYPE_1__* data; scalar_t__ base; } ;
struct phy {int dummy; } ;
struct TYPE_2__ {int nparams; int /*<<< orphan*/ * param; scalar_t__ config1; scalar_t__ config0; } ;

/* Variables and functions */
 scalar_t__ HSPHY_CFG0 ; 
 scalar_t__ HSPHY_CFG1 ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct uniphier_u3hsphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_u3hsphy_set_param (struct uniphier_u3hsphy_priv*,int /*<<< orphan*/ *) ; 
 int uniphier_u3hsphy_update_config (struct uniphier_u3hsphy_priv*,scalar_t__*) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int uniphier_u3hsphy_init(struct phy *phy)
{
	struct uniphier_u3hsphy_priv *priv = phy_get_drvdata(phy);
	u32 config0, config1;
	int i, ret;

	ret = clk_prepare_enable(priv->clk_parent);
	if (ret)
		return ret;

	ret = reset_control_deassert(priv->rst_parent);
	if (ret)
		goto out_clk_disable;

	if (!priv->data->config0 && !priv->data->config1)
		return 0;

	config0 = priv->data->config0;
	config1 = priv->data->config1;

	ret = uniphier_u3hsphy_update_config(priv, &config0);
	if (ret)
		goto out_rst_assert;

	writel(config0, priv->base + HSPHY_CFG0);
	writel(config1, priv->base + HSPHY_CFG1);

	for (i = 0; i < priv->data->nparams; i++)
		uniphier_u3hsphy_set_param(priv, &priv->data->param[i]);

	return 0;

out_rst_assert:
	reset_control_assert(priv->rst_parent);
out_clk_disable:
	clk_disable_unprepare(priv->clk_parent);

	return ret;
}