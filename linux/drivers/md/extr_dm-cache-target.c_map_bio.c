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
struct policy_work {scalar_t__ op; } ;
struct per_bio_data {scalar_t__ req_nr; } ;
struct TYPE_2__ {int /*<<< orphan*/  demotion; } ;
struct cache {int /*<<< orphan*/  committer; TYPE_1__ stats; int /*<<< orphan*/  policy; } ;
struct bio {int bi_opf; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ,int) ; 
 int DM_MAPIO_REMAPPED ; 
 int DM_MAPIO_SUBMITTED ; 
 int ENOENT ; 
 scalar_t__ POLICY_PROMOTE ; 
 int REQ_FUA ; 
 int WRITE ; 
 int /*<<< orphan*/  accounted_begin (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  accounted_complete (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int bio_data_dir (struct bio*) ; 
 int bio_detain_shared (struct cache*,int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  bio_drop_shared_lock (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 int /*<<< orphan*/  bio_io_error (struct bio*) ; 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  inc_hit_counter (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  inc_miss_counter (struct cache*,struct bio*) ; 
 int /*<<< orphan*/  invalidate_start (struct cache*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  is_dirty (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  issue_after_commit (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  mg_start (struct cache*,struct policy_work*,struct bio*) ; 
 scalar_t__ optimisable_bio (struct cache*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ passthrough_mode (struct cache*) ; 
 int policy_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int*) ; 
 int policy_lookup_with_work (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,struct policy_work**) ; 
 int /*<<< orphan*/  remap_to_cache_dirty (struct cache*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_to_origin_and_cache (struct cache*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_to_origin_clear_discard (struct cache*,struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wake_migration_worker (struct cache*) ; 
 scalar_t__ writethrough_mode (struct cache*) ; 

__attribute__((used)) static int map_bio(struct cache *cache, struct bio *bio, dm_oblock_t block,
		   bool *commit_needed)
{
	int r, data_dir;
	bool rb, background_queued;
	dm_cblock_t cblock;

	*commit_needed = false;

	rb = bio_detain_shared(cache, block, bio);
	if (!rb) {
		/*
		 * An exclusive lock is held for this block, so we have to
		 * wait.  We set the commit_needed flag so the current
		 * transaction will be committed asap, allowing this lock
		 * to be dropped.
		 */
		*commit_needed = true;
		return DM_MAPIO_SUBMITTED;
	}

	data_dir = bio_data_dir(bio);

	if (optimisable_bio(cache, bio, block)) {
		struct policy_work *op = NULL;

		r = policy_lookup_with_work(cache->policy, block, &cblock, data_dir, true, &op);
		if (unlikely(r && r != -ENOENT)) {
			DMERR_LIMIT("%s: policy_lookup_with_work() failed with r = %d",
				    cache_device_name(cache), r);
			bio_io_error(bio);
			return DM_MAPIO_SUBMITTED;
		}

		if (r == -ENOENT && op) {
			bio_drop_shared_lock(cache, bio);
			BUG_ON(op->op != POLICY_PROMOTE);
			mg_start(cache, op, bio);
			return DM_MAPIO_SUBMITTED;
		}
	} else {
		r = policy_lookup(cache->policy, block, &cblock, data_dir, false, &background_queued);
		if (unlikely(r && r != -ENOENT)) {
			DMERR_LIMIT("%s: policy_lookup() failed with r = %d",
				    cache_device_name(cache), r);
			bio_io_error(bio);
			return DM_MAPIO_SUBMITTED;
		}

		if (background_queued)
			wake_migration_worker(cache);
	}

	if (r == -ENOENT) {
		struct per_bio_data *pb = get_per_bio_data(bio);

		/*
		 * Miss.
		 */
		inc_miss_counter(cache, bio);
		if (pb->req_nr == 0) {
			accounted_begin(cache, bio);
			remap_to_origin_clear_discard(cache, bio, block);
		} else {
			/*
			 * This is a duplicate writethrough io that is no
			 * longer needed because the block has been demoted.
			 */
			bio_endio(bio);
			return DM_MAPIO_SUBMITTED;
		}
	} else {
		/*
		 * Hit.
		 */
		inc_hit_counter(cache, bio);

		/*
		 * Passthrough always maps to the origin, invalidating any
		 * cache blocks that are written to.
		 */
		if (passthrough_mode(cache)) {
			if (bio_data_dir(bio) == WRITE) {
				bio_drop_shared_lock(cache, bio);
				atomic_inc(&cache->stats.demotion);
				invalidate_start(cache, cblock, block, bio);
			} else
				remap_to_origin_clear_discard(cache, bio, block);
		} else {
			if (bio_data_dir(bio) == WRITE && writethrough_mode(cache) &&
			    !is_dirty(cache, cblock)) {
				remap_to_origin_and_cache(cache, bio, block, cblock);
				accounted_begin(cache, bio);
			} else
				remap_to_cache_dirty(cache, bio, block, cblock);
		}
	}

	/*
	 * dm core turns FUA requests into a separate payload and FLUSH req.
	 */
	if (bio->bi_opf & REQ_FUA) {
		/*
		 * issue_after_commit will call accounted_begin a second time.  So
		 * we call accounted_complete() to avoid double accounting.
		 */
		accounted_complete(cache, bio);
		issue_after_commit(&cache->committer, bio);
		*commit_needed = true;
		return DM_MAPIO_SUBMITTED;
	}

	return DM_MAPIO_REMAPPED;
}