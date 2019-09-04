#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {unsigned int next_to_use; TYPE_1__* buffer_info; } ;
struct ixgb_adapter {TYPE_2__ tx_ring; int /*<<< orphan*/  flags; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_3__ {scalar_t__ time_stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_NEEDED ; 
 unsigned int IXGB_TX_FLAGS_CSUM ; 
 unsigned int IXGB_TX_FLAGS_TSO ; 
 unsigned int IXGB_TX_FLAGS_VLAN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __IXGB_DOWN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  ixgb_maybe_stop_tx (struct net_device*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ixgb_tso (struct ixgb_adapter*,struct sk_buff*) ; 
 scalar_t__ ixgb_tx_csum (struct ixgb_adapter*,struct sk_buff*) ; 
 int ixgb_tx_map (struct ixgb_adapter*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  ixgb_tx_queue (struct ixgb_adapter*,int,int,unsigned int) ; 
 scalar_t__ likely (int) ; 
 struct ixgb_adapter* netdev_priv (struct net_device*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t
ixgb_xmit_frame(struct sk_buff *skb, struct net_device *netdev)
{
	struct ixgb_adapter *adapter = netdev_priv(netdev);
	unsigned int first;
	unsigned int tx_flags = 0;
	int vlan_id = 0;
	int count = 0;
	int tso;

	if (test_bit(__IXGB_DOWN, &adapter->flags)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (skb->len <= 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (unlikely(ixgb_maybe_stop_tx(netdev, &adapter->tx_ring,
                     DESC_NEEDED)))
		return NETDEV_TX_BUSY;

	if (skb_vlan_tag_present(skb)) {
		tx_flags |= IXGB_TX_FLAGS_VLAN;
		vlan_id = skb_vlan_tag_get(skb);
	}

	first = adapter->tx_ring.next_to_use;

	tso = ixgb_tso(adapter, skb);
	if (tso < 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (likely(tso))
		tx_flags |= IXGB_TX_FLAGS_TSO;
	else if (ixgb_tx_csum(adapter, skb))
		tx_flags |= IXGB_TX_FLAGS_CSUM;

	count = ixgb_tx_map(adapter, skb, first);

	if (count) {
		ixgb_tx_queue(adapter, count, vlan_id, tx_flags);
		/* Make sure there is space in the ring for the next send. */
		ixgb_maybe_stop_tx(netdev, &adapter->tx_ring, DESC_NEEDED);

	} else {
		dev_kfree_skb_any(skb);
		adapter->tx_ring.buffer_info[first].time_stamp = 0;
		adapter->tx_ring.next_to_use = first;
	}

	return NETDEV_TX_OK;
}