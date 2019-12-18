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
struct dm_cache_migration {struct cache* cache; } ;
struct cache {int /*<<< orphan*/  migration_pool; int /*<<< orphan*/  migration_wait; int /*<<< orphan*/  nr_allocated_migrations; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct dm_cache_migration*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_migration(struct dm_cache_migration *mg)
{
	struct cache *cache = mg->cache;

	if (atomic_dec_and_test(&cache->nr_allocated_migrations))
		wake_up(&cache->migration_wait);

	mempool_free(mg, &cache->migration_pool);
}