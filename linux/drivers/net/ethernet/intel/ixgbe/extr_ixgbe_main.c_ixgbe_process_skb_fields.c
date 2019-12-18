#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  vlan; } ;
struct TYPE_8__ {TYPE_3__ upper; } ;
union ixgbe_adv_rx_desc {TYPE_4__ wb; } ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int /*<<< orphan*/  protocol; scalar_t__ len; } ;
struct net_device {int features; } ;
struct ixgbe_ring {int /*<<< orphan*/  queue_index; TYPE_2__* q_vector; struct net_device* netdev; } ;
struct TYPE_6__ {TYPE_1__* adapter; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int IXGBE_FLAG_RX_HWTSTAMP_ENABLED ; 
 int /*<<< orphan*/  IXGBE_RXDADV_STAT_SECP ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_VP ; 
 int NETIF_F_HW_VLAN_CTAG_RX ; 
 int /*<<< orphan*/  __vlan_hwaccel_put_tag (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ipsec_rx (struct ixgbe_ring*,union ixgbe_adv_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_ptp_rx_hwtstamp (struct ixgbe_ring*,union ixgbe_adv_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_rx_checksum (struct ixgbe_ring*,union ixgbe_adv_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_rx_hash (struct ixgbe_ring*,union ixgbe_adv_rx_desc*,struct sk_buff*) ; 
 scalar_t__ ixgbe_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_update_rsc_stats (struct ixgbe_ring*,struct sk_buff*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macvlan_count_rx (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 scalar_t__ netif_is_ixgbe (struct net_device*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

void ixgbe_process_skb_fields(struct ixgbe_ring *rx_ring,
			      union ixgbe_adv_rx_desc *rx_desc,
			      struct sk_buff *skb)
{
	struct net_device *dev = rx_ring->netdev;
	u32 flags = rx_ring->q_vector->adapter->flags;

	ixgbe_update_rsc_stats(rx_ring, skb);

	ixgbe_rx_hash(rx_ring, rx_desc, skb);

	ixgbe_rx_checksum(rx_ring, rx_desc, skb);

	if (unlikely(flags & IXGBE_FLAG_RX_HWTSTAMP_ENABLED))
		ixgbe_ptp_rx_hwtstamp(rx_ring, rx_desc, skb);

	if ((dev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_VP)) {
		u16 vid = le16_to_cpu(rx_desc->wb.upper.vlan);
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vid);
	}

	if (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_STAT_SECP))
		ixgbe_ipsec_rx(rx_ring, rx_desc, skb);

	/* record Rx queue, or update MACVLAN statistics */
	if (netif_is_ixgbe(dev))
		skb_record_rx_queue(skb, rx_ring->queue_index);
	else
		macvlan_count_rx(netdev_priv(dev), skb->len + ETH_HLEN, true,
				 false);

	skb->protocol = eth_type_trans(skb, dev);
}