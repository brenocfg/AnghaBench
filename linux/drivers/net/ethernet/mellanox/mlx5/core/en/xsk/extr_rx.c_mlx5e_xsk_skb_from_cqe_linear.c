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
typedef  int u32 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct mlx5e_wqe_frag_info {int /*<<< orphan*/  offset; struct mlx5e_dma_info* di; } ;
struct TYPE_5__ {int headroom; int umem_headroom; } ;
struct mlx5e_rq {TYPE_3__* stats; int /*<<< orphan*/  pdev; TYPE_2__ buff; } ;
struct TYPE_4__ {void* data; } ;
struct mlx5e_dma_info {int /*<<< orphan*/  addr; TYPE_1__ xsk; } ;
struct mlx5_cqe64 {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  wqe_err; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 scalar_t__ MLX5_CQE_RESP_SEND ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_cqe_opcode (struct mlx5_cqe64*) ; 
 scalar_t__ likely (int) ; 
 int mlx5e_xdp_handle (struct mlx5e_rq*,struct mlx5e_dma_info*,void*,int*,int*,int) ; 
 struct sk_buff* mlx5e_xsk_construct_skb (struct mlx5e_rq*,void*,int) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *mlx5e_xsk_skb_from_cqe_linear(struct mlx5e_rq *rq,
					      struct mlx5_cqe64 *cqe,
					      struct mlx5e_wqe_frag_info *wi,
					      u32 cqe_bcnt)
{
	struct mlx5e_dma_info *di = wi->di;
	u16 rx_headroom = rq->buff.headroom - rq->buff.umem_headroom;
	void *va, *data;
	bool consumed;
	u32 frag_size;

	/* wi->offset is not used in this function, because di->xsk.data and
	 * di->addr point directly to the necessary place. Furthermore, in the
	 * current implementation, one page = one packet = one frame, so
	 * wi->offset should always be 0.
	 */
	WARN_ON_ONCE(wi->offset);

	va             = di->xsk.data;
	data           = va + rx_headroom;
	frag_size      = rq->buff.headroom + cqe_bcnt;

	dma_sync_single_for_cpu(rq->pdev, di->addr, frag_size, DMA_BIDIRECTIONAL);
	prefetch(data);

	if (unlikely(get_cqe_opcode(cqe) != MLX5_CQE_RESP_SEND)) {
		rq->stats->wqe_err++;
		return NULL;
	}

	rcu_read_lock();
	consumed = mlx5e_xdp_handle(rq, di, va, &rx_headroom, &cqe_bcnt, true);
	rcu_read_unlock();

	if (likely(consumed))
		return NULL; /* page/packet was consumed by XDP */

	/* XDP_PASS: copy the data from the UMEM to a new SKB. The frame reuse
	 * will be handled by mlx5e_put_rx_frag.
	 * On SKB allocation failure, NULL is returned.
	 */
	return mlx5e_xsk_construct_skb(rq, data, cqe_bcnt);
}