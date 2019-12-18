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
typedef  int /*<<< orphan*/  u32 ;
struct phy {int /*<<< orphan*/  dev; } ;
struct mixel_dphy_priv {int /*<<< orphan*/  phy_ref_clk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPHY_LOCK ; 
 int /*<<< orphan*/  DPHY_PD_DPHY ; 
 int /*<<< orphan*/  DPHY_PD_PLL ; 
 int /*<<< orphan*/  PLL_LOCK_SLEEP ; 
 int /*<<< orphan*/  PLL_LOCK_TIMEOUT ; 
 int /*<<< orphan*/  PWR_ON ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct mixel_dphy_priv* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  phy_write (struct phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_read_poll_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mixel_dphy_power_on(struct phy *phy)
{
	struct mixel_dphy_priv *priv = phy_get_drvdata(phy);
	u32 locked;
	int ret;

	ret = clk_prepare_enable(priv->phy_ref_clk);
	if (ret < 0)
		return ret;

	phy_write(phy, PWR_ON, DPHY_PD_PLL);
	ret = regmap_read_poll_timeout(priv->regmap, DPHY_LOCK, locked,
				       locked, PLL_LOCK_SLEEP,
				       PLL_LOCK_TIMEOUT);
	if (ret < 0) {
		dev_err(&phy->dev, "Could not get DPHY lock (%d)!\n", ret);
		goto clock_disable;
	}
	phy_write(phy, PWR_ON, DPHY_PD_DPHY);

	return 0;
clock_disable:
	clk_disable_unprepare(priv->phy_ref_clk);
	return ret;
}