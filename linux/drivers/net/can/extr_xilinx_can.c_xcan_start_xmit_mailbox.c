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
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  tx_head; } ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  XCAN_TRR_OFFSET ; 
 int /*<<< orphan*/  XCAN_TXMSG_FRAME_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XCAN_TX_MAILBOX_IDX ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int /*<<< orphan*/ ) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xcan_priv*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xcan_write_frame (struct xcan_priv*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xcan_start_xmit_mailbox(struct sk_buff *skb, struct net_device *ndev)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	unsigned long flags;

	if (unlikely(priv->read_reg(priv, XCAN_TRR_OFFSET) &
		     BIT(XCAN_TX_MAILBOX_IDX)))
		return -ENOSPC;

	can_put_echo_skb(skb, ndev, 0);

	spin_lock_irqsave(&priv->tx_lock, flags);

	priv->tx_head++;

	xcan_write_frame(priv, skb,
			 XCAN_TXMSG_FRAME_OFFSET(XCAN_TX_MAILBOX_IDX));

	/* Mark buffer as ready for transmit */
	priv->write_reg(priv, XCAN_TRR_OFFSET, BIT(XCAN_TX_MAILBOX_IDX));

	netif_stop_queue(ndev);

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	return 0;
}