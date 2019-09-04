#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int pkt_info; } ;
struct TYPE_8__ {TYPE_1__ hs_rss; } ;
struct TYPE_9__ {TYPE_2__ lo_dword; } ;
struct TYPE_10__ {TYPE_3__ lower; } ;
union ixgbe_adv_rx_desc {TYPE_4__ wb; } ;
struct sk_buff {int encapsulation; int csum_level; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_12__ {int /*<<< orphan*/  csum_err; } ;
struct ixgbe_ring {TYPE_6__ rx_stats; int /*<<< orphan*/  state; TYPE_5__* netdev; } ;
typedef  int __le16 ;
struct TYPE_11__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  IXGBE_RXDADV_ERR_IPE ; 
 int /*<<< orphan*/  IXGBE_RXDADV_ERR_OUTERIPER ; 
 int /*<<< orphan*/  IXGBE_RXDADV_ERR_TCPE ; 
 int /*<<< orphan*/  IXGBE_RXDADV_PKTTYPE_UDP ; 
 int /*<<< orphan*/  IXGBE_RXDADV_PKTTYPE_VXLAN ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_IPCS ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_L4CS ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_OUTERIPCS ; 
 int NETIF_F_RXCSUM ; 
 int /*<<< orphan*/  __IXGBE_RX_CSUM_UDP_ZERO_ERR ; 
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ixgbe_rx_checksum(struct ixgbe_ring *ring,
				     union ixgbe_adv_rx_desc *rx_desc,
				     struct sk_buff *skb)
{
	__le16 pkt_info = rx_desc->wb.lower.lo_dword.hs_rss.pkt_info;
	bool encap_pkt = false;

	skb_checksum_none_assert(skb);

	/* Rx csum disabled */
	if (!(ring->netdev->features & NETIF_F_RXCSUM))
		return;

	/* check for VXLAN and Geneve packets */
	if (pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_VXLAN)) {
		encap_pkt = true;
		skb->encapsulation = 1;
	}

	/* if IP and error */
	if (ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_IPCS) &&
	    ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_IPE)) {
		ring->rx_stats.csum_err++;
		return;
	}

	if (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_L4CS))
		return;

	if (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_TCPE)) {
		/*
		 * 82599 errata, UDP frames with a 0 checksum can be marked as
		 * checksum errors.
		 */
		if ((pkt_info & cpu_to_le16(IXGBE_RXDADV_PKTTYPE_UDP)) &&
		    test_bit(__IXGBE_RX_CSUM_UDP_ZERO_ERR, &ring->state))
			return;

		ring->rx_stats.csum_err++;
		return;
	}

	/* It must be a TCP or UDP packet with a valid checksum */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	if (encap_pkt) {
		if (!ixgbe_test_staterr(rx_desc, IXGBE_RXD_STAT_OUTERIPCS))
			return;

		if (ixgbe_test_staterr(rx_desc, IXGBE_RXDADV_ERR_OUTERIPER)) {
			skb->ip_summed = CHECKSUM_NONE;
			return;
		}
		/* If we checked the outer header let the stack know */
		skb->csum_level = 1;
	}
}