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
struct ipoib_tx_buf {int /*<<< orphan*/  skb; } ;
struct ipoib_dev_priv {int tx_tail; int tx_head; int /*<<< orphan*/  flags; } ;
struct ipoib_cm_tx {int tx_tail; struct ipoib_tx_buf* tx_ring; TYPE_1__* qp; int /*<<< orphan*/  dev; scalar_t__ tx_head; scalar_t__ id; } ;
struct TYPE_2__ {int /*<<< orphan*/  qp_num; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  IPOIB_FLAG_ADMIN_UP ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_destroy_cm_id (scalar_t__) ; 
 int /*<<< orphan*/  ib_destroy_qp (TYPE_1__*) ; 
 int /*<<< orphan*/  ipoib_dbg (struct ipoib_dev_priv*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ipoib_dma_unmap_tx (struct ipoib_dev_priv*,struct ipoib_tx_buf*) ; 
 struct ipoib_dev_priv* ipoib_priv (int /*<<< orphan*/ ) ; 
 int ipoib_sendq_size ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,scalar_t__) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree (struct ipoib_cm_tx*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  vfree (struct ipoib_tx_buf*) ; 

__attribute__((used)) static void ipoib_cm_tx_destroy(struct ipoib_cm_tx *p)
{
	struct ipoib_dev_priv *priv = ipoib_priv(p->dev);
	struct ipoib_tx_buf *tx_req;
	unsigned long begin;

	ipoib_dbg(priv, "Destroy active connection 0x%x head 0x%x tail 0x%x\n",
		  p->qp ? p->qp->qp_num : 0, p->tx_head, p->tx_tail);

	if (p->id)
		ib_destroy_cm_id(p->id);

	if (p->tx_ring) {
		/* Wait for all sends to complete */
		begin = jiffies;
		while ((int) p->tx_tail - (int) p->tx_head < 0) {
			if (time_after(jiffies, begin + 5 * HZ)) {
				ipoib_warn(priv, "timing out; %d sends not completed\n",
					   p->tx_head - p->tx_tail);
				goto timeout;
			}

			usleep_range(1000, 2000);
		}
	}

timeout:

	while ((int) p->tx_tail - (int) p->tx_head < 0) {
		tx_req = &p->tx_ring[p->tx_tail & (ipoib_sendq_size - 1)];
		ipoib_dma_unmap_tx(priv, tx_req);
		dev_kfree_skb_any(tx_req->skb);
		netif_tx_lock_bh(p->dev);
		++p->tx_tail;
		++priv->tx_tail;
		if (unlikely(priv->tx_head - priv->tx_tail == ipoib_sendq_size >> 1) &&
		    netif_queue_stopped(p->dev) &&
		    test_bit(IPOIB_FLAG_ADMIN_UP, &priv->flags))
			netif_wake_queue(p->dev);
		netif_tx_unlock_bh(p->dev);
	}

	if (p->qp)
		ib_destroy_qp(p->qp);

	vfree(p->tx_ring);
	kfree(p);
}