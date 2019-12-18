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
struct xdp_umem {int dummy; } ;
struct xdp_desc {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ wqe; } ;
struct mlx5e_xdpsq {int (* xmit_xdp_frame_check ) (struct mlx5e_xdpsq*) ;TYPE_1__ mpwqe; int /*<<< orphan*/  (* xmit_xdp_frame ) (struct mlx5e_xdpsq*,struct mlx5e_xdp_xmit_data*,struct mlx5e_xdp_info*,int) ;int /*<<< orphan*/  pdev; struct xdp_umem* umem; } ;
struct mlx5e_xdp_xmit_data {int /*<<< orphan*/  len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  data; } ;
struct mlx5e_xdp_info {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  MLX5E_XDP_XMIT_MODE_XSK ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_xdp_mpwqe_complete (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_doorbell (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  mlx5e_xsk_tx_post_err (struct mlx5e_xdpsq*,struct mlx5e_xdp_info*) ; 
 int stub1 (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  stub2 (struct mlx5e_xdpsq*,struct mlx5e_xdp_xmit_data*,struct mlx5e_xdp_info*,int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_umem_get_data (struct xdp_umem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_umem_get_dma (struct xdp_umem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem_consume_tx (struct xdp_umem*,struct xdp_desc*) ; 
 int /*<<< orphan*/  xsk_umem_consume_tx_done (struct xdp_umem*) ; 

bool mlx5e_xsk_tx(struct mlx5e_xdpsq *sq, unsigned int budget)
{
	struct xdp_umem *umem = sq->umem;
	struct mlx5e_xdp_info xdpi;
	struct mlx5e_xdp_xmit_data xdptxd;
	bool work_done = true;
	bool flush = false;

	xdpi.mode = MLX5E_XDP_XMIT_MODE_XSK;

	for (; budget; budget--) {
		int check_result = sq->xmit_xdp_frame_check(sq);
		struct xdp_desc desc;

		if (unlikely(check_result < 0)) {
			work_done = false;
			break;
		}

		if (!xsk_umem_consume_tx(umem, &desc)) {
			/* TX will get stuck until something wakes it up by
			 * triggering NAPI. Currently it's expected that the
			 * application calls sendto() if there are consumed, but
			 * not completed frames.
			 */
			break;
		}

		xdptxd.dma_addr = xdp_umem_get_dma(umem, desc.addr);
		xdptxd.data = xdp_umem_get_data(umem, desc.addr);
		xdptxd.len = desc.len;

		dma_sync_single_for_device(sq->pdev, xdptxd.dma_addr,
					   xdptxd.len, DMA_BIDIRECTIONAL);

		if (unlikely(!sq->xmit_xdp_frame(sq, &xdptxd, &xdpi, check_result))) {
			if (sq->mpwqe.wqe)
				mlx5e_xdp_mpwqe_complete(sq);

			mlx5e_xsk_tx_post_err(sq, &xdpi);
		}

		flush = true;
	}

	if (flush) {
		if (sq->mpwqe.wqe)
			mlx5e_xdp_mpwqe_complete(sq);
		mlx5e_xmit_xdp_doorbell(sq);

		xsk_umem_consume_tx_done(umem);
	}

	return !(budget && work_done);
}