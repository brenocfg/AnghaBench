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
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct ipoib_tx_buf {TYPE_2__* skb; } ;
struct ipoib_qp_state_validate {int /*<<< orphan*/  work; struct ipoib_dev_priv* priv; } ;
struct ipoib_dev_priv {unsigned int tx_tail; unsigned int tx_head; int /*<<< orphan*/  wq; int /*<<< orphan*/  flags; struct ipoib_tx_buf* tx_ring; } ;
struct ib_wc {unsigned int wr_id; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IB_WC_SUCCESS ; 
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPOIB_FLAG_ADMIN_UP ; 
 int /*<<< orphan*/  dev_kfree_skb_any (TYPE_2__*) ; 
 int /*<<< orphan*/  ipoib_dbg_data (struct ipoib_dev_priv*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipoib_dma_unmap_tx (struct ipoib_dev_priv*,struct ipoib_tx_buf*) ; 
 struct ipoib_dev_priv* ipoib_priv (struct net_device*) ; 
 int /*<<< orphan*/  ipoib_qp_state_validate_work ; 
 unsigned int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,unsigned int,unsigned int,...) ; 
 struct ipoib_qp_state_validate* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void ipoib_ib_handle_tx_wc(struct net_device *dev, struct ib_wc *wc)
{
	struct ipoib_dev_priv *priv = ipoib_priv(dev);
	unsigned int wr_id = wc->wr_id;
	struct ipoib_tx_buf *tx_req;

	ipoib_dbg_data(priv, "send completion: id %d, status: %d\n",
		       wr_id, wc->status);

	if (unlikely(wr_id >= ipoib_sendq_size)) {
		ipoib_warn(priv, "send completion event with wrid %d (> %d)\n",
			   wr_id, ipoib_sendq_size);
		return;
	}

	tx_req = &priv->tx_ring[wr_id];

	ipoib_dma_unmap_tx(priv, tx_req);

	++dev->stats.tx_packets;
	dev->stats.tx_bytes += tx_req->skb->len;

	dev_kfree_skb_any(tx_req->skb);

	++priv->tx_tail;

	if (unlikely(netif_queue_stopped(dev) &&
		     ((priv->tx_head - priv->tx_tail) <= ipoib_sendq_size >> 1) &&
		     test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags)))
		netif_wake_queue(dev);

	if (wc->status != IB_WC_SUCCESS &&
	    wc->status != IB_WC_WR_FLUSH_ERR) {
		struct ipoib_qp_state_validate *qp_work;
		ipoib_warn(priv,
			   "failed send event (status=%d, wrid=%d vend_err %#x)\n",
			   wc->status, wr_id, wc->vendor_err);
		qp_work = kzalloc(sizeof(*qp_work), GFP_ATOMIC);
		if (!qp_work)
			return;

		INIT_WORK(&qp_work->work, ipoib_qp_state_validate_work);
		qp_work->priv = priv;
		queue_work(priv->wq, &qp_work->work);
	}
}