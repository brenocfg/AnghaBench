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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mlx5e_xdp_info_fifo {int dummy; } ;
struct TYPE_7__ {struct mlx5e_xdp_info_fifo xdpi_fifo; } ;
struct mlx5e_xdpsq {int /*<<< orphan*/  pdev; TYPE_3__ db; } ;
struct mlx5e_xdp_wqe_info {scalar_t__ num_pkts; } ;
struct TYPE_6__ {int /*<<< orphan*/  di; int /*<<< orphan*/  rq; } ;
struct TYPE_5__ {TYPE_4__* xdpf; int /*<<< orphan*/  dma_addr; } ;
struct mlx5e_xdp_info {int mode; TYPE_2__ page; TYPE_1__ frame; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
#define  MLX5E_XDP_XMIT_MODE_FRAME 130 
#define  MLX5E_XDP_XMIT_MODE_PAGE 129 
#define  MLX5E_XDP_XMIT_MODE_XSK 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_page_release_dynamic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mlx5e_xdp_info mlx5e_xdpi_fifo_pop (struct mlx5e_xdp_info_fifo*) ; 
 int /*<<< orphan*/  xdp_return_frame (TYPE_4__*) ; 

__attribute__((used)) static void mlx5e_free_xdpsq_desc(struct mlx5e_xdpsq *sq,
				  struct mlx5e_xdp_wqe_info *wi,
				  u32 *xsk_frames,
				  bool recycle)
{
	struct mlx5e_xdp_info_fifo *xdpi_fifo = &sq->db.xdpi_fifo;
	u16 i;

	for (i = 0; i < wi->num_pkts; i++) {
		struct mlx5e_xdp_info xdpi = mlx5e_xdpi_fifo_pop(xdpi_fifo);

		switch (xdpi.mode) {
		case MLX5E_XDP_XMIT_MODE_FRAME:
			/* XDP_TX from the XSK RQ and XDP_REDIRECT */
			dma_unmap_single(sq->pdev, xdpi.frame.dma_addr,
					 xdpi.frame.xdpf->len, DMA_TO_DEVICE);
			xdp_return_frame(xdpi.frame.xdpf);
			break;
		case MLX5E_XDP_XMIT_MODE_PAGE:
			/* XDP_TX from the regular RQ */
			mlx5e_page_release_dynamic(xdpi.page.rq, &xdpi.page.di, recycle);
			break;
		case MLX5E_XDP_XMIT_MODE_XSK:
			/* AF_XDP send */
			(*xsk_frames)++;
			break;
		default:
			WARN_ON_ONCE(true);
		}
	}
}