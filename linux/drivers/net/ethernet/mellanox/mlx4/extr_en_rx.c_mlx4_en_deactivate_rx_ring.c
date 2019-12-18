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
struct TYPE_3__ {int index; TYPE_2__* buf; } ;
struct mlx4_en_rx_ring {scalar_t__ stride; int /*<<< orphan*/  buf; TYPE_1__ page_cache; } ;
struct mlx4_en_priv {int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  ddev; } ;
struct TYPE_4__ {int /*<<< orphan*/  page; int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ TXBB_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_en_free_rx_buf (struct mlx4_en_priv*,struct mlx4_en_rx_ring*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

void mlx4_en_deactivate_rx_ring(struct mlx4_en_priv *priv,
				struct mlx4_en_rx_ring *ring)
{
	int i;

	for (i = 0; i < ring->page_cache.index; i++) {
		dma_unmap_page(priv->ddev, ring->page_cache.buf[i].dma,
			       PAGE_SIZE, priv->dma_dir);
		put_page(ring->page_cache.buf[i].page);
	}
	ring->page_cache.index = 0;
	mlx4_en_free_rx_buf(priv, ring);
	if (ring->stride <= TXBB_SIZE)
		ring->buf -= TXBB_SIZE;
}