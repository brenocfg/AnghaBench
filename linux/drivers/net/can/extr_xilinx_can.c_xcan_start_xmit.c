#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int flags; } ;
struct xcan_priv {TYPE_1__ devtype; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int XCAN_FLAG_TX_MAILBOXES ; 
 scalar_t__ can_dropped_invalid_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int xcan_start_xmit_fifo (struct sk_buff*,struct net_device*) ; 
 int xcan_start_xmit_mailbox (struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t xcan_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	int ret;

	if (can_dropped_invalid_skb(ndev, skb))
		return NETDEV_TX_OK;

	if (priv->devtype.flags & XCAN_FLAG_TX_MAILBOXES)
		ret = xcan_start_xmit_mailbox(skb, ndev);
	else
		ret = xcan_start_xmit_fifo(skb, ndev);

	if (ret < 0) {
		netdev_err(ndev, "BUG!, TX full when queue awake!\n");
		netif_stop_queue(ndev);
		return NETDEV_TX_BUSY;
	}

	return NETDEV_TX_OK;
}