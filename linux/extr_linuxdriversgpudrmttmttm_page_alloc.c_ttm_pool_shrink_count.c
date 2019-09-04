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
struct ttm_page_pool {unsigned long npages; unsigned long order; } ;
struct shrinker {int dummy; } ;
struct shrink_control {int dummy; } ;
struct TYPE_2__ {struct ttm_page_pool* pools; } ;

/* Variables and functions */
 unsigned int NUM_POOLS ; 
 TYPE_1__* _manager ; 

__attribute__((used)) static unsigned long
ttm_pool_shrink_count(struct shrinker *shrink, struct shrink_control *sc)
{
	unsigned i;
	unsigned long count = 0;
	struct ttm_page_pool *pool;

	for (i = 0; i < NUM_POOLS; ++i) {
		pool = &_manager->pools[i];
		count += (pool->npages << pool->order);
	}

	return count;
}