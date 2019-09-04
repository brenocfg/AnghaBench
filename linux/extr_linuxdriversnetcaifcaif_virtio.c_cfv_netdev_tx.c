#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct scatterlist {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  tx_no_mem; int /*<<< orphan*/  tx_full_ring; } ;
struct cfv_info {int watermark_tx; TYPE_7__* ndev; int /*<<< orphan*/  tx_lock; TYPE_3__* vq_tx; scalar_t__ reserved_mem; int /*<<< orphan*/  reserved_size; scalar_t__ genpool; TYPE_1__ stats; } ;
struct buf_info {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_12__ {TYPE_2__ stats; } ;
struct TYPE_11__ {scalar_t__ num_free; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NETDEV_TX_OK ; 
 struct buf_info* cfv_alloc_and_copy_to_shm (struct cfv_info*,struct sk_buff*,struct scatterlist*) ; 
 int /*<<< orphan*/  cfv_release_used_buf (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  free_buf_info (struct cfv_info*,struct buf_info*) ; 
 int /*<<< orphan*/  gen_pool_free (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct cfv_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_7__*,char*,...) ; 
 int /*<<< orphan*/  netif_tx_stop_all_queues (struct net_device*) ; 
 scalar_t__ num_present_cpus () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int virtqueue_add_outbuf (TYPE_3__*,struct scatterlist*,int,struct buf_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virtqueue_enable_cb (TYPE_3__*) ; 
 int virtqueue_get_vring_size (TYPE_3__*) ; 
 int /*<<< orphan*/  virtqueue_kick (TYPE_3__*) ; 

__attribute__((used)) static int cfv_netdev_tx(struct sk_buff *skb, struct net_device *netdev)
{
	struct cfv_info *cfv = netdev_priv(netdev);
	struct buf_info *buf_info;
	struct scatterlist sg;
	unsigned long flags;
	bool flow_off = false;
	int ret;

	/* garbage collect released buffers */
	cfv_release_used_buf(cfv->vq_tx);
	spin_lock_irqsave(&cfv->tx_lock, flags);

	/* Flow-off check takes into account number of cpus to make sure
	 * virtqueue will not be overfilled in any possible smp conditions.
	 *
	 * Flow-on is triggered when sufficient buffers are freed
	 */
	if (unlikely(cfv->vq_tx->num_free <= num_present_cpus())) {
		flow_off = true;
		cfv->stats.tx_full_ring++;
	}

	/* If we run out of memory, we release the memory reserve and retry
	 * allocation.
	 */
	buf_info = cfv_alloc_and_copy_to_shm(cfv, skb, &sg);
	if (unlikely(!buf_info)) {
		cfv->stats.tx_no_mem++;
		flow_off = true;

		if (cfv->reserved_mem && cfv->genpool) {
			gen_pool_free(cfv->genpool,  cfv->reserved_mem,
				      cfv->reserved_size);
			cfv->reserved_mem = 0;
			buf_info = cfv_alloc_and_copy_to_shm(cfv, skb, &sg);
		}
	}

	if (unlikely(flow_off)) {
		/* Turn flow on when a 1/4 of the descriptors are released */
		cfv->watermark_tx = virtqueue_get_vring_size(cfv->vq_tx) / 4;
		/* Enable notifications of recycled TX buffers */
		virtqueue_enable_cb(cfv->vq_tx);
		netif_tx_stop_all_queues(netdev);
	}

	if (unlikely(!buf_info)) {
		/* If the memory reserve does it's job, this shouldn't happen */
		netdev_warn(cfv->ndev, "Out of gen_pool memory\n");
		goto err;
	}

	ret = virtqueue_add_outbuf(cfv->vq_tx, &sg, 1, buf_info, GFP_ATOMIC);
	if (unlikely((ret < 0))) {
		/* If flow control works, this shouldn't happen */
		netdev_warn(cfv->ndev, "Failed adding buffer to TX vring:%d\n",
			    ret);
		goto err;
	}

	/* update netdev statistics */
	cfv->ndev->stats.tx_packets++;
	cfv->ndev->stats.tx_bytes += skb->len;
	spin_unlock_irqrestore(&cfv->tx_lock, flags);

	/* tell the remote processor it has a pending message to read */
	virtqueue_kick(cfv->vq_tx);

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
err:
	spin_unlock_irqrestore(&cfv->tx_lock, flags);
	cfv->ndev->stats.tx_dropped++;
	free_buf_info(cfv, buf_info);
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}