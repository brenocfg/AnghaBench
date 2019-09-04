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
struct sk_buff {int dummy; } ;
struct qlcnic_adapter {int flags; int /*<<< orphan*/  fdb_mac_learn; } ;
struct netlink_callback {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int QLCNIC_ESWITCH_ENABLED ; 
 int ndo_dflt_fdb_dump (struct sk_buff*,struct netlink_callback*,struct net_device*,struct net_device*,int*) ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_sriov_check (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_fdb_dump(struct sk_buff *skb, struct netlink_callback *ncb,
			struct net_device *netdev,
			struct net_device *filter_dev, int *idx)
{
	struct qlcnic_adapter *adapter = netdev_priv(netdev);
	int err = 0;

	if (!adapter->fdb_mac_learn)
		return ndo_dflt_fdb_dump(skb, ncb, netdev, filter_dev, idx);

	if ((adapter->flags & QLCNIC_ESWITCH_ENABLED) ||
	    qlcnic_sriov_check(adapter))
		err = ndo_dflt_fdb_dump(skb, ncb, netdev, filter_dev, idx);

	return err;
}