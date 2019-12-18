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
struct phy {int dummy; } ;
struct mixel_dphy_priv {int /*<<< orphan*/  phy_ref_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_PD_DPHY ; 
 int /*<<< orphan*/  DPHY_PD_PLL ; 
 int /*<<< orphan*/  PWR_OFF ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct mixel_dphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  phy_write (struct phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mixel_dphy_power_off(struct phy *phy)
{
	struct mixel_dphy_priv *priv = phy_get_drvdata(phy);

	phy_write(phy, PWR_OFF, DPHY_PD_PLL);
	phy_write(phy, PWR_OFF, DPHY_PD_DPHY);

	clk_disable_unprepare(priv->phy_ref_clk);

	return 0;
}