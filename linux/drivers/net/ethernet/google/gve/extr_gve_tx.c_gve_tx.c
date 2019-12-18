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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct net_device {int dummy; } ;
struct gve_tx_ring {int req; int /*<<< orphan*/  q_resources; int /*<<< orphan*/  netdev_txq; } ;
struct TYPE_3__ {size_t num_queues; } ;
struct gve_priv {TYPE_2__* pdev; struct gve_tx_ring* tx; TYPE_1__ tx_cfg; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  gve_maybe_stop_tx (struct gve_tx_ring*,struct sk_buff*) ; 
 int gve_tx_add_skb (struct gve_tx_ring*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gve_tx_put_doorbell (struct gve_priv*,int /*<<< orphan*/ ,int) ; 
 struct gve_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netdev_xmit_more () ; 
 int /*<<< orphan*/  netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

netdev_tx_t gve_tx(struct sk_buff *skb, struct net_device *dev)
{
	struct gve_priv *priv = netdev_priv(dev);
	struct gve_tx_ring *tx;
	int nsegs;

	WARN(skb_get_queue_mapping(skb) > priv->tx_cfg.num_queues,
	     "skb queue index out of range");
	tx = &priv->tx[skb_get_queue_mapping(skb)];
	if (unlikely(gve_maybe_stop_tx(tx, skb))) {
		/* We need to ring the txq doorbell -- we have stopped the Tx
		 * queue for want of resources, but prior calls to gve_tx()
		 * may have added descriptors without ringing the doorbell.
		 */

		/* Ensure tx descs from a prior gve_tx are visible before
		 * ringing doorbell.
		 */
		dma_wmb();
		gve_tx_put_doorbell(priv, tx->q_resources, tx->req);
		return NETDEV_TX_BUSY;
	}
	nsegs = gve_tx_add_skb(tx, skb, &priv->pdev->dev);

	netdev_tx_sent_queue(tx->netdev_txq, skb->len);
	skb_tx_timestamp(skb);

	/* give packets to NIC */
	tx->req += nsegs;

	if (!netif_xmit_stopped(tx->netdev_txq) && netdev_xmit_more())
		return NETDEV_TX_OK;

	/* Ensure tx descs are visible before ringing doorbell */
	dma_wmb();
	gve_tx_put_doorbell(priv, tx->q_resources, tx->req);
	return NETDEV_TX_OK;
}