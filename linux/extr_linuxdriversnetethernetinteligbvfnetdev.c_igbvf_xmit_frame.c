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
struct net_device {int dummy; } ;
struct igbvf_ring {int dummy; } ;
struct igbvf_adapter {struct igbvf_ring* tx_ring; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  igbvf_xmit_frame_ring_adv (struct sk_buff*,struct net_device*,struct igbvf_ring*) ; 
 struct igbvf_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t igbvf_xmit_frame(struct sk_buff *skb,
				    struct net_device *netdev)
{
	struct igbvf_adapter *adapter = netdev_priv(netdev);
	struct igbvf_ring *tx_ring;

	if (test_bit(__IGBVF_DOWN, &adapter->state)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	tx_ring = &adapter->tx_ring[0];

	return igbvf_xmit_frame_ring_adv(skb, netdev, tx_ring);
}