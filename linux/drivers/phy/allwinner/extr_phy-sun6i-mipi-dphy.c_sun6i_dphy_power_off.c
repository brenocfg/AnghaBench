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
struct sun6i_dphy {int /*<<< orphan*/  regs; } ;
struct phy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN6I_DPHY_ANA1_REG ; 
 int /*<<< orphan*/  SUN6I_DPHY_ANA1_REG_VTTMODE ; 
 struct sun6i_dphy* phy_get_drvdata (struct phy*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sun6i_dphy_power_off(struct phy *phy)
{
	struct sun6i_dphy *dphy = phy_get_drvdata(phy);

	regmap_update_bits(dphy->regs, SUN6I_DPHY_ANA1_REG,
			   SUN6I_DPHY_ANA1_REG_VTTMODE, 0);

	return 0;
}