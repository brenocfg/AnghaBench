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
struct sk_buff {size_t queue_mapping; } ;
struct net_device {int dummy; } ;
struct ice_vsi {struct ice_ring** tx_rings; } ;
struct ice_ring {int dummy; } ;
struct ice_netdev_priv {struct ice_vsi* vsi; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_MIN_TX_LEN ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  ice_xmit_frame_ring (struct sk_buff*,struct ice_ring*) ; 
 struct ice_netdev_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ skb_put_padto (struct sk_buff*,int /*<<< orphan*/ ) ; 

netdev_tx_t ice_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct ice_netdev_priv *np = netdev_priv(netdev);
	struct ice_vsi *vsi = np->vsi;
	struct ice_ring *tx_ring;

	tx_ring = vsi->tx_rings[skb->queue_mapping];

	/* hardware can't handle really short frames, hardware padding works
	 * beyond this point
	 */
	if (skb_put_padto(skb, ICE_MIN_TX_LEN))
		return NETDEV_TX_OK;

	return ice_xmit_frame_ring(skb, tx_ring);
}