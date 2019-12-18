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
struct ixgbe_fwd_adapter {int pool; } ;
struct ixgbe_adapter {int num_rx_pools; int /*<<< orphan*/  netdev; int /*<<< orphan*/  fwd_bitmask; } ;

/* Variables and functions */
 int find_first_zero_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kfree (struct ixgbe_fwd_adapter*) ; 
 struct ixgbe_fwd_adapter* macvlan_accel_priv (struct net_device*) ; 
 int /*<<< orphan*/  macvlan_release_l2fw_offload (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_set_sb_channel (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_unbind_sb_channel (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  netif_is_macvlan (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ixgbe_reassign_macvlan_pool(struct net_device *vdev, void *data)
{
	struct ixgbe_adapter *adapter = data;
	struct ixgbe_fwd_adapter *accel;
	int pool;

	/* we only care about macvlans... */
	if (!netif_is_macvlan(vdev))
		return 0;

	/* that have hardware offload enabled... */
	accel = macvlan_accel_priv(vdev);
	if (!accel)
		return 0;

	/* If we can relocate to a different bit do so */
	pool = find_first_zero_bit(adapter->fwd_bitmask, adapter->num_rx_pools);
	if (pool < adapter->num_rx_pools) {
		set_bit(pool, adapter->fwd_bitmask);
		accel->pool = pool;
		return 0;
	}

	/* if we cannot find a free pool then disable the offload */
	netdev_err(vdev, "L2FW offload disabled due to lack of queue resources\n");
	macvlan_release_l2fw_offload(vdev);

	/* unbind the queues and drop the subordinate channel config */
	netdev_unbind_sb_channel(adapter->netdev, vdev);
	netdev_set_sb_channel(vdev, 0);

	kfree(accel);

	return 0;
}