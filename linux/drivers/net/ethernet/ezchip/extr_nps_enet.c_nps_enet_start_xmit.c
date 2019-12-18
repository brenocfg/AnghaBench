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
struct sk_buff {int dummy; } ;
struct nps_enet_priv {struct sk_buff* tx_skb; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct nps_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  nps_enet_send_frame (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t nps_enet_start_xmit(struct sk_buff *skb,
				       struct net_device *ndev)
{
	struct nps_enet_priv *priv = netdev_priv(ndev);

	/* This driver handles one frame at a time  */
	netif_stop_queue(ndev);

	priv->tx_skb = skb;

	/* make sure tx_skb is actually written to the memory
	 * before the HW is informed and the IRQ is fired.
	 */
	wmb();

	nps_enet_send_frame(ndev, skb);

	return NETDEV_TX_OK;
}