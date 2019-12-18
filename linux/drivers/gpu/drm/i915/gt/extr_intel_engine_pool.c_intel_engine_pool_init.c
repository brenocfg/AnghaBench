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
struct intel_engine_pool {int /*<<< orphan*/ * cache_list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void intel_engine_pool_init(struct intel_engine_pool *pool)
{
	int n;

	spin_lock_init(&pool->lock);
	for (n = 0; n < ARRAY_SIZE(pool->cache_list); n++)
		INIT_LIST_HEAD(&pool->cache_list[n]);
}