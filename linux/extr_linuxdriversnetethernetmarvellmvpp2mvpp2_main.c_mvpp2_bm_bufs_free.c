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
struct mvpp2_bm_pool {int buf_num; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  id; } ;
struct mvpp2 {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_bm_bufs_get_addrs (struct device*,struct mvpp2*,struct mvpp2_bm_pool*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mvpp2_frag_free (struct mvpp2_bm_pool*,void*) ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvpp2_bm_bufs_free(struct device *dev, struct mvpp2 *priv,
			       struct mvpp2_bm_pool *bm_pool, int buf_num)
{
	int i;

	if (buf_num > bm_pool->buf_num) {
		WARN(1, "Pool does not have so many bufs pool(%d) bufs(%d)\n",
		     bm_pool->id, buf_num);
		buf_num = bm_pool->buf_num;
	}

	for (i = 0; i < buf_num; i++) {
		dma_addr_t buf_dma_addr;
		phys_addr_t buf_phys_addr;
		void *data;

		mvpp2_bm_bufs_get_addrs(dev, priv, bm_pool,
					&buf_dma_addr, &buf_phys_addr);

		dma_unmap_single(dev, buf_dma_addr,
				 bm_pool->buf_size, DMA_FROM_DEVICE);

		data = (void *)phys_to_virt(buf_phys_addr);
		if (!data)
			break;

		mvpp2_frag_free(bm_pool, data);
	}

	/* Update BM driver with number of buffers removed from pool */
	bm_pool->buf_num -= i;
}