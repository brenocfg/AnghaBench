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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_8__ {scalar_t__ headroom; scalar_t__ umem_headroom; } ;
struct mlx5e_rq {scalar_t__ hw_mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev; TYPE_4__ buff; TYPE_2__* stats; } ;
struct TYPE_5__ {struct mlx5e_dma_info* dma_info; } ;
struct mlx5e_mpw_info {int /*<<< orphan*/  xdp_xmit_bitmap; TYPE_1__ umr; } ;
struct TYPE_7__ {void* data; } ;
struct mlx5e_dma_info {int /*<<< orphan*/  addr; TYPE_3__ xsk; } ;
struct TYPE_6__ {int /*<<< orphan*/  oversize_pkts_sw_drop; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  MLX5E_RQ_FLAG_XDP_XMIT ; 
 int /*<<< orphan*/  WARN_ON_ONCE (size_t) ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 int __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int mlx5e_xdp_handle (struct mlx5e_rq*,struct mlx5e_dma_info*,void*,scalar_t__*,size_t*,int) ; 
 struct sk_buff* mlx5e_xsk_construct_skb (struct mlx5e_rq*,void*,size_t) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *mlx5e_xsk_skb_from_cqe_mpwrq_linear(struct mlx5e_rq *rq,
						    struct mlx5e_mpw_info *wi,
						    u16 cqe_bcnt,
						    u32 head_offset,
						    u32 page_idx)
{
	struct mlx5e_dma_info *di = &wi->umr.dma_info[page_idx];
	u16 rx_headroom = rq->buff.headroom - rq->buff.umem_headroom;
	u32 cqe_bcnt32 = cqe_bcnt;
	void *va, *data;
	u32 frag_size;
	bool consumed;

	/* Check packet size. Note LRO doesn't use linear SKB */
	if (unlikely(cqe_bcnt > rq->hw_mtu)) {
		rq->stats->oversize_pkts_sw_drop++;
		return NULL;
	}

	/* head_offset is not used in this function, because di->xsk.data and
	 * di->addr point directly to the necessary place. Furthermore, in the
	 * current implementation, UMR pages are mapped to XSK frames, so
	 * head_offset should always be 0.
	 */
	WARN_ON_ONCE(head_offset);

	va             = di->xsk.data;
	data           = va + rx_headroom;
	frag_size      = rq->buff.headroom + cqe_bcnt32;

	dma_sync_single_for_cpu(rq->pdev, di->addr, frag_size, DMA_BIDIRECTIONAL);
	prefetch(data);

	rcu_read_lock();
	consumed = mlx5e_xdp_handle(rq, di, va, &rx_headroom, &cqe_bcnt32, true);
	rcu_read_unlock();

	/* Possible flows:
	 * - XDP_REDIRECT to XSKMAP:
	 *   The page is owned by the userspace from now.
	 * - XDP_TX and other XDP_REDIRECTs:
	 *   The page was returned by ZCA and recycled.
	 * - XDP_DROP:
	 *   Recycle the page.
	 * - XDP_PASS:
	 *   Allocate an SKB, copy the data and recycle the page.
	 *
	 * Pages to be recycled go to the Reuse Ring on MPWQE deallocation. Its
	 * size is the same as the Driver RX Ring's size, and pages for WQEs are
	 * allocated first from the Reuse Ring, so it has enough space.
	 */

	if (likely(consumed)) {
		if (likely(__test_and_clear_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags)))
			__set_bit(page_idx, wi->xdp_xmit_bitmap); /* non-atomic */
		return NULL; /* page/packet was consumed by XDP */
	}

	/* XDP_PASS: copy the data from the UMEM to a new SKB and reuse the
	 * frame. On SKB allocation failure, NULL is returned.
	 */
	return mlx5e_xsk_construct_skb(rq, data, cqe_bcnt32);
}