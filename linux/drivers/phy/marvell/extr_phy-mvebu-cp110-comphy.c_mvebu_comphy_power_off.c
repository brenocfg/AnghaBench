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
struct mvebu_comphy_priv {int /*<<< orphan*/  cp_phys; } ;
struct mvebu_comphy_lane {int /*<<< orphan*/  id; struct mvebu_comphy_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPHY_SIP_POWER_OFF ; 
 int mvebu_comphy_power_off_legacy (struct phy*) ; 
 int mvebu_comphy_smc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mvebu_comphy_lane* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int mvebu_comphy_power_off(struct phy *phy)
{
	struct mvebu_comphy_lane *lane = phy_get_drvdata(phy);
	struct mvebu_comphy_priv *priv = lane->priv;
	int ret;

	ret = mvebu_comphy_smc(COMPHY_SIP_POWER_OFF, priv->cp_phys,
			       lane->id, 0);
	if (!ret)
		return ret;

	/* Fallback to Linux's implementation */
	return mvebu_comphy_power_off_legacy(phy);
}