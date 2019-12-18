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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int buf_num; } ;
struct mvneta_bm_pool {int port_map; TYPE_2__ hwbm_pool; int /*<<< orphan*/  buf_size; } ;
struct mvneta_bm {TYPE_1__* pdev; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  MVNETA_BM_EMPTY_LIMIT_MASK ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwbm_buf_free (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvneta_bm_config_clear (struct mvneta_bm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_config_set (struct mvneta_bm*,int /*<<< orphan*/ ) ; 
 scalar_t__ mvneta_bm_pool_get_bp (struct mvneta_bm*,struct mvneta_bm_pool*) ; 
 int /*<<< orphan*/ * phys_to_virt (scalar_t__) ; 

void mvneta_bm_bufs_free(struct mvneta_bm *priv, struct mvneta_bm_pool *bm_pool,
			 u8 port_map)
{
	int i;

	bm_pool->port_map &= ~port_map;
	if (bm_pool->port_map)
		return;

	mvneta_bm_config_set(priv, MVNETA_BM_EMPTY_LIMIT_MASK);

	for (i = 0; i < bm_pool->hwbm_pool.buf_num; i++) {
		dma_addr_t buf_phys_addr;
		u32 *vaddr;

		/* Get buffer physical address (indirect access) */
		buf_phys_addr = mvneta_bm_pool_get_bp(priv, bm_pool);

		/* Work-around to the problems when destroying the pool,
		 * when it occurs that a read access to BPPI returns 0.
		 */
		if (buf_phys_addr == 0)
			continue;

		vaddr = phys_to_virt(buf_phys_addr);
		if (!vaddr)
			break;

		dma_unmap_single(&priv->pdev->dev, buf_phys_addr,
				 bm_pool->buf_size, DMA_FROM_DEVICE);
		hwbm_buf_free(&bm_pool->hwbm_pool, vaddr);
	}

	mvneta_bm_config_clear(priv, MVNETA_BM_EMPTY_LIMIT_MASK);

	/* Update BM driver with number of buffers removed from pool */
	bm_pool->hwbm_pool.buf_num -= i;
}