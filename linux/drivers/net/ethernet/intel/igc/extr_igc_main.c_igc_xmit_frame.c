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
struct sk_buff {int len; } ;
struct net_device {int dummy; } ;
struct igc_adapter {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  igc_tx_queue_mapping (struct igc_adapter*,struct sk_buff*) ; 
 int /*<<< orphan*/  igc_xmit_frame_ring (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_padto (struct sk_buff*,int) ; 

__attribute__((used)) static netdev_tx_t igc_xmit_frame(struct sk_buff *skb,
				  struct net_device *netdev)
{
	struct igc_adapter *adapter = netdev_priv(netdev);

	/* The minimum packet size with TCTL.PSP set is 17 so pad the skb
	 * in order to meet this minimum size requirement.
	 */
	if (skb->len < 17) {
		if (skb_padto(skb, 17))
			return NETDEV_TX_OK;
		skb->len = 17;
	}

	return igc_xmit_frame_ring(skb, igc_tx_queue_mapping(adapter, skb));
}