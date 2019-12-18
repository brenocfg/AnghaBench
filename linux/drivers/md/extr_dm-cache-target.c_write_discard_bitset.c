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
struct cache {int /*<<< orphan*/  cmd; int /*<<< orphan*/  discard_nr_blocks; int /*<<< orphan*/  discard_block_size; } ;

/* Variables and functions */
 scalar_t__ CM_READ_ONLY ; 
 int /*<<< orphan*/  DMERR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 unsigned int dm_cache_discard_bitset_resize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int dm_cache_set_discard (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int from_dblock (int /*<<< orphan*/ ) ; 
 scalar_t__ get_cache_mode (struct cache*) ; 
 int /*<<< orphan*/  is_discarded (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct cache*,char*,unsigned int) ; 
 int /*<<< orphan*/  to_dblock (unsigned int) ; 

__attribute__((used)) static int write_discard_bitset(struct cache *cache)
{
	unsigned i, r;

	if (get_cache_mode(cache) >= CM_READ_ONLY)
		return -EINVAL;

	r = dm_cache_discard_bitset_resize(cache->cmd, cache->discard_block_size,
					   cache->discard_nr_blocks);
	if (r) {
		DMERR("%s: could not resize on-disk discard bitset", cache_device_name(cache));
		metadata_operation_failed(cache, "dm_cache_discard_bitset_resize", r);
		return r;
	}

	for (i = 0; i < from_dblock(cache->discard_nr_blocks); i++) {
		r = dm_cache_set_discard(cache->cmd, to_dblock(i),
					 is_discarded(cache, to_dblock(i)));
		if (r) {
			metadata_operation_failed(cache, "dm_cache_set_discard", r);
			return r;
		}
	}

	return 0;
}