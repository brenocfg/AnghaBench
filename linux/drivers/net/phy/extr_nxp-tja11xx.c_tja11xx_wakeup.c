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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_ECTRL ; 
 int MII_ECTRL_POWER_MODE_MASK ; 
#define  MII_ECTRL_POWER_MODE_NORMAL 130 
#define  MII_ECTRL_POWER_MODE_NO_CHANGE 129 
#define  MII_ECTRL_POWER_MODE_STANDBY 128 
 int /*<<< orphan*/  MII_ECTRL_WAKE_REQUEST ; 
 int /*<<< orphan*/  MII_GENSTAT ; 
 int MII_GENSTAT_PLL_LOCKED ; 
 int phy_clear_bits (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phy_modify (struct phy_device*,int /*<<< orphan*/ ,int,int const) ; 
 int phy_modify_check (struct phy_device*,int /*<<< orphan*/ ,int,int const) ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_set_bits (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tja11xx_enable_link_control (struct phy_device*) ; 

__attribute__((used)) static int tja11xx_wakeup(struct phy_device *phydev)
{
	int ret;

	ret = phy_read(phydev, MII_ECTRL);
	if (ret < 0)
		return ret;

	switch (ret & MII_ECTRL_POWER_MODE_MASK) {
	case MII_ECTRL_POWER_MODE_NO_CHANGE:
		break;
	case MII_ECTRL_POWER_MODE_NORMAL:
		ret = phy_set_bits(phydev, MII_ECTRL, MII_ECTRL_WAKE_REQUEST);
		if (ret)
			return ret;

		ret = phy_clear_bits(phydev, MII_ECTRL, MII_ECTRL_WAKE_REQUEST);
		if (ret)
			return ret;
		break;
	case MII_ECTRL_POWER_MODE_STANDBY:
		ret = phy_modify_check(phydev, MII_ECTRL,
				       MII_ECTRL_POWER_MODE_MASK,
				       MII_ECTRL_POWER_MODE_STANDBY);
		if (ret)
			return ret;

		ret = phy_modify(phydev, MII_ECTRL, MII_ECTRL_POWER_MODE_MASK,
				 MII_ECTRL_POWER_MODE_NORMAL);
		if (ret)
			return ret;

		ret = phy_modify_check(phydev, MII_GENSTAT,
				       MII_GENSTAT_PLL_LOCKED,
				       MII_GENSTAT_PLL_LOCKED);
		if (ret)
			return ret;

		return tja11xx_enable_link_control(phydev);
	default:
		break;
	}

	return 0;
}