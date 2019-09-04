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
typedef  int u32 ;
typedef  size_t u16 ;
struct sk_buff {int len; int /*<<< orphan*/  end; } ;
struct netdev_queue {int dummy; } ;
struct ena_tx_buffer {int num_of_bufs; scalar_t__ tx_descs; struct ena_com_buf* bufs; scalar_t__ last_jiffies; struct sk_buff* skb; } ;
struct TYPE_2__ {int /*<<< orphan*/  queue_wakeup; } ;
struct ena_ring {size_t next_to_clean; size_t* free_tx_ids; int per_napi_packets; int /*<<< orphan*/  per_napi_bytes; int /*<<< orphan*/  syncp; TYPE_1__ tx_stats; int /*<<< orphan*/  ena_com_io_sq; int /*<<< orphan*/  qid; int /*<<< orphan*/  netdev; int /*<<< orphan*/  adapter; int /*<<< orphan*/  ena_com_io_cq; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  dev; struct ena_tx_buffer* tx_buffer_info; } ;
struct ena_com_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t ENA_TX_RING_IDX_NEXT (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ ENA_TX_WAKEUP_THRESH ; 
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ena_com_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len (struct ena_com_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_com_comp_ack (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ena_com_sq_empty_space (int /*<<< orphan*/ ) ; 
 int ena_com_tx_comp_req_id_get (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  ena_com_update_dev_comp_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (int) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (struct netdev_queue*,int,int) ; 
 int /*<<< orphan*/  netif_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 
 int /*<<< orphan*/  paddr ; 
 int /*<<< orphan*/  prefetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  tx_done ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int validate_tx_req_id (struct ena_ring*,size_t) ; 

__attribute__((used)) static int ena_clean_tx_irq(struct ena_ring *tx_ring, u32 budget)
{
	struct netdev_queue *txq;
	bool above_thresh;
	u32 tx_bytes = 0;
	u32 total_done = 0;
	u16 next_to_clean;
	u16 req_id;
	int tx_pkts = 0;
	int rc;

	next_to_clean = tx_ring->next_to_clean;
	txq = netdev_get_tx_queue(tx_ring->netdev, tx_ring->qid);

	while (tx_pkts < budget) {
		struct ena_tx_buffer *tx_info;
		struct sk_buff *skb;
		struct ena_com_buf *ena_buf;
		int i, nr_frags;

		rc = ena_com_tx_comp_req_id_get(tx_ring->ena_com_io_cq,
						&req_id);
		if (rc)
			break;

		rc = validate_tx_req_id(tx_ring, req_id);
		if (rc)
			break;

		tx_info = &tx_ring->tx_buffer_info[req_id];
		skb = tx_info->skb;

		/* prefetch skb_end_pointer() to speedup skb_shinfo(skb) */
		prefetch(&skb->end);

		tx_info->skb = NULL;
		tx_info->last_jiffies = 0;

		if (likely(tx_info->num_of_bufs != 0)) {
			ena_buf = tx_info->bufs;

			dma_unmap_single(tx_ring->dev,
					 dma_unmap_addr(ena_buf, paddr),
					 dma_unmap_len(ena_buf, len),
					 DMA_TO_DEVICE);

			/* unmap remaining mapped pages */
			nr_frags = tx_info->num_of_bufs - 1;
			for (i = 0; i < nr_frags; i++) {
				ena_buf++;
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(ena_buf, paddr),
					       dma_unmap_len(ena_buf, len),
					       DMA_TO_DEVICE);
			}
		}

		netif_dbg(tx_ring->adapter, tx_done, tx_ring->netdev,
			  "tx_poll: q %d skb %p completed\n", tx_ring->qid,
			  skb);

		tx_bytes += skb->len;
		dev_kfree_skb(skb);
		tx_pkts++;
		total_done += tx_info->tx_descs;

		tx_ring->free_tx_ids[next_to_clean] = req_id;
		next_to_clean = ENA_TX_RING_IDX_NEXT(next_to_clean,
						     tx_ring->ring_size);
	}

	tx_ring->next_to_clean = next_to_clean;
	ena_com_comp_ack(tx_ring->ena_com_io_sq, total_done);
	ena_com_update_dev_comp_head(tx_ring->ena_com_io_cq);

	netdev_tx_completed_queue(txq, tx_pkts, tx_bytes);

	netif_dbg(tx_ring->adapter, tx_done, tx_ring->netdev,
		  "tx_poll: q %d done. total pkts: %d\n",
		  tx_ring->qid, tx_pkts);

	/* need to make the rings circular update visible to
	 * ena_start_xmit() before checking for netif_queue_stopped().
	 */
	smp_mb();

	above_thresh = ena_com_sq_empty_space(tx_ring->ena_com_io_sq) >
		ENA_TX_WAKEUP_THRESH;
	if (unlikely(netif_tx_queue_stopped(txq) && above_thresh)) {
		__netif_tx_lock(txq, smp_processor_id());
		above_thresh = ena_com_sq_empty_space(tx_ring->ena_com_io_sq) >
			ENA_TX_WAKEUP_THRESH;
		if (netif_tx_queue_stopped(txq) && above_thresh) {
			netif_tx_wake_queue(txq);
			u64_stats_update_begin(&tx_ring->syncp);
			tx_ring->tx_stats.queue_wakeup++;
			u64_stats_update_end(&tx_ring->syncp);
		}
		__netif_tx_unlock(txq);
	}

	tx_ring->per_napi_bytes += tx_bytes;
	tx_ring->per_napi_packets += tx_pkts;

	return tx_pkts;
}