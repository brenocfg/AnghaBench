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
struct mlx4_en_rx_alloc {scalar_t__ page; int /*<<< orphan*/  dma; } ;
struct mlx4_en_priv {int /*<<< orphan*/  dma_dir; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  __free_page (scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx4_en_rx_alloc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mlx4_en_free_frag(const struct mlx4_en_priv *priv,
			      struct mlx4_en_rx_alloc *frag)
{
	if (frag->page) {
		dma_unmap_page(priv->ddev, frag->dma,
			       PAGE_SIZE, priv->dma_dir);
		__free_page(frag->page);
	}
	/* We need to clear all fields, otherwise a change of priv->log_rx_info
	 * could lead to see garbage later in frag->page.
	 */
	memset(frag, 0, sizeof(*frag));
}