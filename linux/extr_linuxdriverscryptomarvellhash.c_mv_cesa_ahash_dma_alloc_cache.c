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
struct mv_cesa_ahash_dma_req {int /*<<< orphan*/  cache; int /*<<< orphan*/  cache_dma; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {TYPE_1__* dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  cache_pool; } ;

/* Variables and functions */
 int ENOMEM ; 
 TYPE_2__* cesa_dev ; 
 int /*<<< orphan*/  dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int
mv_cesa_ahash_dma_alloc_cache(struct mv_cesa_ahash_dma_req *req, gfp_t flags)
{
	req->cache = dma_pool_alloc(cesa_dev->dma->cache_pool, flags,
				    &req->cache_dma);
	if (!req->cache)
		return -ENOMEM;

	return 0;
}