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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ixgbe_adapter {int flags; int /*<<< orphan*/  bridge_mode; } ;

/* Variables and functions */
 int IXGBE_FLAG_SRIOV_ENABLED ; 
 int ndo_dflt_bridge_getlink (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ixgbe_ndo_bridge_getlink(struct sk_buff *skb, u32 pid, u32 seq,
				    struct net_device *dev,
				    u32 filter_mask, int nlflags)
{
	struct ixgbe_adapter *adapter = netdev_priv(dev);

	if (!(adapter->flags & IXGBE_FLAG_SRIOV_ENABLED))
		return 0;

	return ndo_dflt_bridge_getlink(skb, pid, seq, dev,
				       adapter->bridge_mode, 0, 0, nlflags,
				       filter_mask, NULL);
}