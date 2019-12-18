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
typedef  union fm10k_rx_desc {int dummy; } fm10k_rx_desc ;
struct sk_buff {int encapsulation; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_4__ {int /*<<< orphan*/  csum_good; int /*<<< orphan*/  csum_err; } ;
struct fm10k_ring {TYPE_2__ rx_stats; TYPE_1__* netdev; } ;
struct TYPE_3__ {int features; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int FM10K_RXD_STATUS_IPE ; 
 int FM10K_RXD_STATUS_IPE2 ; 
 int FM10K_RXD_STATUS_L4CS ; 
 int FM10K_RXD_STATUS_L4CS2 ; 
 int FM10K_RXD_STATUS_L4E ; 
 int FM10K_RXD_STATUS_L4E2 ; 
 int NETIF_F_RXCSUM ; 
 scalar_t__ fm10k_test_staterr (union fm10k_rx_desc*,int) ; 
 int /*<<< orphan*/  skb_checksum_none_assert (struct sk_buff*) ; 

__attribute__((used)) static inline void fm10k_rx_checksum(struct fm10k_ring *ring,
				     union fm10k_rx_desc *rx_desc,
				     struct sk_buff *skb)
{
	skb_checksum_none_assert(skb);

	/* Rx checksum disabled via ethtool */
	if (!(ring->netdev->features & NETIF_F_RXCSUM))
		return;

	/* TCP/UDP checksum error bit is set */
	if (fm10k_test_staterr(rx_desc,
			       FM10K_RXD_STATUS_L4E |
			       FM10K_RXD_STATUS_L4E2 |
			       FM10K_RXD_STATUS_IPE |
			       FM10K_RXD_STATUS_IPE2)) {
		ring->rx_stats.csum_err++;
		return;
	}

	/* It must be a TCP or UDP packet with a valid checksum */
	if (fm10k_test_staterr(rx_desc, FM10K_RXD_STATUS_L4CS2))
		skb->encapsulation = true;
	else if (!fm10k_test_staterr(rx_desc, FM10K_RXD_STATUS_L4CS))
		return;

	skb->ip_summed = CHECKSUM_UNNECESSARY;

	ring->rx_stats.csum_good++;
}