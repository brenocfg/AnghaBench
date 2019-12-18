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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct hwbm_pool {int size; scalar_t__ buf_num; } ;
struct mvneta_bm_pool {int port_map; int /*<<< orphan*/  id; int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  phys_addr; int /*<<< orphan*/  type; struct hwbm_pool hwbm_pool; } ;
struct mvneta_bm {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_BM_FREE ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_bufs_free (struct mvneta_bm*,struct mvneta_bm_pool*,int) ; 
 int /*<<< orphan*/  mvneta_bm_pool_disable (struct mvneta_bm*,int /*<<< orphan*/ ) ; 

void mvneta_bm_pool_destroy(struct mvneta_bm *priv,
			    struct mvneta_bm_pool *bm_pool, u8 port_map)
{
	struct hwbm_pool *hwbm_pool = &bm_pool->hwbm_pool;
	bm_pool->port_map &= ~port_map;
	if (bm_pool->port_map)
		return;

	bm_pool->type = MVNETA_BM_FREE;

	mvneta_bm_bufs_free(priv, bm_pool, port_map);
	if (hwbm_pool->buf_num)
		WARN(1, "cannot free all buffers in pool %d\n", bm_pool->id);

	if (bm_pool->virt_addr) {
		dma_free_coherent(&priv->pdev->dev,
				  sizeof(u32) * hwbm_pool->size,
				  bm_pool->virt_addr, bm_pool->phys_addr);
		bm_pool->virt_addr = NULL;
	}

	mvneta_bm_pool_disable(priv, bm_pool->id);
}