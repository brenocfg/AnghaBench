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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int wolopts; } ;
struct dmfe_board_info {int wol_mode; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGICSECURE ; 
 int WAKE_MCAST ; 
 int WAKE_UCAST ; 
 struct dmfe_board_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dmfe_ethtool_set_wol(struct net_device *dev,
				struct ethtool_wolinfo *wolinfo)
{
	struct dmfe_board_info *db = netdev_priv(dev);

	if (wolinfo->wolopts & (WAKE_UCAST | WAKE_MCAST | WAKE_BCAST |
		   		WAKE_ARP | WAKE_MAGICSECURE))
		   return -EOPNOTSUPP;

	db->wol_mode = wolinfo->wolopts;
	return 0;
}