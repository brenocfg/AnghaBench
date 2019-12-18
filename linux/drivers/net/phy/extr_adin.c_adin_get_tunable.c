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
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_PHY_DOWNSHIFT 129 
#define  ETHTOOL_PHY_EDPD 128 
 int adin_get_downshift (struct phy_device*,void*) ; 
 int adin_get_edpd (struct phy_device*,void*) ; 

__attribute__((used)) static int adin_get_tunable(struct phy_device *phydev,
			    struct ethtool_tunable *tuna, void *data)
{
	switch (tuna->id) {
	case ETHTOOL_PHY_DOWNSHIFT:
		return adin_get_downshift(phydev, data);
	case ETHTOOL_PHY_EDPD:
		return adin_get_edpd(phydev, data);
	default:
		return -EOPNOTSUPP;
	}
}