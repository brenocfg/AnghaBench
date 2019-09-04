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
struct dsa_switch {struct b53_device* priv; } ;
struct b53_device {int dummy; } ;

/* Variables and functions */
 int ETH_SS_PHY_STATS ; 
 int ETH_SS_STATS ; 
 int b53_get_mib_size (struct b53_device*) ; 
 struct phy_device* b53_get_phy_device (struct dsa_switch*,int) ; 
 int phy_ethtool_get_sset_count (struct phy_device*) ; 

int b53_get_sset_count(struct dsa_switch *ds, int port, int sset)
{
	struct b53_device *dev = ds->priv;
	struct phy_device *phydev;

	if (sset == ETH_SS_STATS) {
		return b53_get_mib_size(dev);
	} else if (sset == ETH_SS_PHY_STATS) {
		phydev = b53_get_phy_device(ds, port);
		if (!phydev)
			return 0;

		return phy_ethtool_get_sset_count(phydev);
	}

	return 0;
}