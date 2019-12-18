#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct xdp_umem {int dummy; } ;
struct xdp_buff {void* data; void* data_end; void* data_hard_start; int /*<<< orphan*/  handle; int /*<<< orphan*/ * rxq; } ;
struct mlx5e_rq {TYPE_2__* stats; int /*<<< orphan*/  netdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  xdpsq; int /*<<< orphan*/  xdp_rxq; struct xdp_umem* umem; int /*<<< orphan*/  xdp_prog; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct mlx5e_dma_info {TYPE_1__ xsk; } ;
struct bpf_prog {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  xdp_drop; int /*<<< orphan*/  xdp_redirect; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_RQ_FLAG_XDP_REDIRECT ; 
 int /*<<< orphan*/  MLX5E_RQ_FLAG_XDP_XMIT ; 
 struct bpf_prog* READ_ONCE (int /*<<< orphan*/ ) ; 
#define  XDP_ABORTED 132 
#define  XDP_DROP 131 
#define  XDP_PASS 130 
#define  XDP_REDIRECT 129 
#define  XDP_TX 128 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bpf_prog_run_xdp (struct bpf_prog*,struct xdp_buff*) ; 
 int /*<<< orphan*/  bpf_warn_invalid_xdp_action (int) ; 
 int /*<<< orphan*/  mlx5e_page_dma_unmap (struct mlx5e_rq*,struct mlx5e_dma_info*) ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_buff (int /*<<< orphan*/ ,struct mlx5e_rq*,struct mlx5e_dma_info*,struct xdp_buff*) ; 
 int /*<<< orphan*/  trace_xdp_exception (int /*<<< orphan*/ ,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  unlikely (int) ; 
 int xdp_do_redirect (int /*<<< orphan*/ ,struct xdp_buff*,struct bpf_prog*) ; 
 int /*<<< orphan*/  xdp_set_data_meta_invalid (struct xdp_buff*) ; 
 int /*<<< orphan*/  xsk_umem_adjust_offset (struct xdp_umem*,int /*<<< orphan*/ ,int) ; 

bool mlx5e_xdp_handle(struct mlx5e_rq *rq, struct mlx5e_dma_info *di,
		      void *va, u16 *rx_headroom, u32 *len, bool xsk)
{
	struct bpf_prog *prog = READ_ONCE(rq->xdp_prog);
	struct xdp_umem *umem = rq->umem;
	struct xdp_buff xdp;
	u32 act;
	int err;

	if (!prog)
		return false;

	xdp.data = va + *rx_headroom;
	xdp_set_data_meta_invalid(&xdp);
	xdp.data_end = xdp.data + *len;
	xdp.data_hard_start = va;
	if (xsk)
		xdp.handle = di->xsk.handle;
	xdp.rxq = &rq->xdp_rxq;

	act = bpf_prog_run_xdp(prog, &xdp);
	if (xsk) {
		u64 off = xdp.data - xdp.data_hard_start;

		xdp.handle = xsk_umem_adjust_offset(umem, xdp.handle, off);
	}
	switch (act) {
	case XDP_PASS:
		*rx_headroom = xdp.data - xdp.data_hard_start;
		*len = xdp.data_end - xdp.data;
		return false;
	case XDP_TX:
		if (unlikely(!mlx5e_xmit_xdp_buff(rq->xdpsq, rq, di, &xdp)))
			goto xdp_abort;
		__set_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags); /* non-atomic */
		return true;
	case XDP_REDIRECT:
		/* When XDP enabled then page-refcnt==1 here */
		err = xdp_do_redirect(rq->netdev, &xdp, prog);
		if (unlikely(err))
			goto xdp_abort;
		__set_bit(MLX5E_RQ_FLAG_XDP_XMIT, rq->flags);
		__set_bit(MLX5E_RQ_FLAG_XDP_REDIRECT, rq->flags);
		if (!xsk)
			mlx5e_page_dma_unmap(rq, di);
		rq->stats->xdp_redirect++;
		return true;
	default:
		bpf_warn_invalid_xdp_action(act);
		/* fall through */
	case XDP_ABORTED:
xdp_abort:
		trace_xdp_exception(rq->netdev, prog, act);
		/* fall through */
	case XDP_DROP:
		rq->stats->xdp_drop++;
		return true;
	}
}