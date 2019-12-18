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
struct xdp_umem {size_t npgs; TYPE_2__* pages; } ;
struct mlx5e_priv {TYPE_1__* mdev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {scalar_t__ dma; } ;
struct TYPE_3__ {struct device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5e_xsk_unmap_umem(struct mlx5e_priv *priv,
				 struct xdp_umem *umem)
{
	struct device *dev = priv->mdev->device;
	u32 i;

	for (i = 0; i < umem->npgs; i++) {
		dma_unmap_page(dev, umem->pages[i].dma, PAGE_SIZE,
			       DMA_BIDIRECTIONAL);
		umem->pages[i].dma = 0;
	}
}