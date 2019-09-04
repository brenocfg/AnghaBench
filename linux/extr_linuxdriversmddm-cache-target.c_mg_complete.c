#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct policy_work {int op; int /*<<< orphan*/  oblock; int /*<<< orphan*/  cblock; } ;
struct TYPE_3__ {int /*<<< orphan*/  input; } ;
struct dm_cache_migration {scalar_t__ cell; TYPE_2__* overwrite_bio; TYPE_1__ k; struct policy_work* op; struct cache* cache; } ;
struct cache {int /*<<< orphan*/  prison; int /*<<< orphan*/  policy; int /*<<< orphan*/  stats; } ;
struct bio_list {int dummy; } ;
typedef  int /*<<< orphan*/  dm_cblock_t ;
struct TYPE_4__ {int /*<<< orphan*/  bi_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_STS_IOERR ; 
#define  POLICY_DEMOTE 130 
#define  POLICY_PROMOTE 129 
#define  POLICY_WRITEBACK 128 
 int /*<<< orphan*/  background_work_end (struct cache*) ; 
 int /*<<< orphan*/  bio_endio (TYPE_2__*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  clear_discard (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_io_migrations (struct cache*) ; 
 int /*<<< orphan*/  defer_bios (struct cache*,struct bio_list*) ; 
 scalar_t__ dm_cell_unlock_v2 (int /*<<< orphan*/ ,scalar_t__,struct bio_list*) ; 
 int /*<<< orphan*/  force_clear_dirty (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_set_dirty (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_migration (struct dm_cache_migration*) ; 
 int /*<<< orphan*/  free_prison_cell (struct cache*,scalar_t__) ; 
 int /*<<< orphan*/  oblock_to_dblock (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_complete_background_work (int /*<<< orphan*/ ,struct policy_work*,int) ; 
 int /*<<< orphan*/  update_stats (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wake_migration_worker (struct cache*) ; 

__attribute__((used)) static void mg_complete(struct dm_cache_migration *mg, bool success)
{
	struct bio_list bios;
	struct cache *cache = mg->cache;
	struct policy_work *op = mg->op;
	dm_cblock_t cblock = op->cblock;

	if (success)
		update_stats(&cache->stats, op->op);

	switch (op->op) {
	case POLICY_PROMOTE:
		clear_discard(cache, oblock_to_dblock(cache, op->oblock));
		policy_complete_background_work(cache->policy, op, success);

		if (mg->overwrite_bio) {
			if (success)
				force_set_dirty(cache, cblock);
			else if (mg->k.input)
				mg->overwrite_bio->bi_status = mg->k.input;
			else
				mg->overwrite_bio->bi_status = BLK_STS_IOERR;
			bio_endio(mg->overwrite_bio);
		} else {
			if (success)
				force_clear_dirty(cache, cblock);
			dec_io_migrations(cache);
		}
		break;

	case POLICY_DEMOTE:
		/*
		 * We clear dirty here to update the nr_dirty counter.
		 */
		if (success)
			force_clear_dirty(cache, cblock);
		policy_complete_background_work(cache->policy, op, success);
		dec_io_migrations(cache);
		break;

	case POLICY_WRITEBACK:
		if (success)
			force_clear_dirty(cache, cblock);
		policy_complete_background_work(cache->policy, op, success);
		dec_io_migrations(cache);
		break;
	}

	bio_list_init(&bios);
	if (mg->cell) {
		if (dm_cell_unlock_v2(cache->prison, mg->cell, &bios))
			free_prison_cell(cache, mg->cell);
	}

	free_migration(mg);
	defer_bios(cache, &bios);
	wake_migration_worker(cache);

	background_work_end(cache);
}