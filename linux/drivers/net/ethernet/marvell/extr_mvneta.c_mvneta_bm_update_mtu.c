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
struct skb_shared_info {int dummy; } ;
struct mvneta_port {int id; int /*<<< orphan*/  dev; int /*<<< orphan*/ * bm_priv; struct mvneta_bm_pool* pool_short; struct mvneta_bm_pool* pool_long; } ;
struct hwbm_pool {int size; scalar_t__ frag_size; scalar_t__ buf_num; } ;
struct mvneta_bm_pool {int buf_size; int /*<<< orphan*/  id; int /*<<< orphan*/  pkt_size; struct hwbm_pool hwbm_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_ACC_MODE ; 
 int /*<<< orphan*/  MVNETA_ACC_MODE_EXT1 ; 
 int MVNETA_RX_BUF_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MVNETA_RX_PKT_SIZE (int) ; 
 scalar_t__ SKB_DATA_ALIGN (int) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,...) ; 
 int hwbm_pool_add (struct hwbm_pool*,int) ; 
 int /*<<< orphan*/  mvneta_bm_bufs_free (int /*<<< orphan*/ *,struct mvneta_bm_pool*,int) ; 
 int /*<<< orphan*/  mvneta_bm_pool_bufsize_set (struct mvneta_port*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_pool_destroy (int /*<<< orphan*/ *,struct mvneta_bm_pool*,int) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void mvneta_bm_update_mtu(struct mvneta_port *pp, int mtu)
{
	struct mvneta_bm_pool *bm_pool = pp->pool_long;
	struct hwbm_pool *hwbm_pool = &bm_pool->hwbm_pool;
	int num;

	/* Release all buffers from long pool */
	mvneta_bm_bufs_free(pp->bm_priv, bm_pool, 1 << pp->id);
	if (hwbm_pool->buf_num) {
		WARN(1, "cannot free all buffers in pool %d\n",
		     bm_pool->id);
		goto bm_mtu_err;
	}

	bm_pool->pkt_size = MVNETA_RX_PKT_SIZE(mtu);
	bm_pool->buf_size = MVNETA_RX_BUF_SIZE(bm_pool->pkt_size);
	hwbm_pool->frag_size = SKB_DATA_ALIGN(sizeof(struct skb_shared_info)) +
			SKB_DATA_ALIGN(MVNETA_RX_BUF_SIZE(bm_pool->pkt_size));

	/* Fill entire long pool */
	num = hwbm_pool_add(hwbm_pool, hwbm_pool->size);
	if (num != hwbm_pool->size) {
		WARN(1, "pool %d: %d of %d allocated\n",
		     bm_pool->id, num, hwbm_pool->size);
		goto bm_mtu_err;
	}
	mvneta_bm_pool_bufsize_set(pp, bm_pool->buf_size, bm_pool->id);

	return;

bm_mtu_err:
	mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_long, 1 << pp->id);
	mvneta_bm_pool_destroy(pp->bm_priv, pp->pool_short, 1 << pp->id);

	pp->bm_priv = NULL;
	mvreg_write(pp, MVNETA_ACC_MODE, MVNETA_ACC_MODE_EXT1);
	netdev_info(pp->dev, "fail to update MTU, fall back to software BM\n");
}