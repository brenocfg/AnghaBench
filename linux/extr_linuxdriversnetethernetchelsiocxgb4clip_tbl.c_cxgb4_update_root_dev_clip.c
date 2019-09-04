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

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int VLAN_N_VID ; 
 struct net_device* __vlan_find_dev_deep_rcu (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int cxgb4_update_dev_clip (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 struct net_device* netdev_master_upper_dev_get_rcu (struct net_device*) ; 

int cxgb4_update_root_dev_clip(struct net_device *dev)
{
	struct net_device *root_dev = NULL;
	int i, ret = 0;

	/* First populate the real net device's IPv6 addresses */
	ret = cxgb4_update_dev_clip(dev, dev);
	if (ret)
		return ret;

	/* Parse all bond and vlan devices layered on top of the physical dev */
	root_dev = netdev_master_upper_dev_get_rcu(dev);
	if (root_dev) {
		ret = cxgb4_update_dev_clip(root_dev, dev);
		if (ret)
			return ret;
	}

	for (i = 0; i < VLAN_N_VID; i++) {
		root_dev = __vlan_find_dev_deep_rcu(dev, htons(ETH_P_8021Q), i);
		if (!root_dev)
			continue;

		ret = cxgb4_update_dev_clip(root_dev, dev);
		if (ret)
			break;
	}

	return ret;
}