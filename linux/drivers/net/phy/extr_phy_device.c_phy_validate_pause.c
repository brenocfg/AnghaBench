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
struct phy_device {int /*<<< orphan*/  supported; } ;
struct ethtool_pauseparam {scalar_t__ rx_pause; scalar_t__ tx_pause; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Asym_Pause_BIT ; 
 int /*<<< orphan*/  ETHTOOL_LINK_MODE_Pause_BIT ; 
 int /*<<< orphan*/  linkmode_test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool phy_validate_pause(struct phy_device *phydev,
			struct ethtool_pauseparam *pp)
{
	if (!linkmode_test_bit(ETHTOOL_LINK_MODE_Pause_BIT,
			       phydev->supported) && pp->rx_pause)
		return false;

	if (!linkmode_test_bit(ETHTOOL_LINK_MODE_Asym_Pause_BIT,
			       phydev->supported) &&
	    pp->rx_pause != pp->tx_pause)
		return false;

	return true;
}