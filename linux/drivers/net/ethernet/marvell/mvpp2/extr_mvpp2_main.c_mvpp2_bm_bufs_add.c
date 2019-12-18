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
struct mvpp2_port {int /*<<< orphan*/  dev; TYPE_1__* priv; } ;
struct mvpp2_bm_pool {scalar_t__ pkt_size; scalar_t__ buf_num; scalar_t__ size; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {scalar_t__ percpu_pools; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ MVPP2_BM_LONG_PKT_SIZE ; 
 int MVPP2_RX_BUF_SIZE (scalar_t__) ; 
 int MVPP2_RX_TOTAL_SIZE (int) ; 
 int /*<<< orphan*/  mvpp2_bm_pool_put (struct mvpp2_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* mvpp2_buf_alloc (struct mvpp2_port*,struct mvpp2_bm_pool*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int mvpp2_bm_bufs_add(struct mvpp2_port *port,
			     struct mvpp2_bm_pool *bm_pool, int buf_num)
{
	int i, buf_size, total_size;
	dma_addr_t dma_addr;
	phys_addr_t phys_addr;
	void *buf;

	if (port->priv->percpu_pools &&
	    bm_pool->pkt_size > MVPP2_BM_LONG_PKT_SIZE) {
		netdev_err(port->dev,
			   "attempted to use jumbo frames with per-cpu pools");
		return 0;
	}

	buf_size = MVPP2_RX_BUF_SIZE(bm_pool->pkt_size);
	total_size = MVPP2_RX_TOTAL_SIZE(buf_size);

	if (buf_num < 0 ||
	    (buf_num + bm_pool->buf_num > bm_pool->size)) {
		netdev_err(port->dev,
			   "cannot allocate %d buffers for pool %d\n",
			   buf_num, bm_pool->id);
		return 0;
	}

	for (i = 0; i < buf_num; i++) {
		buf = mvpp2_buf_alloc(port, bm_pool, &dma_addr,
				      &phys_addr, GFP_KERNEL);
		if (!buf)
			break;

		mvpp2_bm_pool_put(port, bm_pool->id, dma_addr,
				  phys_addr);
	}

	/* Update BM driver with number of buffers added to pool */
	bm_pool->buf_num += i;

	netdev_dbg(port->dev,
		   "pool %d: pkt_size=%4d, buf_size=%4d, total_size=%4d\n",
		   bm_pool->id, bm_pool->pkt_size, buf_size, total_size);

	netdev_dbg(port->dev,
		   "pool %d: %d of %d buffers added\n",
		   bm_pool->id, i, buf_num);
	return i;
}