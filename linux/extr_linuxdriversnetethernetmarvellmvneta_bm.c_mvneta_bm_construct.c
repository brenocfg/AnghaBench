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
typedef  scalar_t__ u32 ;
struct mvneta_bm_pool {int /*<<< orphan*/  buf_size; struct mvneta_bm* priv; } ;
struct mvneta_bm {TYPE_1__* pdev; } ;
struct hwbm_pool {scalar_t__ priv; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_pool_put_bp (struct mvneta_bm*,struct mvneta_bm_pool*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int mvneta_bm_construct(struct hwbm_pool *hwbm_pool, void *buf)
{
	struct mvneta_bm_pool *bm_pool =
		(struct mvneta_bm_pool *)hwbm_pool->priv;
	struct mvneta_bm *priv = bm_pool->priv;
	dma_addr_t phys_addr;

	/* In order to update buf_cookie field of RX descriptor properly,
	 * BM hardware expects buf virtual address to be placed in the
	 * first four bytes of mapped buffer.
	 */
	*(u32 *)buf = (u32)buf;
	phys_addr = dma_map_single(&priv->pdev->dev, buf, bm_pool->buf_size,
				   DMA_FROM_DEVICE);
	if (unlikely(dma_mapping_error(&priv->pdev->dev, phys_addr)))
		return -ENOMEM;

	mvneta_bm_pool_put_bp(priv, bm_pool, phys_addr);
	return 0;
}