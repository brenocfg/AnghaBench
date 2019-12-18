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
struct phy_device {scalar_t__ autoneg; scalar_t__ pause; scalar_t__ asym_pause; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int linkmode_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *phy_pause_str(struct phy_device *phydev)
{
	bool local_pause, local_asym_pause;

	if (phydev->autoneg == AUTONEG_DISABLE)
		goto no_pause;

	local_pause = linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
					phydev->advertising);
	local_asym_pause = linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
					     phydev->advertising);

	if (local_pause && phydev->pause)
		return "rx/tx";

	if (local_asym_pause && phydev->asym_pause) {
		if (local_pause)
			return "rx";
		if (phydev->pause)
			return "tx";
	}

no_pause:
	return "off";
}