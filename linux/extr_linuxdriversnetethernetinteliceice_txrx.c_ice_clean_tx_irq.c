#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ice_vsi {unsigned int work_lmt; int /*<<< orphan*/  state; } ;
struct ice_tx_desc {int cmd_type_offset_bsz; } ;
struct ice_tx_buf {int /*<<< orphan*/ * skb; scalar_t__ gso_segs; scalar_t__ bytecount; struct ice_tx_desc* next_to_watch; } ;
struct TYPE_8__ {int /*<<< orphan*/  restart_q; } ;
struct TYPE_5__ {unsigned int bytes; unsigned int pkts; } ;
struct ice_ring {size_t next_to_clean; TYPE_4__ tx_stats; int /*<<< orphan*/  q_index; int /*<<< orphan*/  netdev; TYPE_3__* q_vector; int /*<<< orphan*/  syncp; TYPE_1__ stats; scalar_t__ count; struct ice_tx_buf* tx_buf; int /*<<< orphan*/  dev; } ;
typedef  size_t s16 ;
struct TYPE_6__ {unsigned int total_bytes; unsigned int total_pkts; } ;
struct TYPE_7__ {TYPE_2__ tx; } ;

/* Variables and functions */
 int DESC_NEEDED ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t ICE_DESC_UNUSED (struct ice_ring*) ; 
 struct ice_tx_desc* ICE_TX_DESC (struct ice_ring*,size_t) ; 
 int /*<<< orphan*/  ICE_TX_DESC_DTYPE_DESC_DONE ; 
 int /*<<< orphan*/  __ICE_DOWN ; 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ice_tx_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct ice_tx_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct ice_tx_buf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  napi_consume_skb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (struct ice_tx_desc*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txring_txq (struct ice_ring*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ice_clean_tx_irq(struct ice_vsi *vsi, struct ice_ring *tx_ring,
			     int napi_budget)
{
	unsigned int total_bytes = 0, total_pkts = 0;
	unsigned int budget = vsi->work_lmt;
	s16 i = tx_ring->next_to_clean;
	struct ice_tx_desc *tx_desc;
	struct ice_tx_buf *tx_buf;

	tx_buf = &tx_ring->tx_buf[i];
	tx_desc = ICE_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	do {
		struct ice_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* if next_to_watch is not set then there is no work pending */
		if (!eop_desc)
			break;

		smp_rmb();	/* prevent any other reads prior to eop_desc */

		/* if the descriptor isn't done, no work yet to do */
		if (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_le64(ICE_TX_DESC_DTYPE_DESC_DONE)))
			break;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = NULL;

		/* update the statistics for this packet */
		total_bytes += tx_buf->bytecount;
		total_pkts += tx_buf->gso_segs;

		/* free the skb */
		napi_consume_skb(tx_buf->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buf, dma),
				 dma_unmap_len(tx_buf, len),
				 DMA_TO_DEVICE);

		/* clear tx_buf data */
		tx_buf->skb = NULL;
		dma_unmap_len_set(tx_buf, len, 0);

		/* unmap remaining buffers */
		while (tx_desc != eop_desc) {
			tx_buf++;
			tx_desc++;
			i++;
			if (unlikely(!i)) {
				i -= tx_ring->count;
				tx_buf = tx_ring->tx_buf;
				tx_desc = ICE_TX_DESC(tx_ring, 0);
			}

			/* unmap any remaining paged data */
			if (dma_unmap_len(tx_buf, len)) {
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buf, dma),
					       dma_unmap_len(tx_buf, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buf, len, 0);
			}
		}

		/* move us one more past the eop_desc for start of next pkt */
		tx_buf++;
		tx_desc++;
		i++;
		if (unlikely(!i)) {
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_buf;
			tx_desc = ICE_TX_DESC(tx_ring, 0);
		}

		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	} while (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.pkts += total_pkts;
	u64_stats_update_end(&tx_ring->syncp);
	tx_ring->q_vector->tx.total_bytes += total_bytes;
	tx_ring->q_vector->tx.total_pkts += total_pkts;

	netdev_tx_completed_queue(txring_txq(tx_ring), total_pkts,
				  total_bytes);

#define TX_WAKE_THRESHOLD ((s16)(DESC_NEEDED * 2))
	if (unlikely(total_pkts && netif_carrier_ok(tx_ring->netdev) &&
		     (ICE_DESC_UNUSED(tx_ring) >= TX_WAKE_THRESHOLD))) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		if (__netif_subqueue_stopped(tx_ring->netdev,
					     tx_ring->q_index) &&
		   !test_bit(__ICE_DOWN, vsi->state)) {
			netif_wake_subqueue(tx_ring->netdev,
					    tx_ring->q_index);
			++tx_ring->tx_stats.restart_q;
		}
	}

	return !!budget;
}