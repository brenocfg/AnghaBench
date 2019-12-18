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
struct xcan_priv {int (* read_reg ) (struct xcan_priv*,int /*<<< orphan*/ ) ;int tx_head; int tx_max; int tx_tail; int /*<<< orphan*/  tx_lock; int /*<<< orphan*/  (* write_reg ) (struct xcan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  XCAN_ICR_OFFSET ; 
 int /*<<< orphan*/  XCAN_IXR_TXFEMP_MASK ; 
 int /*<<< orphan*/  XCAN_SR_OFFSET ; 
 int XCAN_SR_TXFLL_MASK ; 
 int /*<<< orphan*/  XCAN_TXFIFO_OFFSET ; 
 int /*<<< orphan*/  can_put_echo_skb (struct sk_buff*,struct net_device*,int) ; 
 struct xcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct xcan_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct xcan_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xcan_write_frame (struct xcan_priv*,struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xcan_start_xmit_fifo(struct sk_buff *skb, struct net_device *ndev)
{
	struct xcan_priv *priv = netdev_priv(ndev);
	unsigned long flags;

	/* Check if the TX buffer is full */
	if (unlikely(priv->read_reg(priv, XCAN_SR_OFFSET) &
			XCAN_SR_TXFLL_MASK))
		return -ENOSPC;

	can_put_echo_skb(skb, ndev, priv->tx_head % priv->tx_max);

	spin_lock_irqsave(&priv->tx_lock, flags);

	priv->tx_head++;

	xcan_write_frame(priv, skb, XCAN_TXFIFO_OFFSET);

	/* Clear TX-FIFO-empty interrupt for xcan_tx_interrupt() */
	if (priv->tx_max > 1)
		priv->write_reg(priv, XCAN_ICR_OFFSET, XCAN_IXR_TXFEMP_MASK);

	/* Check if the TX buffer is full */
	if ((priv->tx_head - priv->tx_tail) == priv->tx_max)
		netif_stop_queue(ndev);

	spin_unlock_irqrestore(&priv->tx_lock, flags);

	return 0;
}