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
struct dm_cache_statistics {int /*<<< orphan*/  write_misses; int /*<<< orphan*/  write_hits; int /*<<< orphan*/  read_misses; int /*<<< orphan*/  read_hits; } ;
struct TYPE_2__ {int /*<<< orphan*/  write_miss; int /*<<< orphan*/  write_hit; int /*<<< orphan*/  read_miss; int /*<<< orphan*/  read_hit; } ;
struct cache {TYPE_1__ stats; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_cache_metadata_get_stats (int /*<<< orphan*/ ,struct dm_cache_statistics*) ; 

__attribute__((used)) static void load_stats(struct cache *cache)
{
	struct dm_cache_statistics stats;

	dm_cache_metadata_get_stats(cache->cmd, &stats);
	atomic_set(&cache->stats.read_hit, stats.read_hits);
	atomic_set(&cache->stats.read_miss, stats.read_misses);
	atomic_set(&cache->stats.write_hit, stats.write_hits);
	atomic_set(&cache->stats.write_miss, stats.write_misses);
}