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
struct virt_wifi_netdev_priv {int /*<<< orphan*/  lowerdev; int /*<<< orphan*/  tx_failed; int /*<<< orphan*/  is_connected; int /*<<< orphan*/  tx_packets; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NET_XMIT_DROP ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 struct virt_wifi_netdev_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t virt_wifi_start_xmit(struct sk_buff *skb,
					struct net_device *dev)
{
	struct virt_wifi_netdev_priv *priv = netdev_priv(dev);

	priv->tx_packets++;
	if (!priv->is_connected) {
		priv->tx_failed++;
		return NET_XMIT_DROP;
	}

	skb->dev = priv->lowerdev;
	return dev_queue_xmit(skb);
}