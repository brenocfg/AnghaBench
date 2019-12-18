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
typedef  int /*<<< orphan*/  u8 ;
struct phy_device {int dummy; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_PHY_DOWNSHIFT 128 
 int bcm_phy_downshift_get (struct phy_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm_omega_get_tunable(struct phy_device *phydev,
				 struct ethtool_tunable *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOL_PHY_DOWNSHIFT:
		return bcm_phy_downshift_get(phydev, (u8 *)data);
	default:
		return -EOPNOTSUPP;
	}
}