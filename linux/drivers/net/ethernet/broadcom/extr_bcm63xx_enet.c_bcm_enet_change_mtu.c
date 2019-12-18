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
struct net_device {int mtu; } ;
struct bcm_enet_priv {int hw_mtu; int dma_maxburst; int /*<<< orphan*/  rx_skb_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (scalar_t__,int) ; 
 int EBUSY ; 
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ VLAN_ETH_HLEN ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 

__attribute__((used)) static int bcm_enet_change_mtu(struct net_device *dev, int new_mtu)
{
	struct bcm_enet_priv *priv = netdev_priv(dev);
	int actual_mtu = new_mtu;

	if (netif_running(dev))
		return -EBUSY;

	/* add ethernet header + vlan tag size */
	actual_mtu += VLAN_ETH_HLEN;

	/*
	 * setup maximum size before we get overflow mark in
	 * descriptor, note that this will not prevent reception of
	 * big frames, they will be split into multiple buffers
	 * anyway
	 */
	priv->hw_mtu = actual_mtu;

	/*
	 * align rx buffer size to dma burst len, account FCS since
	 * it's appended
	 */
	priv->rx_skb_size = ALIGN(actual_mtu + ETH_FCS_LEN,
				  priv->dma_maxburst * 4);

	dev->mtu = new_mtu;
	return 0;
}