#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct skb_shared_hwtstamps {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  users; } ;
struct mlx4_wqe_data_seg {int /*<<< orphan*/  byte_count; int /*<<< orphan*/  addr; } ;
struct mlx4_en_tx_ring {int buf_size; struct mlx4_wqe_data_seg* buf; struct mlx4_en_tx_info* tx_info; } ;
struct mlx4_en_tx_info {int data_offset; int nr_maps; int nr_txbb; int /*<<< orphan*/  map0_byte_count; int /*<<< orphan*/  map0_dma; scalar_t__ linear; int /*<<< orphan*/  inl; struct sk_buff* skb; } ;
struct mlx4_en_tx_desc {int /*<<< orphan*/  byte_count; int /*<<< orphan*/  addr; } ;
struct mlx4_en_priv {int /*<<< orphan*/  ddev; int /*<<< orphan*/  mdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int LOG_TXBB_SIZE ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mlx4_en_fill_hwtstamps (int /*<<< orphan*/ ,struct skb_shared_hwtstamps*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_consume_skb (struct sk_buff*,int) ; 
 int /*<<< orphan*/  prefetchw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_tstamp_tx (struct sk_buff*,struct skb_shared_hwtstamps*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

u32 mlx4_en_free_tx_desc(struct mlx4_en_priv *priv,
			 struct mlx4_en_tx_ring *ring,
			 int index, u64 timestamp,
			 int napi_mode)
{
	struct mlx4_en_tx_info *tx_info = &ring->tx_info[index];
	struct mlx4_en_tx_desc *tx_desc = ring->buf + (index << LOG_TXBB_SIZE);
	struct mlx4_wqe_data_seg *data = (void *) tx_desc + tx_info->data_offset;
	void *end = ring->buf + ring->buf_size;
	struct sk_buff *skb = tx_info->skb;
	int nr_maps = tx_info->nr_maps;
	int i;

	/* We do not touch skb here, so prefetch skb->users location
	 * to speedup consume_skb()
	 */
	prefetchw(&skb->users);

	if (unlikely(timestamp)) {
		struct skb_shared_hwtstamps hwts;

		mlx4_en_fill_hwtstamps(priv->mdev, &hwts, timestamp);
		skb_tstamp_tx(skb, &hwts);
	}

	if (!tx_info->inl) {
		if (tx_info->linear)
			dma_unmap_single(priv->ddev,
					 tx_info->map0_dma,
					 tx_info->map0_byte_count,
					 PCI_DMA_TODEVICE);
		else
			dma_unmap_page(priv->ddev,
				       tx_info->map0_dma,
				       tx_info->map0_byte_count,
				       PCI_DMA_TODEVICE);
		/* Optimize the common case when there are no wraparounds */
		if (likely((void *)tx_desc +
			   (tx_info->nr_txbb << LOG_TXBB_SIZE) <= end)) {
			for (i = 1; i < nr_maps; i++) {
				data++;
				dma_unmap_page(priv->ddev,
					(dma_addr_t)be64_to_cpu(data->addr),
					be32_to_cpu(data->byte_count),
					PCI_DMA_TODEVICE);
			}
		} else {
			if ((void *)data >= end)
				data = ring->buf + ((void *)data - end);

			for (i = 1; i < nr_maps; i++) {
				data++;
				/* Check for wraparound before unmapping */
				if ((void *) data >= end)
					data = ring->buf;
				dma_unmap_page(priv->ddev,
					(dma_addr_t)be64_to_cpu(data->addr),
					be32_to_cpu(data->byte_count),
					PCI_DMA_TODEVICE);
			}
		}
	}
	napi_consume_skb(skb, napi_mode);

	return tx_info->nr_txbb;
}