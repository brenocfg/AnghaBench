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
typedef  int /*<<< orphan*/  u32 ;
struct mlx4_en_tx_ring {int /*<<< orphan*/  recycle_ring; struct mlx4_en_tx_info* tx_info; } ;
struct mlx4_en_tx_info {int /*<<< orphan*/  nr_txbb; int /*<<< orphan*/  page; int /*<<< orphan*/  map0_dma; } ;
struct mlx4_en_rx_alloc {int /*<<< orphan*/  dma; int /*<<< orphan*/  page; } ;
struct mlx4_en_priv {int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_rx_recycle (int /*<<< orphan*/ ,struct mlx4_en_rx_alloc*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

u32 mlx4_en_recycle_tx_desc(struct mlx4_en_priv *priv,
			    struct mlx4_en_tx_ring *ring,
			    int index, u64 timestamp,
			    int napi_mode)
{
	struct mlx4_en_tx_info *tx_info = &ring->tx_info[index];
	struct mlx4_en_rx_alloc frame = {
		.page = tx_info->page,
		.dma = tx_info->map0_dma,
	};

	if (!mlx4_en_rx_recycle(ring->recycle_ring, &frame)) {
		dma_unmap_page(priv->ddev, tx_info->map0_dma,
			       PAGE_SIZE, priv->dma_dir);
		put_page(tx_info->page);
	}

	return tx_info->nr_txbb;
}