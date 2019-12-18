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
struct dm_cache_statistics {void* write_misses; void* write_hits; void* read_misses; void* read_hits; } ;
struct TYPE_2__ {int /*<<< orphan*/  write_miss; int /*<<< orphan*/  write_hit; int /*<<< orphan*/  read_miss; int /*<<< orphan*/  read_hit; } ;
struct cache {int /*<<< orphan*/  cmd; TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_cache_metadata_set_stats (int /*<<< orphan*/ ,struct dm_cache_statistics*) ; 
 scalar_t__ get_cache_mode (struct cache*) ; 

__attribute__((used)) static void save_stats(struct cache *cache)
{
	struct dm_cache_statistics stats;

	if (get_cache_mode(cache) >= CM_READ_ONLY)
		return;

	stats.read_hits = atomic_read(&cache->stats.read_hit);
	stats.read_misses = atomic_read(&cache->stats.read_miss);
	stats.write_hits = atomic_read(&cache->stats.write_hit);
	stats.write_misses = atomic_read(&cache->stats.write_miss);

	dm_cache_metadata_set_stats(cache->cmd, &stats);
}