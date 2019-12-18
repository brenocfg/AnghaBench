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
struct cache {int /*<<< orphan*/  nr_allocated_migrations; int /*<<< orphan*/  migration_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct dm_cache_migration* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct dm_cache_migration*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct dm_cache_migration *alloc_migration(struct cache *cache)
{
	struct dm_cache_migration *mg;

	mg = mempool_alloc(&cache->migration_pool, GFP_NOIO);

	memset(mg, 0, sizeof(*mg));

	mg->cache = cache;
	atomic_inc(&cache->nr_allocated_migrations);

	return mg;
}