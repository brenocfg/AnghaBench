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
struct net_device {int /*<<< orphan*/  irq; } ;
struct TYPE_2__ {int /*<<< orphan*/ * echo_skb; scalar_t__ echo_skb_max; int /*<<< orphan*/  state; } ;
struct grcan_priv {int closing; int /*<<< orphan*/  txdlc; int /*<<< orphan*/  echo_skb; TYPE_1__ can; int /*<<< orphan*/  lock; int /*<<< orphan*/  rr_timer; int /*<<< orphan*/  hang_timer; scalar_t__ need_txbug_workaround; int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAN_STATE_STOPPED ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  grcan_free_dma_buffers (struct net_device*) ; 
 int /*<<< orphan*/  grcan_stop_hardware (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct grcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grcan_close(struct net_device *dev)
{
	struct grcan_priv *priv = netdev_priv(dev);
	unsigned long flags;

	napi_disable(&priv->napi);

	spin_lock_irqsave(&priv->lock, flags);

	priv->closing = true;
	if (priv->need_txbug_workaround) {
		del_timer_sync(&priv->hang_timer);
		del_timer_sync(&priv->rr_timer);
	}
	netif_stop_queue(dev);
	grcan_stop_hardware(dev);
	priv->can.state = CAN_STATE_STOPPED;

	spin_unlock_irqrestore(&priv->lock, flags);

	free_irq(dev->irq, dev);
	close_candev(dev);

	grcan_free_dma_buffers(dev);
	priv->can.echo_skb_max = 0;
	priv->can.echo_skb = NULL;
	kfree(priv->echo_skb);
	kfree(priv->txdlc);

	return 0;
}