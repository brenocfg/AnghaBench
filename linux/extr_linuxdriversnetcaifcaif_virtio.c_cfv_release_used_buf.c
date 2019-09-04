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
struct virtqueue {scalar_t__ num_free; TYPE_1__* vdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_flow_on; } ;
struct cfv_info {scalar_t__ watermark_tx; scalar_t__ reserved_mem; struct virtqueue* vq_tx; TYPE_2__ stats; int /*<<< orphan*/  ndev; int /*<<< orphan*/  reserved_size; scalar_t__ genpool; int /*<<< orphan*/  tx_lock; } ;
struct buf_info {int dummy; } ;
struct TYPE_3__ {struct cfv_info* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  free_buf_info (struct cfv_info*,struct buf_info*) ; 
 scalar_t__ gen_pool_alloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_all_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  virtqueue_disable_cb (struct virtqueue*) ; 
 struct buf_info* virtqueue_get_buf (struct virtqueue*,unsigned int*) ; 
 int virtqueue_get_vring_size (struct virtqueue*) ; 

__attribute__((used)) static void cfv_release_used_buf(struct virtqueue *vq_tx)
{
	struct cfv_info *cfv = vq_tx->vdev->priv;
	unsigned long flags;

	BUG_ON(vq_tx != cfv->vq_tx);

	for (;;) {
		unsigned int len;
		struct buf_info *buf_info;

		/* Get used buffer from used ring to recycle used descriptors */
		spin_lock_irqsave(&cfv->tx_lock, flags);
		buf_info = virtqueue_get_buf(vq_tx, &len);
		spin_unlock_irqrestore(&cfv->tx_lock, flags);

		/* Stop looping if there are no more buffers to free */
		if (!buf_info)
			break;

		free_buf_info(cfv, buf_info);

		/* watermark_tx indicates if we previously stopped the tx
		 * queues. If we have enough free stots in the virtio ring,
		 * re-establish memory reserved and open up tx queues.
		 */
		if (cfv->vq_tx->num_free <= cfv->watermark_tx)
			continue;

		/* Re-establish memory reserve */
		if (cfv->reserved_mem == 0 && cfv->genpool)
			cfv->reserved_mem =
				gen_pool_alloc(cfv->genpool,
					       cfv->reserved_size);

		/* Open up the tx queues */
		if (cfv->reserved_mem) {
			cfv->watermark_tx =
				virtqueue_get_vring_size(cfv->vq_tx);
			netif_tx_wake_all_queues(cfv->ndev);
			/* Buffers are recycled in cfv_netdev_tx, so
			 * disable notifications when queues are opened.
			 */
			virtqueue_disable_cb(cfv->vq_tx);
			++cfv->stats.tx_flow_on;
		} else {
			/* if no memory reserve, wait for more free slots */
			WARN_ON(cfv->watermark_tx >
			       virtqueue_get_vring_size(cfv->vq_tx));
			cfv->watermark_tx +=
				virtqueue_get_vring_size(cfv->vq_tx) / 4;
		}
	}
}