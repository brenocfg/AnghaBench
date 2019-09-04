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
struct page {int dummy; } ;
struct mlx4_en_rx_alloc {int /*<<< orphan*/  page_offset; int /*<<< orphan*/  dma; struct page* page; } ;
struct mlx4_en_priv {int /*<<< orphan*/  rx_headroom; int /*<<< orphan*/  ddev; int /*<<< orphan*/  dma_dir; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (struct page*) ; 
 struct page* alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mlx4_alloc_page(struct mlx4_en_priv *priv,
			   struct mlx4_en_rx_alloc *frag,
			   gfp_t gfp)
{
	struct page *page;
	dma_addr_t dma;

	page = alloc_page(gfp);
	if (unlikely(!page))
		return -ENOMEM;
	dma = dma_map_page(priv->ddev, page, 0, PAGE_SIZE, priv->dma_dir);
	if (unlikely(dma_mapping_error(priv->ddev, dma))) {
		__free_page(page);
		return -ENOMEM;
	}
	frag->page = page;
	frag->dma = dma;
	frag->page_offset = priv->rx_headroom;
	return 0;
}