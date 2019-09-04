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
struct dm_target {struct cache* private; } ;
struct discard_load_info {int dummy; } ;
struct cache {int sized; scalar_t__ cache_size; int loaded_mappings; int loaded_discards; int /*<<< orphan*/  cmd; int /*<<< orphan*/  discard_nr_blocks; int /*<<< orphan*/  discard_bitset; int /*<<< orphan*/  policy; } ;
typedef  scalar_t__ dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 int /*<<< orphan*/  can_resize (struct cache*,scalar_t__) ; 
 int /*<<< orphan*/  clear_bitset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  discard_load_info_init (struct cache*,struct discard_load_info*) ; 
 int dm_cache_load_discards (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct discard_load_info*) ; 
 int dm_cache_load_mappings (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cache*) ; 
 int /*<<< orphan*/  from_dblock (int /*<<< orphan*/ ) ; 
 scalar_t__ get_cache_dev_size (struct cache*) ; 
 int /*<<< orphan*/  load_discard ; 
 int /*<<< orphan*/  load_mapping ; 
 int /*<<< orphan*/  metadata_operation_failed (struct cache*,char*,int) ; 
 int resize_cache_dev (struct cache*,scalar_t__) ; 
 int /*<<< orphan*/  set_discard_range (struct discard_load_info*) ; 

__attribute__((used)) static int cache_preresume(struct dm_target *ti)
{
	int r = 0;
	struct cache *cache = ti->private;
	dm_cblock_t csize = get_cache_dev_size(cache);

	/*
	 * Check to see if the cache has resized.
	 */
	if (!cache->sized) {
		r = resize_cache_dev(cache, csize);
		if (r)
			return r;

		cache->sized = true;

	} else if (csize != cache->cache_size) {
		if (!can_resize(cache, csize))
			return -EINVAL;

		r = resize_cache_dev(cache, csize);
		if (r)
			return r;
	}

	if (!cache->loaded_mappings) {
		r = dm_cache_load_mappings(cache->cmd, cache->policy,
					   load_mapping, cache);
		if (r) {
			DMERR("%s: could not load cache mappings", cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_load_mappings", r);
			return r;
		}

		cache->loaded_mappings = true;
	}

	if (!cache->loaded_discards) {
		struct discard_load_info li;

		/*
		 * The discard bitset could have been resized, or the
		 * discard block size changed.  To be safe we start by
		 * setting every dblock to not discarded.
		 */
		clear_bitset(cache->discard_bitset, from_dblock(cache->discard_nr_blocks));

		discard_load_info_init(cache, &li);
		r = dm_cache_load_discards(cache->cmd, load_discard, &li);
		if (r) {
			DMERR("%s: could not load origin discards", cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_load_discards", r);
			return r;
		}
		set_discard_range(&li);

		cache->loaded_discards = true;
	}

	return r;
}