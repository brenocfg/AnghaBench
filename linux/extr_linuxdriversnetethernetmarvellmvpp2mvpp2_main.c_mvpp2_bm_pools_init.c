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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mvpp2_bm_pool {int id; } ;
struct mvpp2 {struct mvpp2_bm_pool* bm_pools; } ;

/* Variables and functions */
 int MVPP2_BM_POOLS_NUM ; 
 int MVPP2_BM_POOL_SIZE_MAX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  mvpp2_bm_pool_bufsize_set (struct mvpp2*,struct mvpp2_bm_pool*,int /*<<< orphan*/ ) ; 
 int mvpp2_bm_pool_create (struct platform_device*,struct mvpp2*,struct mvpp2_bm_pool*,int) ; 
 int /*<<< orphan*/  mvpp2_bm_pool_destroy (struct platform_device*,struct mvpp2*,struct mvpp2_bm_pool*) ; 

__attribute__((used)) static int mvpp2_bm_pools_init(struct platform_device *pdev,
			       struct mvpp2 *priv)
{
	int i, err, size;
	struct mvpp2_bm_pool *bm_pool;

	/* Create all pools with maximum size */
	size = MVPP2_BM_POOL_SIZE_MAX;
	for (i = 0; i < MVPP2_BM_POOLS_NUM; i++) {
		bm_pool = &priv->bm_pools[i];
		bm_pool->id = i;
		err = mvpp2_bm_pool_create(pdev, priv, bm_pool, size);
		if (err)
			goto err_unroll_pools;
		mvpp2_bm_pool_bufsize_set(priv, bm_pool, 0);
	}
	return 0;

err_unroll_pools:
	dev_err(&pdev->dev, "failed to create BM pool %d, size %d\n", i, size);
	for (i = i - 1; i >= 0; i--)
		mvpp2_bm_pool_destroy(pdev, priv, &priv->bm_pools[i]);
	return err;
}