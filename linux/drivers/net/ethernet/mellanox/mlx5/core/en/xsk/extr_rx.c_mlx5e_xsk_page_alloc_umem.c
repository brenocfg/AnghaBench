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
typedef  int /*<<< orphan*/  u64 ;
struct xdp_umem {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  umem_headroom; } ;
struct mlx5e_rq {int /*<<< orphan*/  pdev; TYPE_2__ buff; struct xdp_umem* umem; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  data; } ;
struct mlx5e_dma_info {int /*<<< orphan*/  addr; TYPE_1__ xsk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_umem_get_data (struct xdp_umem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_umem_get_dma (struct xdp_umem*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem_adjust_offset (struct xdp_umem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem_discard_addr_rq (struct xdp_umem*) ; 
 int /*<<< orphan*/  xsk_umem_peek_addr_rq (struct xdp_umem*,int /*<<< orphan*/ *) ; 

int mlx5e_xsk_page_alloc_umem(struct mlx5e_rq *rq,
			      struct mlx5e_dma_info *dma_info)
{
	struct xdp_umem *umem = rq->umem;
	u64 handle;

	if (!xsk_umem_peek_addr_rq(umem, &handle))
		return -ENOMEM;

	dma_info->xsk.handle = xsk_umem_adjust_offset(umem, handle,
						      rq->buff.umem_headroom);
	dma_info->xsk.data = xdp_umem_get_data(umem, dma_info->xsk.handle);

	/* No need to add headroom to the DMA address. In striding RQ case, we
	 * just provide pages for UMR, and headroom is counted at the setup
	 * stage when creating a WQE. In non-striding RQ case, headroom is
	 * accounted in mlx5e_alloc_rx_wqe.
	 */
	dma_info->addr = xdp_umem_get_dma(umem, handle);

	xsk_umem_discard_addr_rq(umem);

	dma_sync_single_for_device(rq->pdev, dma_info->addr, PAGE_SIZE,
				   DMA_BIDIRECTIONAL);

	return 0;
}