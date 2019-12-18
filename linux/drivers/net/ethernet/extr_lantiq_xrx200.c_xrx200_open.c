#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  napi; } ;
struct TYPE_3__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  napi; } ;
struct xrx200_priv {TYPE_2__ chan_rx; TYPE_1__ chan_tx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ltq_dma_enable_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ltq_dma_open (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct xrx200_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  xrx200_flush_dma (TYPE_2__*) ; 

__attribute__((used)) static int xrx200_open(struct net_device *net_dev)
{
	struct xrx200_priv *priv = netdev_priv(net_dev);

	napi_enable(&priv->chan_tx.napi);
	ltq_dma_open(&priv->chan_tx.dma);
	ltq_dma_enable_irq(&priv->chan_tx.dma);

	napi_enable(&priv->chan_rx.napi);
	ltq_dma_open(&priv->chan_rx.dma);
	/* The boot loader does not always deactivate the receiving of frames
	 * on the ports and then some packets queue up in the PPE buffers.
	 * They already passed the PMAC so they do not have the tags
	 * configured here. Read the these packets here and drop them.
	 * The HW should have written them into memory after 10us
	 */
	usleep_range(20, 40);
	xrx200_flush_dma(&priv->chan_rx);
	ltq_dma_enable_irq(&priv->chan_rx.dma);

	netif_wake_queue(net_dev);

	return 0;
}