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
struct uniphier_u3ssphy_priv {int /*<<< orphan*/  clk_parent; int /*<<< orphan*/  clk_parent_gio; int /*<<< orphan*/  rst_parent; int /*<<< orphan*/  rst_parent_gio; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct uniphier_u3ssphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_u3ssphy_exit(struct phy *phy)
{
	struct uniphier_u3ssphy_priv *priv = phy_get_drvdata(phy);

	reset_control_assert(priv->rst_parent_gio);
	reset_control_assert(priv->rst_parent);
	clk_disable_unprepare(priv->clk_parent_gio);
	clk_disable_unprepare(priv->clk_parent);

	return 0;
}