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
struct uniphier_u3ssphy_priv {int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  clk_parent_gio; int /*<<< orphan*/  rst_parent; TYPE_1__* data; int /*<<< orphan*/  rst_parent_gio; } ;
struct phy {int dummy; } ;
struct TYPE_2__ {int nparams; int /*<<< orphan*/ * param; scalar_t__ is_legacy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct uniphier_u3ssphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_u3ssphy_set_param (struct uniphier_u3ssphy_priv*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uniphier_u3ssphy_init(struct phy *phy)
{
	struct uniphier_u3ssphy_priv *priv = phy_get_drvdata(phy);
	int i, ret;

	ret = clk_prepare_enable(priv->clk_parent);
	if (ret)
		return ret;

	ret = clk_prepare_enable(priv->clk_parent_gio);
	if (ret)
		goto out_clk_disable;

	ret = reset_control_deassert(priv->rst_parent);
	if (ret)
		goto out_clk_gio_disable;

	ret = reset_control_deassert(priv->rst_parent_gio);
	if (ret)
		goto out_rst_assert;

	if (priv->data->is_legacy)
		return 0;

	for (i = 0; i < priv->data->nparams; i++)
		uniphier_u3ssphy_set_param(priv, &priv->data->param[i]);

	return 0;

out_rst_assert:
	reset_control_assert(priv->rst_parent);
out_clk_gio_disable:
	clk_disable_unprepare(priv->clk_parent_gio);
out_clk_disable:
	clk_disable_unprepare(priv->clk_parent);

	return ret;
}