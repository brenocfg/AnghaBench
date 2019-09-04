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
typedef  int u32 ;
struct xdp_frame {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct mlx5e_xdpsq {int /*<<< orphan*/  pdev; } ;
struct mlx5e_xdp_info {int /*<<< orphan*/  dma_addr; struct xdp_frame* xdpf; } ;
struct TYPE_4__ {int num; TYPE_1__** c; } ;
struct mlx5e_priv {TYPE_2__ channels; } ;
struct TYPE_3__ {struct mlx5e_xdpsq xdpsq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENXIO ; 
 int XDP_XMIT_FLAGS_MASK ; 
 int XDP_XMIT_FLUSH ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_xdp_tx_is_enabled (struct mlx5e_priv*) ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_doorbell (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_frame (struct mlx5e_xdpsq*,struct mlx5e_xdp_info*) ; 
 struct mlx5e_priv* netdev_priv (struct net_device*) ; 
 int smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xdp_return_frame_rx_napi (struct xdp_frame*) ; 

int mlx5e_xdp_xmit(struct net_device *dev, int n, struct xdp_frame **frames,
		   u32 flags)
{
	struct mlx5e_priv *priv = netdev_priv(dev);
	struct mlx5e_xdpsq *sq;
	int drops = 0;
	int sq_num;
	int i;

	/* this flag is sufficient, no need to test internal sq state */
	if (unlikely(!mlx5e_xdp_tx_is_enabled(priv)))
		return -ENETDOWN;

	if (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		return -EINVAL;

	sq_num = smp_processor_id();

	if (unlikely(sq_num >= priv->channels.num))
		return -ENXIO;

	sq = &priv->channels.c[sq_num]->xdpsq;

	for (i = 0; i < n; i++) {
		struct xdp_frame *xdpf = frames[i];
		struct mlx5e_xdp_info xdpi;

		xdpi.dma_addr = dma_map_single(sq->pdev, xdpf->data, xdpf->len,
					       DMA_TO_DEVICE);
		if (unlikely(dma_mapping_error(sq->pdev, xdpi.dma_addr))) {
			xdp_return_frame_rx_napi(xdpf);
			drops++;
			continue;
		}

		xdpi.xdpf = xdpf;

		if (unlikely(!mlx5e_xmit_xdp_frame(sq, &xdpi))) {
			dma_unmap_single(sq->pdev, xdpi.dma_addr,
					 xdpf->len, DMA_TO_DEVICE);
			xdp_return_frame_rx_napi(xdpf);
			drops++;
		}
	}

	if (flags & XDP_XMIT_FLUSH)
		mlx5e_xmit_xdp_doorbell(sq);

	return n - drops;
}