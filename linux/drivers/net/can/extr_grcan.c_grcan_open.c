#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  irq; } ;
struct TYPE_6__ {int ctrlmode; void* echo_skb; int /*<<< orphan*/  echo_skb_max; } ;
struct TYPE_4__ {int /*<<< orphan*/  rxsize; int /*<<< orphan*/  txsize; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;
struct grcan_dma {TYPE_2__ tx; } ;
struct grcan_priv {int resetting; int closing; void* echo_skb; void* txdlc; int /*<<< orphan*/  lock; TYPE_3__ can; int /*<<< orphan*/  napi; TYPE_1__ config; struct grcan_dma dma; } ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  close_candev (struct net_device*) ; 
 int grcan_allocate_dma_buffers (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grcan_free_dma_buffers (struct net_device*) ; 
 int /*<<< orphan*/  grcan_interrupt ; 
 int /*<<< orphan*/  grcan_start (struct net_device*) ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct grcan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int open_candev (struct net_device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int grcan_open(struct net_device *dev)
{
	struct grcan_priv *priv = netdev_priv(dev);
	struct grcan_dma *dma = &priv->dma;
	unsigned long flags;
	int err;

	/* Allocate memory */
	err = grcan_allocate_dma_buffers(dev, priv->config.txsize,
					 priv->config.rxsize);
	if (err) {
		netdev_err(dev, "could not allocate DMA buffers\n");
		return err;
	}

	priv->echo_skb = kcalloc(dma->tx.size, sizeof(*priv->echo_skb),
				 GFP_KERNEL);
	if (!priv->echo_skb) {
		err = -ENOMEM;
		goto exit_free_dma_buffers;
	}
	priv->can.echo_skb_max = dma->tx.size;
	priv->can.echo_skb = priv->echo_skb;

	priv->txdlc = kcalloc(dma->tx.size, sizeof(*priv->txdlc), GFP_KERNEL);
	if (!priv->txdlc) {
		err = -ENOMEM;
		goto exit_free_echo_skb;
	}

	/* Get can device up */
	err = open_candev(dev);
	if (err)
		goto exit_free_txdlc;

	err = request_irq(dev->irq, grcan_interrupt, IRQF_SHARED,
			  dev->name, dev);
	if (err)
		goto exit_close_candev;

	spin_lock_irqsave(&priv->lock, flags);

	napi_enable(&priv->napi);
	grcan_start(dev);
	if (!(priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY))
		netif_start_queue(dev);
	priv->resetting = false;
	priv->closing = false;

	spin_unlock_irqrestore(&priv->lock, flags);

	return 0;

exit_close_candev:
	close_candev(dev);
exit_free_txdlc:
	kfree(priv->txdlc);
exit_free_echo_skb:
	kfree(priv->echo_skb);
exit_free_dma_buffers:
	grcan_free_dma_buffers(dev);
	return err;
}