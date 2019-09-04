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
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct enet_cb {int dummy; } ;
struct bcmgenet_priv {int num_tx_bds; struct enet_cb* tx_cbs; struct enet_cb* rx_cbs; TYPE_3__* tx_rings; int /*<<< orphan*/  dev; TYPE_2__* hw_params; TYPE_1__* pdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
struct TYPE_5__ {int tx_queues; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t DESC_INDEX ; 
 int /*<<< orphan*/  bcmgenet_fini_rx_napi (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_fini_tx_napi (struct bcmgenet_priv*) ; 
 int /*<<< orphan*/  bcmgenet_free_rx_buffers (struct bcmgenet_priv*) ; 
 struct sk_buff* bcmgenet_free_tx_cb (int /*<<< orphan*/ *,struct enet_cb*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct enet_cb*) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (struct netdev_queue*) ; 

__attribute__((used)) static void bcmgenet_fini_dma(struct bcmgenet_priv *priv)
{
	struct netdev_queue *txq;
	struct sk_buff *skb;
	struct enet_cb *cb;
	int i;

	bcmgenet_fini_rx_napi(priv);
	bcmgenet_fini_tx_napi(priv);

	for (i = 0; i < priv->num_tx_bds; i++) {
		cb = priv->tx_cbs + i;
		skb = bcmgenet_free_tx_cb(&priv->pdev->dev, cb);
		if (skb)
			dev_kfree_skb(skb);
	}

	for (i = 0; i < priv->hw_params->tx_queues; i++) {
		txq = netdev_get_tx_queue(priv->dev, priv->tx_rings[i].queue);
		netdev_tx_reset_queue(txq);
	}

	txq = netdev_get_tx_queue(priv->dev, priv->tx_rings[DESC_INDEX].queue);
	netdev_tx_reset_queue(txq);

	bcmgenet_free_rx_buffers(priv);
	kfree(priv->rx_cbs);
	kfree(priv->tx_cbs);
}