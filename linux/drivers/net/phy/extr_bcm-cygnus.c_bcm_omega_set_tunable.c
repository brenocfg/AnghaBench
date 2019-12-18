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
typedef  scalar_t__ u8 ;
struct phy_device {int dummy; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 scalar_t__ DOWNSHIFT_DEV_DISABLE ; 
 int EOPNOTSUPP ; 
#define  ETHTOOL_PHY_DOWNSHIFT 128 
 int bcm_phy_downshift_set (struct phy_device*,scalar_t__) ; 
 int bcm_phy_set_eee (struct phy_device*,int) ; 
 int genphy_restart_aneg (struct phy_device*) ; 

__attribute__((used)) static int bcm_omega_set_tunable(struct phy_device *phydev,
				 struct ethtool_tunable *tuna,
				 const void *data)
{
	u8 count = *(u8 *)data;
	int ret;

	switch (tuna->id) {
	case ETHTOOL_PHY_DOWNSHIFT:
		ret = bcm_phy_downshift_set(phydev, count);
		break;
	default:
		return -EOPNOTSUPP;
	}

	if (ret)
		return ret;

	/* Disable EEE advertisement since this prevents the PHY
	 * from successfully linking up, trigger auto-negotiation restart
	 * to let the MAC decide what to do.
	 */
	ret = bcm_phy_set_eee(phydev, count == DOWNSHIFT_DEV_DISABLE);
	if (ret)
		return ret;

	return genphy_restart_aneg(phydev);
}