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
struct dmaengine_unmap_pool {int /*<<< orphan*/ * cache; int /*<<< orphan*/ * pool; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct dmaengine_unmap_pool*) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ *) ; 
 struct dmaengine_unmap_pool* unmap_pool ; 

__attribute__((used)) static void dmaengine_destroy_unmap_pool(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(unmap_pool); i++) {
		struct dmaengine_unmap_pool *p = &unmap_pool[i];

		mempool_destroy(p->pool);
		p->pool = NULL;
		kmem_cache_destroy(p->cache);
		p->cache = NULL;
	}
}