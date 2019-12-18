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
struct uniphier_pciephy_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct uniphier_pciephy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uniphier_pciephy_assert (struct uniphier_pciephy_priv*) ; 

__attribute__((used)) static int uniphier_pciephy_exit(struct phy *phy)
{
	struct uniphier_pciephy_priv *priv = phy_get_drvdata(phy);

	uniphier_pciephy_assert(priv);
	reset_control_assert(priv->rst);
	clk_disable_unprepare(priv->clk);

	return 0;
}