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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  size_t u16 ;
struct net_device {int dummy; } ;
struct mlx4_err_cqe {int /*<<< orphan*/  syndrome; int /*<<< orphan*/  vendor_err_syndrome; } ;
struct mlx4_en_tx_ring {int size_mask; int (* free_tx_desc ) (struct mlx4_en_priv*,struct mlx4_en_tx_ring*,size_t,int /*<<< orphan*/ ,int) ;int size; int /*<<< orphan*/  wake_queue; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  cons; int /*<<< orphan*/  last_nr_txbb; TYPE_1__* tx_info; } ;
struct mlx4_en_priv {int cqe_factor; int tx_work_limit; int /*<<< orphan*/  cqe_size; int /*<<< orphan*/  port_up; struct mlx4_en_tx_ring*** tx_ring; } ;
struct mlx4_cq {int cons_index; } ;
struct mlx4_en_cq {size_t type; size_t ring; int size; struct mlx4_cqe* buf; struct mlx4_cq mcq; } ;
struct mlx4_cqe {int owner_sr_opcode; int /*<<< orphan*/  wqe_index; } ;
struct TYPE_2__ {int ts_requested; scalar_t__ nr_bytes; } ;

/* Variables and functions */
 int MLX4_CQE_OPCODE_ERROR ; 
 int MLX4_CQE_OPCODE_MASK ; 
 int MLX4_CQE_OWNER_MASK ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 size_t TX_XDP ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XNOR (int,int) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_rmb () ; 
 int /*<<< orphan*/  en_err (struct mlx4_en_priv*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cq_set_ci (struct mlx4_cq*) ; 
 struct mlx4_cqe* mlx4_en_get_cqe (struct mlx4_cqe*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_get_cqe_ts (struct mlx4_cqe*) ; 
 int /*<<< orphan*/  mlx4_en_is_tx_ring_full (struct mlx4_en_tx_ring*) ; 
 int /*<<< orphan*/  mlx4_en_stamp_wqe (struct mlx4_en_priv*,struct mlx4_en_tx_ring*,size_t,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_tx_completed_queue (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  netdev_txq_bql_complete_prefetchw (int /*<<< orphan*/ ) ; 
 scalar_t__ netif_tx_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (int /*<<< orphan*/ ) ; 
 int stub1 (struct mlx4_en_priv*,struct mlx4_en_tx_ring*,size_t,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

bool mlx4_en_process_tx_cq(struct net_device *dev,
			   struct mlx4_en_cq *cq, int napi_budget)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	struct mlx4_cq *mcq = &cq->mcq;
	struct mlx4_en_tx_ring *ring = priv->tx_ring[cq->type][cq->ring];
	struct mlx4_cqe *cqe;
	u16 index, ring_index, stamp_index;
	u32 txbbs_skipped = 0;
	u32 txbbs_stamp = 0;
	u32 cons_index = mcq->cons_index;
	int size = cq->size;
	u32 size_mask = ring->size_mask;
	struct mlx4_cqe *buf = cq->buf;
	u32 packets = 0;
	u32 bytes = 0;
	int factor = priv->cqe_factor;
	int done = 0;
	int budget = priv->tx_work_limit;
	u32 last_nr_txbb;
	u32 ring_cons;

	if (unlikely(!priv->port_up))
		return true;

	netdev_txq_bql_complete_prefetchw(ring->tx_queue);

	index = cons_index & size_mask;
	cqe = mlx4_en_get_cqe(buf, index, priv->cqe_size) + factor;
	last_nr_txbb = READ_ONCE(ring->last_nr_txbb);
	ring_cons = READ_ONCE(ring->cons);
	ring_index = ring_cons & size_mask;
	stamp_index = ring_index;

	/* Process all completed CQEs */
	while (XNOR(cqe->owner_sr_opcode & MLX4_CQE_OWNER_MASK,
			cons_index & size) && (done < budget)) {
		u16 new_index;

		/*
		 * make sure we read the CQE after we read the
		 * ownership bit
		 */
		dma_rmb();

		if (unlikely((cqe->owner_sr_opcode & MLX4_CQE_OPCODE_MASK) ==
			     MLX4_CQE_OPCODE_ERROR)) {
			struct mlx4_err_cqe *cqe_err = (struct mlx4_err_cqe *)cqe;

			en_err(priv, "CQE error - vendor syndrome: 0x%x syndrome: 0x%x\n",
			       cqe_err->vendor_err_syndrome,
			       cqe_err->syndrome);
		}

		/* Skip over last polled CQE */
		new_index = be16_to_cpu(cqe->wqe_index) & size_mask;

		do {
			u64 timestamp = 0;

			txbbs_skipped += last_nr_txbb;
			ring_index = (ring_index + last_nr_txbb) & size_mask;

			if (unlikely(ring->tx_info[ring_index].ts_requested))
				timestamp = mlx4_en_get_cqe_ts(cqe);

			/* free next descriptor */
			last_nr_txbb = ring->free_tx_desc(
					priv, ring, ring_index,
					timestamp, napi_budget);

			mlx4_en_stamp_wqe(priv, ring, stamp_index,
					  !!((ring_cons + txbbs_stamp) &
						ring->size));
			stamp_index = ring_index;
			txbbs_stamp = txbbs_skipped;
			packets++;
			bytes += ring->tx_info[ring_index].nr_bytes;
		} while ((++done < budget) && (ring_index != new_index));

		++cons_index;
		index = cons_index & size_mask;
		cqe = mlx4_en_get_cqe(buf, index, priv->cqe_size) + factor;
	}

	/*
	 * To prevent CQ overflow we first update CQ consumer and only then
	 * the ring consumer.
	 */
	mcq->cons_index = cons_index;
	mlx4_cq_set_ci(mcq);
	wmb();

	/* we want to dirty this cache line once */
	WRITE_ONCE(ring->last_nr_txbb, last_nr_txbb);
	WRITE_ONCE(ring->cons, ring_cons + txbbs_skipped);

	if (cq->type == TX_XDP)
		return done < budget;

	netdev_tx_completed_queue(ring->tx_queue, packets, bytes);

	/* Wakeup Tx queue if this stopped, and ring is not full.
	 */
	if (netif_tx_queue_stopped(ring->tx_queue) &&
	    !mlx4_en_is_tx_ring_full(ring)) {
		netif_tx_wake_queue(ring->tx_queue);
		ring->wake_queue++;
	}

	return done < budget;
}