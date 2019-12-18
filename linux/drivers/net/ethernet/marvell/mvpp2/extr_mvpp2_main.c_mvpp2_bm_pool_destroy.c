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
typedef  int /*<<< orphan*/  u32 ;
struct mvpp2_bm_pool {int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  virt_addr; int /*<<< orphan*/  size_bytes; int /*<<< orphan*/  id; int /*<<< orphan*/  buf_num; } ;
struct mvpp2 {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVPP2_BM_POOL_CTRL_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVPP2_BM_STOP_MASK ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_bm_bufs_free (struct device*,struct mvpp2*,struct mvpp2_bm_pool*,int) ; 
 int mvpp2_check_hw_buf_num (struct mvpp2*,struct mvpp2_bm_pool*) ; 
 int /*<<< orphan*/  mvpp2_read (struct mvpp2*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_write (struct mvpp2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvpp2_bm_pool_destroy(struct device *dev, struct mvpp2 *priv,
				 struct mvpp2_bm_pool *bm_pool)
{
	int buf_num;
	u32 val;

	buf_num = mvpp2_check_hw_buf_num(priv, bm_pool);
	mvpp2_bm_bufs_free(dev, priv, bm_pool, buf_num);

	/* Check buffer counters after free */
	buf_num = mvpp2_check_hw_buf_num(priv, bm_pool);
	if (buf_num) {
		WARN(1, "cannot free all buffers in pool %d, buf_num left %d\n",
		     bm_pool->id, bm_pool->buf_num);
		return 0;
	}

	val = mvpp2_read(priv, MVPP2_BM_POOL_CTRL_REG(bm_pool->id));
	val |= MVPP2_BM_STOP_MASK;
	mvpp2_write(priv, MVPP2_BM_POOL_CTRL_REG(bm_pool->id), val);

	dma_free_coherent(dev, bm_pool->size_bytes,
			  bm_pool->virt_addr,
			  bm_pool->dma_addr);
	return 0;
}