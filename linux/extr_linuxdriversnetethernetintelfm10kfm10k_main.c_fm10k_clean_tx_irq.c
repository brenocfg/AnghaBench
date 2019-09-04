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
struct fm10k_tx_desc {int flags; } ;
struct fm10k_tx_buffer {int /*<<< orphan*/ * skb; scalar_t__ gso_segs; scalar_t__ bytecount; struct fm10k_tx_desc* next_to_watch; } ;
struct TYPE_6__ {int /*<<< orphan*/  restart_queue; } ;
struct TYPE_4__ {unsigned int bytes; unsigned int packets; } ;
struct fm10k_ring {unsigned int next_to_clean; TYPE_3__ tx_stats; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  netdev; int /*<<< orphan*/  next_to_use; int /*<<< orphan*/  reg_idx; int /*<<< orphan*/  syncp; TYPE_1__ stats; scalar_t__ count; struct fm10k_tx_buffer* tx_buffer; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {unsigned int work_limit; unsigned int total_bytes; unsigned int total_packets; } ;
struct fm10k_q_vector {TYPE_2__ tx; struct fm10k_intfc* interface; } ;
struct fm10k_hw {int dummy; } ;
struct fm10k_intfc {int /*<<< orphan*/  state; scalar_t__ tx_timeout_count; struct fm10k_hw hw; } ;

/* Variables and functions */
 int DESC_NEEDED ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ FM10K_MIN_TXD ; 
 int /*<<< orphan*/  FM10K_TDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM10K_TDT (int /*<<< orphan*/ ) ; 
 int FM10K_TXD_FLAG_DONE ; 
 struct fm10k_tx_desc* FM10K_TX_DESC (struct fm10k_ring*,unsigned int) ; 
 int /*<<< orphan*/  __FM10K_DOWN ; 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_for_tx_hang (struct fm10k_ring*) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct fm10k_tx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct fm10k_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct fm10k_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ fm10k_check_tx_hang (struct fm10k_ring*) ; 
 scalar_t__ fm10k_desc_unused (struct fm10k_ring*) ; 
 int /*<<< orphan*/  fm10k_read_reg (struct fm10k_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_tx_timeout_reset (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (unsigned int) ; 
 scalar_t__ min_t (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  napi_consume_skb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct fm10k_intfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  netif_info (struct fm10k_intfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (struct fm10k_tx_desc*) ; 
 int /*<<< orphan*/  probe ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txring_txq (struct fm10k_ring*) ; 
 int /*<<< orphan*/  u16 ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool fm10k_clean_tx_irq(struct fm10k_q_vector *q_vector,
			       struct fm10k_ring *tx_ring, int napi_budget)
{
	struct fm10k_intfc *interface = q_vector->interface;
	struct fm10k_tx_buffer *tx_buffer;
	struct fm10k_tx_desc *tx_desc;
	unsigned int total_bytes = 0, total_packets = 0;
	unsigned int budget = q_vector->tx.work_limit;
	unsigned int i = tx_ring->next_to_clean;

	if (test_bit(__FM10K_DOWN, interface->state))
		return true;

	tx_buffer = &tx_ring->tx_buffer[i];
	tx_desc = FM10K_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	do {
		struct fm10k_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* if next_to_watch is not set then there is no work pending */
		if (!eop_desc)
			break;

		/* prevent any other reads prior to eop_desc */
		smp_rmb();

		/* if DD is not set pending work has not been completed */
		if (!(eop_desc->flags & FM10K_TXD_FLAG_DONE))
			break;

		/* clear next_to_watch to prevent false hangs */
		tx_buffer->next_to_watch = NULL;

		/* update the statistics for this packet */
		total_bytes += tx_buffer->bytecount;
		total_packets += tx_buffer->gso_segs;

		/* free the skb */
		napi_consume_skb(tx_buffer->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		tx_buffer->skb = NULL;
		dma_unmap_len_set(tx_buffer, len, 0);

		/* unmap remaining buffers */
		while (tx_desc != eop_desc) {
			tx_buffer++;
			tx_desc++;
			i++;
			if (unlikely(!i)) {
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer;
				tx_desc = FM10K_TX_DESC(tx_ring, 0);
			}

			/* unmap any remaining paged data */
			if (dma_unmap_len(tx_buffer, len)) {
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buffer, dma),
					       dma_unmap_len(tx_buffer, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buffer, len, 0);
			}
		}

		/* move us one more past the eop_desc for start of next pkt */
		tx_buffer++;
		tx_desc++;
		i++;
		if (unlikely(!i)) {
			i -= tx_ring->count;
			tx_buffer = tx_ring->tx_buffer;
			tx_desc = FM10K_TX_DESC(tx_ring, 0);
		}

		/* issue prefetch for next Tx descriptor */
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
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;

	if (check_for_tx_hang(tx_ring) && fm10k_check_tx_hang(tx_ring)) {
		/* schedule immediate reset if we believe we hung */
		struct fm10k_hw *hw = &interface->hw;

		netif_err(interface, drv, tx_ring->netdev,
			  "Detected Tx Unit Hang\n"
			  "  Tx Queue             <%d>\n"
			  "  TDH, TDT             <%x>, <%x>\n"
			  "  next_to_use          <%x>\n"
			  "  next_to_clean        <%x>\n",
			  tx_ring->queue_index,
			  fm10k_read_reg(hw, FM10K_TDH(tx_ring->reg_idx)),
			  fm10k_read_reg(hw, FM10K_TDT(tx_ring->reg_idx)),
			  tx_ring->next_to_use, i);

		netif_stop_subqueue(tx_ring->netdev,
				    tx_ring->queue_index);

		netif_info(interface, probe, tx_ring->netdev,
			   "tx hang %d detected on queue %d, resetting interface\n",
			   interface->tx_timeout_count + 1,
			   tx_ring->queue_index);

		fm10k_tx_timeout_reset(interface);

		/* the netdev is about to reset, no point in enabling stuff */
		return true;
	}

	/* notify netdev of completed buffers */
	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);

#define TX_WAKE_THRESHOLD min_t(u16, FM10K_MIN_TXD - 1, DESC_NEEDED * 2)
	if (unlikely(total_packets && netif_carrier_ok(tx_ring->netdev) &&
		     (fm10k_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD))) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		if (__netif_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		    !test_bit(__FM10K_DOWN, interface->state)) {
			netif_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		}
	}

	return !!budget;
}