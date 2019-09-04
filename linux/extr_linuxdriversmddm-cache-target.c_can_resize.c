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
struct cache {int /*<<< orphan*/  cache_size; scalar_t__ sized; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 scalar_t__ from_cblock (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dirty (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_cblock (scalar_t__) ; 

__attribute__((used)) static bool can_resize(struct cache *cache, dm_cblock_t new_size)
{
	if (from_cblock(new_size) > from_cblock(cache->cache_size)) {
		if (cache->sized) {
			DMERR("%s: unable to extend cache due to missing cache table reload",
			      cache_device_name(cache));
			return false;
		}
	}

	/*
	 * We can't drop a dirty block when shrinking the cache.
	 */
	while (from_cblock(new_size) < from_cblock(cache->cache_size)) {
		new_size = to_cblock(from_cblock(new_size) + 1);
		if (is_dirty(cache, new_size)) {
			DMERR("%s: unable to shrink cache; cache block %llu is dirty",
			      cache_device_name(cache),
			      (unsigned long long) from_cblock(new_size));
			return false;
		}
	}

	return true;
}