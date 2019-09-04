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
typedef  size_t u16 ;
struct i40e_vsi {unsigned int work_limit; int /*<<< orphan*/  state; } ;
struct i40e_tx_desc {int dummy; } ;
struct i40e_tx_buffer {int /*<<< orphan*/ * skb; int /*<<< orphan*/  xdpf; scalar_t__ gso_segs; scalar_t__ bytecount; struct i40e_tx_desc* next_to_watch; } ;
struct TYPE_8__ {int /*<<< orphan*/  restart_queue; } ;
struct TYPE_5__ {unsigned int bytes; unsigned int packets; } ;
struct i40e_ring {size_t next_to_clean; scalar_t__ count; int flags; int arm_wb; TYPE_4__ tx_stats; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  netdev; TYPE_3__* q_vector; int /*<<< orphan*/  syncp; TYPE_1__ stats; struct i40e_tx_buffer* tx_bi; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ s16 ;
struct TYPE_6__ {unsigned int total_bytes; unsigned int total_packets; } ;
struct TYPE_7__ {TYPE_2__ tx; } ;

/* Variables and functions */
 int DESC_NEEDED ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ I40E_DESC_UNUSED (struct i40e_ring*) ; 
 int I40E_TXR_FLAGS_WB_ON_ITR ; 
 struct i40e_tx_desc* I40E_TX_DESC (struct i40e_ring*,size_t) ; 
 unsigned int WB_STRIDE ; 
 int /*<<< orphan*/  __I40E_VSI_DOWN ; 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clean_tx_irq ; 
 int /*<<< orphan*/  clean_tx_irq_unmap ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct i40e_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct i40e_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 size_t i40e_get_head (struct i40e_ring*) ; 
 unsigned int i40e_get_tx_pending (struct i40e_ring*,int) ; 
 int /*<<< orphan*/  i40e_trace (int /*<<< orphan*/ ,struct i40e_ring*,struct i40e_tx_desc*,struct i40e_tx_buffer*) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  napi_consume_skb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (struct i40e_tx_desc*) ; 
 scalar_t__ ring_is_xdp (struct i40e_ring*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txring_txq (struct i40e_ring*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i40e_clean_tx_irq(struct i40e_vsi *vsi,
			      struct i40e_ring *tx_ring, int napi_budget)
{
	u16 i = tx_ring->next_to_clean;
	struct i40e_tx_buffer *tx_buf;
	struct i40e_tx_desc *tx_head;
	struct i40e_tx_desc *tx_desc;
	unsigned int total_bytes = 0, total_packets = 0;
	unsigned int budget = vsi->work_limit;

	tx_buf = &tx_ring->tx_bi[i];
	tx_desc = I40E_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	tx_head = I40E_TX_DESC(tx_ring, i40e_get_head(tx_ring));

	do {
		struct i40e_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* if next_to_watch is not set then there is no work pending */
		if (!eop_desc)
			break;

		/* prevent any other reads prior to eop_desc */
		smp_rmb();

		i40e_trace(clean_tx_irq, tx_ring, tx_desc, tx_buf);
		/* we have caught up to head, no work left to do */
		if (tx_head == tx_desc)
			break;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = NULL;

		/* update the statistics for this packet */
		total_bytes += tx_buf->bytecount;
		total_packets += tx_buf->gso_segs;

		/* free the skb/XDP data */
		if (ring_is_xdp(tx_ring))
			xdp_return_frame(tx_buf->xdpf);
		else
			napi_consume_skb(tx_buf->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buf, dma),
				 dma_unmap_len(tx_buf, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		tx_buf->skb = NULL;
		dma_unmap_len_set(tx_buf, len, 0);

		/* unmap remaining buffers */
		while (tx_desc != eop_desc) {
			i40e_trace(clean_tx_irq_unmap,
				   tx_ring, tx_desc, tx_buf);

			tx_buf++;
			tx_desc++;
			i++;
			if (unlikely(!i)) {
				i -= tx_ring->count;
				tx_buf = tx_ring->tx_bi;
				tx_desc = I40E_TX_DESC(tx_ring, 0);
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
			tx_buf = tx_ring->tx_bi;
			tx_desc = I40E_TX_DESC(tx_ring, 0);
		}

		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	} while (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->syncp);
	tx_ring->q_vector->tx.total_bytes += total_bytes;
	tx_ring->q_vector->tx.total_packets += total_packets;

	if (tx_ring->flags & I40E_TXR_FLAGS_WB_ON_ITR) {
		/* check to see if there are < 4 descriptors
		 * waiting to be written back, then kick the hardware to force
		 * them to be written back in case we stay in NAPI.
		 * In this mode on X722 we do not enable Interrupt.
		 */
		unsigned int j = i40e_get_tx_pending(tx_ring, false);

		if (budget &&
		    ((j / WB_STRIDE) == 0) && (j > 0) &&
		    !test_bit(__I40E_VSI_DOWN, vsi->state) &&
		    (I40E_DESC_UNUSED(tx_ring) != tx_ring->count))
			tx_ring->arm_wb = true;
	}

	if (ring_is_xdp(tx_ring))
		return !!budget;

	/* notify netdev of completed buffers */
	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);

#define TX_WAKE_THRESHOLD ((s16)(DESC_NEEDED * 2))
	if (unlikely(total_packets && netif_carrier_ok(tx_ring->netdev) &&
		     (I40E_DESC_UNUSED(tx_ring) >= TX_WAKE_THRESHOLD))) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		if (__netif_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		   !test_bit(__I40E_VSI_DOWN, vsi->state)) {
			netif_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		}
	}

	return !!budget;
}