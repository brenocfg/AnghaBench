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
struct cache {int /*<<< orphan*/  committer; int /*<<< orphan*/  origin_blocks; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int /*<<< orphan*/  accounted_begin (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  defer_bio (struct cache*,struct bio*) ; 
 scalar_t__ discard_or_flush (struct bio*) ; 
 scalar_t__ from_oblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bio_block (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  init_per_bio_data (struct bio*) ; 
 int map_bio (struct cache*,struct bio*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  remap_to_origin (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  schedule_commit (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int cache_map(struct dm_target *ti, struct bio *bio)
{
	struct cache *cache = ti->private;

	int r;
	bool commit_needed;
	dm_oblock_t block = get_bio_block(cache, bio);

	init_per_bio_data(bio);
	if (unlikely(from_oblock(block) >= from_oblock(cache->origin_blocks))) {
		/*
		 * This can only occur if the io goes to a partial block at
		 * the end of the origin device.  We don't cache these.
		 * Just remap to the origin and carry on.
		 */
		remap_to_origin(cache, bio);
		accounted_begin(cache, bio);
		return DM_MAPIO_REMAPPED;
	}

	if (discard_or_flush(bio)) {
		defer_bio(cache, bio);
		return DM_MAPIO_SUBMITTED;
	}

	r = map_bio(cache, bio, block, &commit_needed);
	if (commit_needed)
		schedule_commit(&cache->committer);

	return r;
}