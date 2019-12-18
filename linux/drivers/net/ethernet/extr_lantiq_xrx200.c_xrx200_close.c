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
struct xrx200_priv {TYPE_2__ chan_tx; TYPE_1__ chan_rx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ltq_dma_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct xrx200_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static int xrx200_close(struct net_device *net_dev)
{
	struct xrx200_priv *priv = netdev_priv(net_dev);

	netif_stop_queue(net_dev);

	napi_disable(&priv->chan_rx.napi);
	ltq_dma_close(&priv->chan_rx.dma);

	napi_disable(&priv->chan_tx.napi);
	ltq_dma_close(&priv->chan_tx.dma);

	return 0;
}