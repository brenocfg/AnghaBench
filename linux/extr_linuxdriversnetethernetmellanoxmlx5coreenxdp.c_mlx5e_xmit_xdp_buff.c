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
struct xdp_buff {int dummy; } ;
struct mlx5e_xdpsq {int /*<<< orphan*/  pdev; } ;
struct mlx5e_dma_info {int addr; } ;
struct mlx5e_xdp_info {int dma_addr; struct mlx5e_dma_info di; TYPE_1__* xdpf; } ;
struct TYPE_2__ {void* data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 TYPE_1__* convert_to_xdp_frame (struct xdp_buff*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5e_xmit_xdp_frame (struct mlx5e_xdpsq*,struct mlx5e_xdp_info*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline bool
mlx5e_xmit_xdp_buff(struct mlx5e_xdpsq *sq, struct mlx5e_dma_info *di,
		    struct xdp_buff *xdp)
{
	struct mlx5e_xdp_info xdpi;

	xdpi.xdpf = convert_to_xdp_frame(xdp);
	if (unlikely(!xdpi.xdpf))
		return false;
	xdpi.dma_addr = di->addr + (xdpi.xdpf->data - (void *)xdpi.xdpf);
	dma_sync_single_for_device(sq->pdev, xdpi.dma_addr,
				   xdpi.xdpf->len, PCI_DMA_TODEVICE);
	xdpi.di = *di;

	return mlx5e_xmit_xdp_frame(sq, &xdpi);
}