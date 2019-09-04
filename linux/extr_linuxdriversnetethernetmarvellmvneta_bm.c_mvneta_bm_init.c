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
struct mvneta_bm_pool {int dummy; } ;
struct mvneta_bm {int /*<<< orphan*/  bm_pools; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MVNETA_BM_POOLS_NUM ; 
 int /*<<< orphan*/  devm_kcalloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvneta_bm_default_set (struct mvneta_bm*) ; 
 int /*<<< orphan*/  mvneta_bm_pools_init (struct mvneta_bm*) ; 

__attribute__((used)) static int mvneta_bm_init(struct mvneta_bm *priv)
{
	mvneta_bm_default_set(priv);

	/* Allocate and initialize BM pools structures */
	priv->bm_pools = devm_kcalloc(&priv->pdev->dev, MVNETA_BM_POOLS_NUM,
				      sizeof(struct mvneta_bm_pool),
				      GFP_KERNEL);
	if (!priv->bm_pools)
		return -ENOMEM;

	mvneta_bm_pools_init(priv);

	return 0;
}