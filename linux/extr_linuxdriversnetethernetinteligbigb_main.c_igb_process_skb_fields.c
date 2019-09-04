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
struct TYPE_3__ {int /*<<< orphan*/  vlan; } ;
struct TYPE_4__ {TYPE_1__ upper; } ;
union e1000_adv_rx_desc {TYPE_2__ wb; } ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct net_device {int features; } ;
struct igb_ring {struct net_device* netdev; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  flags; int /*<<< orphan*/  q_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RXDADV_STAT_TS ; 
 int /*<<< orphan*/  E1000_RXDADV_STAT_TSIP ; 
 int /*<<< orphan*/  E1000_RXDEXT_STATERR_LB ; 
 int /*<<< orphan*/  E1000_RXD_STAT_VP ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int /*<<< orphan*/  IGB_RING_FLAG_RX_LB_VLAN_BSWAP ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_ptp_rx_rgtstamp (int /*<<< orphan*/ ,struct sk_buff*) ; 
 int /*<<< orphan*/  igb_rx_checksum (struct igb_ring*,union e1000_adv_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  igb_rx_hash (struct igb_ring*,union e1000_adv_rx_desc*,struct sk_buff*) ; 
 scalar_t__ igb_test_staterr (union e1000_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void igb_process_skb_fields(struct igb_ring *rx_ring,
				   union e1000_adv_rx_desc *rx_desc,
				   struct sk_buff *skb)
{
	struct net_device *dev = rx_ring->netdev;

	igb_rx_hash(rx_ring, rx_desc, skb);

	igb_rx_checksum(rx_ring, rx_desc, skb);

	if (igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TS) &&
	    !igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TSIP))
		igb_ptp_rx_rgtstamp(rx_ring->q_vector, skb);

	if ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    igb_test_staterr(rx_desc, E1000_RXD_STAT_VP)) {
		u16 vid;

		if (igb_test_staterr(rx_desc, E1000_RXDEXT_STATERR_LB) &&
		    test_bit(IGB_RING_FLAG_RX_LB_VLAN_BSWAP, &rx_ring->flags))
			vid = be16_to_cpu(rx_desc->wb.upper.vlan);
		else
			vid = le16_to_cpu(rx_desc->wb.upper.vlan);

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	}

	skb_record_rx_queue(skb, rx_ring->queue_index);

	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
}