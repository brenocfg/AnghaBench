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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
struct sk_buff {int /*<<< orphan*/  ip_summed; } ;
struct TYPE_4__ {int /*<<< orphan*/  csum_err; } ;
struct ixgbevf_ring {TYPE_2__ rx_stats; TYPE_1__* netdev; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  IXGBE_RXDADV_ERR_IPE ; 
 int /*<<< orphan*/  IXGBE_RXDADV_ERR_TCPE ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_IPCS ; 
 int /*<<< orphan*/  IXGBE_RXD_STAT_L4CS ; 
 int NETIF_F_RXCSUM ; 
 scalar_t__ ixgbevf_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void ixgbevf_rx_checksum(struct ixgbevf_ring *ring,
				       union ixgbe_adv_rx_desc *rx_desc,
				       struct sk_buff *skb)
{
	skb_checksum_none_assert(skb);

	/* Rx csum disabled */
	if (!(ring->netdev->features & NETIF_F_RXCSUM))
		return;

	/* if IP and error */
	if (ixgbevf_test_staterr(rx_desc, IXGBE_RXD_STAT_IPCS) &&
	    ixgbevf_test_staterr(rx_desc, IXGBE_RXDADV_ERR_IPE)) {
		ring->rx_stats.csum_err++;
		return;
	}

	if (!ixgbevf_test_staterr(rx_desc, IXGBE_RXD_STAT_L4CS))
		return;

	if (ixgbevf_test_staterr(rx_desc, IXGBE_RXDADV_ERR_TCPE)) {
		ring->rx_stats.csum_err++;
		return;
	}

	/* It must be a TCP or UDP packet with a valid checksum */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
}