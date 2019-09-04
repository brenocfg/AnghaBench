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
struct txbd8 {int dummy; } ;
struct rxbd8 {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct gfar_private {int num_tx_queues; int num_rx_queues; int total_tx_ring_size; int total_rx_ring_size; struct gfar_priv_tx_q** tx_queue; int /*<<< orphan*/  dev; struct gfar_priv_rx_q** rx_queue; } ;
struct gfar_priv_tx_q {int /*<<< orphan*/  tx_bd_dma_base; int /*<<< orphan*/  tx_bd_base; scalar_t__ tx_skbuff; int /*<<< orphan*/  qindex; int /*<<< orphan*/  dev; } ;
struct gfar_priv_rx_q {scalar_t__ rx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_skb_rx_queue (struct gfar_priv_rx_q*) ; 
 int /*<<< orphan*/  free_skb_tx_queue (struct gfar_priv_tx_q*) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_reset_queue (struct netdev_queue*) ; 

__attribute__((used)) static void free_skb_resources(struct gfar_private *priv)
{
	struct gfar_priv_tx_q *tx_queue = NULL;
	struct gfar_priv_rx_q *rx_queue = NULL;
	int i;

	/* Go through all the buffer descriptors and free their data buffers */
	for (i = 0; i < priv->num_tx_queues; i++) {
		struct netdev_queue *txq;

		tx_queue = priv->tx_queue[i];
		txq = netdev_get_tx_queue(tx_queue->dev, tx_queue->qindex);
		if (tx_queue->tx_skbuff)
			free_skb_tx_queue(tx_queue);
		netdev_tx_reset_queue(txq);
	}

	for (i = 0; i < priv->num_rx_queues; i++) {
		rx_queue = priv->rx_queue[i];
		if (rx_queue->rx_buff)
			free_skb_rx_queue(rx_queue);
	}

	dma_free_coherent(priv->dev,
			  sizeof(struct txbd8) * priv->total_tx_ring_size +
			  sizeof(struct rxbd8) * priv->total_rx_ring_size,
			  priv->tx_queue[0]->tx_bd_base,
			  priv->tx_queue[0]->tx_bd_dma_base);
}