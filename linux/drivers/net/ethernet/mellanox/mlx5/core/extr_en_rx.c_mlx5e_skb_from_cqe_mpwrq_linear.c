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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {scalar_t__ headroom; } ;
struct mlx5e_rq {scalar_t__ hw_mtu; int /*<<< orphan*/  flags; int /*<<< orphan*/  pdev; TYPE_3__* stats; TYPE_2__ buff; } ;
struct TYPE_4__ {struct mlx5e_dma_info* dma_info; } ;
struct mlx5e_mpw_info {int /*<<< orphan*/  xdp_xmit_bitmap; TYPE_1__ umr; } ;
struct mlx5e_dma_info {int /*<<< orphan*/  page; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  oversize_pkts_sw_drop; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  MLX5E_RQ_FLAG_XDP_XMIT ; 
 size_t MLX5_SKB_FRAG_SZ (scalar_t__) ; 
 int /*<<< orphan*/  __set_bit (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ __test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_range_for_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ) ; 
 struct sk_buff* mlx5e_build_linear_skb (struct mlx5e_rq*,void*,size_t,scalar_t__,size_t) ; 
 int mlx5e_xdp_handle (struct mlx5e_rq*,struct mlx5e_dma_info*,void*,scalar_t__*,size_t*,int) ; 
 size_t page_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_ref_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefetch (void*) ; 
 int /*<<< orphan*/  prefetchw (void*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 

struct sk_buff *
mlx5e_skb_from_cqe_mpwrq_linear(struct mlx5e_rq *rq, struct mlx5e_mpw_info *wi,
				u16 cqe_bcnt, u32 head_offset, u32 page_idx)
{
	struct mlx5e_dma_info *di = &wi->umr.dma_info[page_idx];
	u16 rx_headroom = rq->buff.headroom;
	u32 cqe_bcnt32 = cqe_bcnt;
	struct sk_buff *skb;
	void *va, *data;
	u32 frag_size;
	bool consumed;

	/* Check packet size. Note LRO doesn't use linear SKB */
	if (unlikely(cqe_bcnt > rq->hw_mtu)) {
		rq->stats->oversize_pkts_sw_drop++;
		return NULL;
	}

	va             = page_address(di->page) + head_offset;
	data           = va + rx_headroom;
	frag_size      = MLX5_SKB_FRAG_SZ(rx_headroom + cqe_bcnt32);

	dma_sync_single_range_for_cpu(rq->pdev, di->addr, head_offset,
				      frag_size, DMA_FROM_DEVICE);
	prefetchw(va); /* xdp_frame data area */
	prefetch(data);

	rcu_read_lock();
	consumed = mlx5e_xdp_handle(rq, di, va, &rx_headroom, &cqe_bcnt32, false);
	rcu_read_unlock();
	if (consumed) {
		if (__test_and_clear_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags))
			__set_bit(page_idx, wi->xdp_xmit_bitmap); /* non-atomic */
		return NULL; /* page/packet was consumed by XDP */
	}

	skb = mlx5e_build_linear_skb(rq, va, frag_size, rx_headroom, cqe_bcnt32);
	if (unlikely(!skb))
		return NULL;

	/* queue up for recycling/reuse */
	page_ref_inc(di->page);

	return skb;
}