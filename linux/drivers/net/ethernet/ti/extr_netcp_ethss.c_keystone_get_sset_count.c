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
struct netcp_intf {int dummy; } ;
struct net_device {int dummy; } ;
struct gbe_priv {int num_et_stats; } ;
struct gbe_intf {struct gbe_priv* gbe_dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 struct gbe_intf* keystone_get_intf_data (struct netcp_intf*) ; 
 struct netcp_intf* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int keystone_get_sset_count(struct net_device *ndev, int stringset)
{
	struct netcp_intf *netcp = netdev_priv(ndev);
	struct gbe_intf *gbe_intf;
	struct gbe_priv *gbe_dev;

	gbe_intf = keystone_get_intf_data(netcp);
	if (!gbe_intf)
		return -EINVAL;
	gbe_dev = gbe_intf->gbe_dev;

	switch (stringset) {
	case ETH_SS_TEST:
		return 0;
	case ETH_SS_STATS:
		return gbe_dev->num_et_stats;
	default:
		return -EINVAL;
	}
}