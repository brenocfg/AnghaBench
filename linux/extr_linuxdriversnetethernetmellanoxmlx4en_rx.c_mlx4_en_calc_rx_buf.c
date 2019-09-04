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
struct net_device {int /*<<< orphan*/  mtu; } ;
struct mlx4_en_rx_alloc {int dummy; } ;
struct mlx4_en_priv {int num_frags; int rx_skb_size; TYPE_1__* frag_info; int /*<<< orphan*/  log_rx_info; scalar_t__ rx_headroom; int /*<<< orphan*/  dma_dir; scalar_t__* tx_ring_num; } ;
struct TYPE_2__ {int frag_size; int frag_stride; } ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int /*<<< orphan*/  DRV ; 
 int MLX4_EN_EFF_MTU (int /*<<< orphan*/ ) ; 
 int MLX4_EN_MAX_RX_FRAGS ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  ROUNDUP_LOG2 (int) ; 
 int SMP_CACHE_BYTES ; 
 size_t TX_XDP ; 
 scalar_t__ XDP_PACKET_HEADROOM ; 
 int /*<<< orphan*/  en_dbg (int /*<<< orphan*/ ,struct mlx4_en_priv*,char*,int,int,...) ; 
 int min (int,int) ; 
 struct mlx4_en_priv* netdev_priv (struct net_device*) ; 

void mlx4_en_calc_rx_buf(struct net_device *dev)
{
	struct mlx4_en_priv *priv = netdev_priv(dev);
	int eff_mtu = MLX4_EN_EFF_MTU(dev->mtu);
	int i = 0;

	/* bpf requires buffers to be set up as 1 packet per page.
	 * This only works when num_frags == 1.
	 */
	if (priv->tx_ring_num[TX_XDP]) {
		priv->frag_info[0].frag_size = eff_mtu;
		/* This will gain efficient xdp frame recycling at the
		 * expense of more costly truesize accounting
		 */
		priv->frag_info[0].frag_stride = PAGE_SIZE;
		priv->dma_dir = PCI_DMA_BIDIRECTIONAL;
		priv->rx_headroom = XDP_PACKET_HEADROOM;
		i = 1;
	} else {
		int frag_size_max = 2048, buf_size = 0;

		/* should not happen, right ? */
		if (eff_mtu > PAGE_SIZE + (MLX4_EN_MAX_RX_FRAGS - 1) * 2048)
			frag_size_max = PAGE_SIZE;

		while (buf_size < eff_mtu) {
			int frag_stride, frag_size = eff_mtu - buf_size;
			int pad, nb;

			if (i < MLX4_EN_MAX_RX_FRAGS - 1)
				frag_size = min(frag_size, frag_size_max);

			priv->frag_info[i].frag_size = frag_size;
			frag_stride = ALIGN(frag_size, SMP_CACHE_BYTES);
			/* We can only pack 2 1536-bytes frames in on 4K page
			 * Therefore, each frame would consume more bytes (truesize)
			 */
			nb = PAGE_SIZE / frag_stride;
			pad = (PAGE_SIZE - nb * frag_stride) / nb;
			pad &= ~(SMP_CACHE_BYTES - 1);
			priv->frag_info[i].frag_stride = frag_stride + pad;

			buf_size += frag_size;
			i++;
		}
		priv->dma_dir = PCI_DMA_FROMDEVICE;
		priv->rx_headroom = 0;
	}

	priv->num_frags = i;
	priv->rx_skb_size = eff_mtu;
	priv->log_rx_info = ROUNDUP_LOG2(i * sizeof(struct mlx4_en_rx_alloc));

	en_dbg(DRV, priv, "Rx buffer scatter-list (effective-mtu:%d num_frags:%d):\n",
	       eff_mtu, priv->num_frags);
	for (i = 0; i < priv->num_frags; i++) {
		en_dbg(DRV,
		       priv,
		       "  frag:%d - size:%d stride:%d\n",
		       i,
		       priv->frag_info[i].frag_size,
		       priv->frag_info[i].frag_stride);
	}
}