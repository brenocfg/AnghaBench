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
struct TYPE_7__ {int status; } ;
union ixgbe_adv_tx_desc {TYPE_3__ wb; } ;
struct ixgbevf_tx_buffer {int /*<<< orphan*/  time_stamp; union ixgbe_adv_tx_desc* next_to_watch; int /*<<< orphan*/  skb; int /*<<< orphan*/  data; scalar_t__ gso_segs; scalar_t__ bytecount; } ;
struct TYPE_8__ {int /*<<< orphan*/  restart_queue; } ;
struct TYPE_5__ {unsigned int bytes; unsigned int packets; } ;
struct ixgbevf_ring {int count; unsigned int next_to_clean; TYPE_4__ tx_stats; int /*<<< orphan*/  queue_index; int /*<<< orphan*/  netdev; struct ixgbevf_tx_buffer* tx_buffer_info; int /*<<< orphan*/  next_to_use; int /*<<< orphan*/  reg_idx; int /*<<< orphan*/  syncp; TYPE_1__ stats; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {unsigned int total_bytes; unsigned int total_packets; } ;
struct ixgbevf_q_vector {TYPE_2__ tx; struct ixgbevf_adapter* adapter; } ;
struct ixgbe_hw {int dummy; } ;
struct ixgbevf_adapter {int /*<<< orphan*/  state; struct ixgbe_hw hw; } ;

/* Variables and functions */
 int DESC_NEEDED ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 union ixgbe_adv_tx_desc* IXGBEVF_TX_DESC (struct ixgbevf_ring*,unsigned int) ; 
 int /*<<< orphan*/  IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_TXD_STAT_DD ; 
 int /*<<< orphan*/  IXGBE_VFTDH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_VFTDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IXGBEVF_DOWN ; 
 scalar_t__ __netif_subqueue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_for_tx_hang (struct ixgbevf_ring*) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma ; 
 int /*<<< orphan*/  dma_unmap_addr (struct ixgbevf_tx_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_unmap_len (struct ixgbevf_tx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct ixgbevf_tx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbevf_check_tx_hang (struct ixgbevf_ring*) ; 
 int ixgbevf_desc_unused (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  ixgbevf_tx_timeout_reset (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  len ; 
 scalar_t__ likely (unsigned int) ; 
 int /*<<< orphan*/  napi_consume_skb (int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_subqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_frag_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,union ixgbe_adv_tx_desc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (union ixgbe_adv_tx_desc*) ; 
 scalar_t__ ring_is_xdp (struct ixgbevf_ring*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool ixgbevf_clean_tx_irq(struct ixgbevf_q_vector *q_vector,
				 struct ixgbevf_ring *tx_ring, int napi_budget)
{
	struct ixgbevf_adapter *adapter = q_vector->adapter;
	struct ixgbevf_tx_buffer *tx_buffer;
	union ixgbe_adv_tx_desc *tx_desc;
	unsigned int total_bytes = 0, total_packets = 0;
	unsigned int budget = tx_ring->count / 2;
	unsigned int i = tx_ring->next_to_clean;

	if (test_bit(__IXGBEVF_DOWN, &adapter->state))
		return true;

	tx_buffer = &tx_ring->tx_buffer_info[i];
	tx_desc = IXGBEVF_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	do {
		union ixgbe_adv_tx_desc *eop_desc = tx_buffer->next_to_watch;

		/* if next_to_watch is not set then there is no work pending */
		if (!eop_desc)
			break;

		/* prevent any other reads prior to eop_desc */
		smp_rmb();

		/* if DD is not set pending work has not been completed */
		if (!(eop_desc->wb.status & cpu_to_le32(IXGBE_TXD_STAT_DD)))
			break;

		/* clear next_to_watch to prevent false hangs */
		tx_buffer->next_to_watch = NULL;

		/* update the statistics for this packet */
		total_bytes += tx_buffer->bytecount;
		total_packets += tx_buffer->gso_segs;

		/* free the skb */
		if (ring_is_xdp(tx_ring))
			page_frag_free(tx_buffer->data);
		else
			napi_consume_skb(tx_buffer->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buffer, dma),
				 dma_unmap_len(tx_buffer, len),
				 DMA_TO_DEVICE);

		/* clear tx_buffer data */
		dma_unmap_len_set(tx_buffer, len, 0);

		/* unmap remaining buffers */
		while (tx_desc != eop_desc) {
			tx_buffer++;
			tx_desc++;
			i++;
			if (unlikely(!i)) {
				i -= tx_ring->count;
				tx_buffer = tx_ring->tx_buffer_info;
				tx_desc = IXGBEVF_TX_DESC(tx_ring, 0);
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
			tx_desc = IXGBEVF_TX_DESC(tx_ring, 0);
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

	if (check_for_tx_hang(tx_ring) && ixgbevf_check_tx_hang(tx_ring)) {
		struct ixgbe_hw *hw = &adapter->hw;
		union ixgbe_adv_tx_desc *eop_desc;

		eop_desc = tx_ring->tx_buffer_info[i].next_to_watch;

		pr_err("Detected Tx Unit Hang%s\n"
		       "  Tx Queue             <%d>\n"
		       "  TDH, TDT             <%x>, <%x>\n"
		       "  next_to_use          <%x>\n"
		       "  next_to_clean        <%x>\n"
		       "tx_buffer_info[next_to_clean]\n"
		       "  next_to_watch        <%p>\n"
		       "  eop_desc->wb.status  <%x>\n"
		       "  time_stamp           <%lx>\n"
		       "  jiffies              <%lx>\n",
		       ring_is_xdp(tx_ring) ? " XDP" : "",
		       tx_ring->queue_index,
		       IXGBE_READ_REG(hw, IXGBE_VFTDH(tx_ring->reg_idx)),
		       IXGBE_READ_REG(hw, IXGBE_VFTDT(tx_ring->reg_idx)),
		       tx_ring->next_to_use, i,
		       eop_desc, (eop_desc ? eop_desc->wb.status : 0),
		       tx_ring->tx_buffer_info[i].time_stamp, jiffies);

		if (!ring_is_xdp(tx_ring))
			netif_stop_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);

		/* schedule immediate reset if we believe we hung */
		ixgbevf_tx_timeout_reset(adapter);

		return true;
	}

	if (ring_is_xdp(tx_ring))
		return !!budget;

#define TX_WAKE_THRESHOLD (DESC_NEEDED * 2)
	if (unlikely(total_packets && netif_carrier_ok(tx_ring->netdev) &&
		     (ixgbevf_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD))) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();

		if (__netif_subqueue_stopped(tx_ring->netdev,
					     tx_ring->queue_index) &&
		    !test_bit(__IXGBEVF_DOWN, &adapter->state)) {
			netif_wake_subqueue(tx_ring->netdev,
					    tx_ring->queue_index);
			++tx_ring->tx_stats.restart_queue;
		}
	}

	return !!budget;
}