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
struct phy_device {int /*<<< orphan*/  supported; int /*<<< orphan*/  advertising; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int /*<<< orphan*/  linkmode_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linkmode_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void phy_set_sym_pause(struct phy_device *phydev, bool rx, bool tx,
		       bool autoneg)
{
	linkmode_clear_bit(ETHTOOL_LINK_MODE_Pause_BIT, phydev->supported);

	if (rx && tx && autoneg)
		linkmode_set_bit(ETHTOOL_LINK_MODE_Pause_BIT,
				 phydev->supported);

	linkmode_copy(phydev->advertising, phydev->supported);
}