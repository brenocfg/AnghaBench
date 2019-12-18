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
typedef  size_t u32 ;
struct xdp_umem {size_t npgs; TYPE_1__* pages; int /*<<< orphan*/ * pgs; } ;
struct mlx5e_priv {TYPE_2__* mdev; } ;
struct device {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_4__ {struct device* device; } ;
struct TYPE_3__ {scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ dma_map_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5e_xsk_map_umem(struct mlx5e_priv *priv,
			      struct xdp_umem *umem)
{
	struct device *dev = priv->mdev->device;
	u32 i;

	for (i = 0; i < umem->npgs; i++) {
		dma_addr_t dma = dma_map_page(dev, umem->pgs[i], 0, PAGE_SIZE,
					      DMA_BIDIRECTIONAL);

		if (unlikely(dma_mapping_error(dev, dma)))
			goto err_unmap;
		umem->pages[i].dma = dma;
	}

	return 0;

err_unmap:
	while (i--) {
		dma_unmap_page(dev, umem->pages[i].dma, PAGE_SIZE,
			       DMA_BIDIRECTIONAL);
		umem->pages[i].dma = 0;
	}

	return -ENOMEM;
}