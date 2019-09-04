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
struct ethtool_wolinfo {int supported; int /*<<< orphan*/  wolopts; } ;
struct dmfe_board_info {int /*<<< orphan*/  wol_mode; } ;

/* Variables and functions */
 int WAKE_MAGIC ; 
 int WAKE_PHY ; 
 struct dmfe_board_info* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void dmfe_ethtool_get_wol(struct net_device *dev,
				 struct ethtool_wolinfo *wolinfo)
{
	struct dmfe_board_info *db = netdev_priv(dev);

	wolinfo->supported = WAKE_PHY | WAKE_MAGIC;
	wolinfo->wolopts = db->wol_mode;
}