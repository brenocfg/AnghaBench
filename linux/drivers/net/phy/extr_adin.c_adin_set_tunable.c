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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {int dummy; } ;
struct ethtool_tunable {int id; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  ETHTOOL_PHY_DOWNSHIFT 129 
#define  ETHTOOL_PHY_EDPD 128 
 int adin_set_downshift (struct phy_device*,int /*<<< orphan*/  const) ; 
 int adin_set_edpd (struct phy_device*,int /*<<< orphan*/  const) ; 

__attribute__((used)) static int adin_set_tunable(struct phy_device *phydev,
			    struct ethtool_tunable *tuna, const void *data)
{
	switch (tuna->id) {
	case ETHTOOL_PHY_DOWNSHIFT:
		return adin_set_downshift(phydev, *(const u8 *)data);
	case ETHTOOL_PHY_EDPD:
		return adin_set_edpd(phydev, *(const u16 *)data);
	default:
		return -EOPNOTSUPP;
	}
}