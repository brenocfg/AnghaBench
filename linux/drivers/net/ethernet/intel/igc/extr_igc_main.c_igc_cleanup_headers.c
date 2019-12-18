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
typedef  union igc_adv_rx_desc {int dummy; } igc_adv_rx_desc ;
struct sk_buff {int dummy; } ;
struct net_device {int features; } ;
struct igc_ring {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IGC_RXDEXT_ERR_FRAME_ERR_MASK ; 
 int NETIF_F_RXALL ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ eth_skb_pad (struct sk_buff*) ; 
 int /*<<< orphan*/  igc_test_staterr (union igc_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool igc_cleanup_headers(struct igc_ring *rx_ring,
				union igc_adv_rx_desc *rx_desc,
				struct sk_buff *skb)
{
	if (unlikely((igc_test_staterr(rx_desc,
				       IGC_RXDEXT_ERR_FRAME_ERR_MASK)))) {
		struct net_device *netdev = rx_ring->netdev;

		if (!(netdev->features & NETIF_F_RXALL)) {
			dev_kfree_skb_any(skb);
			return true;
		}
	}

	/* if eth_skb_pad returns an error the skb was freed */
	if (eth_skb_pad(skb))
		return true;

	return false;
}