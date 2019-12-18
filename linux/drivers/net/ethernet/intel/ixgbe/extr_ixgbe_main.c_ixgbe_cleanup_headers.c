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
typedef  union ixgbe_adv_rx_desc {int dummy; } ixgbe_adv_rx_desc ;
struct sk_buff {int dummy; } ;
struct net_device {int features; } ;
struct ixgbe_ring {struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  IXGBE_RXDADV_ERR_FRAME_ERR_MASK ; 
 int NETIF_F_RXALL ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ eth_skb_pad (struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_pull_tail (struct ixgbe_ring*,struct sk_buff*) ; 
 scalar_t__ ixgbe_rx_is_fcoe (struct ixgbe_ring*,union ixgbe_adv_rx_desc*) ; 
 scalar_t__ ixgbe_test_staterr (union ixgbe_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_headlen (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

bool ixgbe_cleanup_headers(struct ixgbe_ring *rx_ring,
			   union ixgbe_adv_rx_desc *rx_desc,
			   struct sk_buff *skb)
{
	struct net_device *netdev = rx_ring->netdev;

	/* XDP packets use error pointer so abort at this point */
	if (IS_ERR(skb))
		return true;

	/* Verify netdev is present, and that packet does not have any
	 * errors that would be unacceptable to the netdev.
	 */
	if (!netdev ||
	    (unlikely(ixgbe_test_staterr(rx_desc,
					 IXGBE_RXDADV_ERR_FRAME_ERR_MASK) &&
	     !(netdev->features & NETIF_F_RXALL)))) {
		dev_kfree_skb_any(skb);
		return true;
	}

	/* place header in linear portion of buffer */
	if (!skb_headlen(skb))
		ixgbe_pull_tail(rx_ring, skb);

#ifdef IXGBE_FCOE
	/* do not attempt to pad FCoE Frames as this will disrupt DDP */
	if (ixgbe_rx_is_fcoe(rx_ring, rx_desc))
		return false;

#endif
	/* if eth_skb_pad returns an error the skb was freed */
	if (eth_skb_pad(skb))
		return true;

	return false;
}