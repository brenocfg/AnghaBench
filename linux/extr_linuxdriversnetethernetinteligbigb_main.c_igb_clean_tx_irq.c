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
struct TYPE_5__ {int status; } ;
union e1000_adv_tx_desc {TYPE_2__ wb; } ;
struct igb_tx_buffer {union e1000_adv_tx_desc* next_to_watch; scalar_t__ time_stamp; int /*<<< orphan*/  skb; scalar_t__ gso_segs; scalar_t__ bytecount; } ;
struct TYPE_6__ {unsigned int bytes; unsigned int packets; int /*<<< orphan*/  restart_queue; } ;
struct igb_ring {unsigned int next_to_clean; int /*<<< orphan*/  tx_syncp; TYPE_3__ tx_stats; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  netdev; int /*<<< orphan*/  next_to_use; int /*<<< orphan*/  tail; int /*<<< orphan*/  reg_idx; int /*<<< orphan*/  dev; int /*<<< orphan*/  flags; scalar_t__ count; struct igb_tx_buffer* tx_buffer_info; } ;
struct TYPE_4__ {unsigned int work_limit; unsigned int total_bytes; unsigned int total_packets; struct igb_ring* ring; } ;
struct igb_q_vector {TYPE_1__ tx; struct igb_adapter* adapter; } ;
struct e1000_hw {int dummy; } ;
struct igb_adapter {int tx_timeout_factor; int /*<<< orphan*/  state; struct e1000_hw hw; } ;

/* Variables and functions */
 int DESC_NEEDED ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_TXOFF ; 
 int /*<<< orphan*/  E1000_TDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_TXD_STAT_DD ; 
 int HZ ; 
 int /*<<< orphan*/  IGB_RING_FLAG_TX_DETECT_HANG ; 
 union e1000_adv_tx_desc* IGB_TX_DESC (struct igb_ring*,unsigned int) ; 
 int /*<<< orphan*/  __IGB_DOWN ; 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__,union e1000_adv_tx_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct igb_tx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct igb_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct igb_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int igb_desc_unused (struct igb_ring*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  napi_consume_skb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (union e1000_adv_tx_desc*) ; 
 int rd32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  txring_txq (struct igb_ring*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool igb_clean_tx_irq(struct igb_q_vector *q_vector, int napi_budget)
{
	struct igb_adapter *adapter = q_vector->adapter;
	struct igb_ring *tx_ring = q_vector->tx.ring;
	struct igb_tx_buffer *tx_buffer;
	union e1000_adv_tx_desc *tx_desc;
	unsigned int total_bytes = 0, total_packets = 0;
	unsigned int budget = q_vector->tx.work_limit;
	unsigned int i = tx_ring->next_to_clean;

	if (test_bit(__IGB_DOWN, &adapter->state))
		return true;

	tx_buffer = &tx_ring->tx_buffer_info[i];
	tx_desc = IGB_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	do {
		union e1000_adv_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* if next_to_watch is not set then there is no work pending */
		if (!eop_desc)
			break;

		/* prevent any other reads prior to eop_desc */
		smp_rmb();

		/* if DD is not set pending work has not been completed */
		if (!(eop_desc->wb.status & cpu_to_le32(E1000_TXD_STAT_DD)))
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
		dma_unmap_len_set(tx_buffer, len, 0);

		/* clear last DMA location and unmap remaining buffers */
		while (tx_desc != eop_desc) {
			tx_buffer++;
			tx_desc++;
			i++;
			if (unlikely(!i)) {
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IGB_TX_DESC(tx_ring, 0);
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
			tx_buffer = tx_ring->tx_buffer_info;
			tx_desc = IGB_TX_DESC(tx_ring, 0);
		}

		/* issue prefetch for next Tx descriptor */
		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	} while (likely(budget));

	netdev_tx_completed_queue(txring_txq(tx_ring),
				  total_packets, total_bytes);
	i += tx_ring->count;
	tx_ring->next_to_clean = i;
	u64_stats_update_begin(&tx_ring->tx_syncp);
	tx_ring->tx_stats.bytes += total_bytes;
	tx_ring->tx_stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->tx_syncp);
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;

	if (test_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags)) {
		struct e1000_hw *hw = &adapter->hw;

		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of time_stamp and movement of i
		 */
		clear_bit(IGB_RING_FLAG_TX_DETECT_HANG, &tx_ring->flags);
		if (tx_buffer->next_to_watch &&
		    time_after(jiffies, tx_buffer->time_stamp +
			       (adapter->tx_timeout_factor * HZ)) &&
		    !(rd32(E1000_STATUS) & E1000_STATUS_TXOFF)) {

			/* detected Tx unit hang */
			dev_err(tx_ring->dev,
				"Detected Tx Unit Hang\n"
				"  Tx Queue             <%d>\n"
				"  TDH                  <%x>\n"
				"  TDT                  <%x>\n"
				"  next_to_use          <%x>\n"
				"  next_to_clean        <%x>\n"
				"buffer_info[next_to_clean]\n"
				"  time_stamp           <%lx>\n"
				"  next_to_watch        <%p>\n"
				"  jiffies              <%lx>\n"
				"  desc.status          <%x>\n",
				tx_ring->queue_index,
				rd32(E1000_TDH(tx_ring->reg_idx)),
				readl(tx_ring->tail),
				tx_ring->next_to_use,
				tx_ring->next_to_clean,
				tx_buffer->time_stamp,
				tx_buffer->next_to_watch,
				jiffies,
				tx_buffer->next_to_watch->wb.status);
			netif_stop_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

			/* we are about to reset, no point in enabling stuff */
			return true;
		}
	}

#define TX_WAKE_THRESHOLD (DESC_NEEDED * 2)
	if (unlikely(total_packets &&
	    netif_carrier_ok(tx_ring->netdev) &&
	    igb_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD)) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		if (__netif_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		    !(test_bit(__IGB_DOWN, &adapter->state))) {
			netif_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

			u64_stats_update_begin(&tx_ring->tx_syncp);
			tx_ring->tx_stats.restart_queue++;
			u64_stats_update_end(&tx_ring->tx_syncp);
		}
	}

	return !!budget;
}