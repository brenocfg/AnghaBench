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
struct dm_cell_key_v2 {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ws; } ;
struct dm_cache_migration {TYPE_2__ k; struct dm_bio_prison_cell_v2* cell; scalar_t__ overwrite_bio; TYPE_1__* op; struct cache* cache; } ;
struct dm_bio_prison_cell_v2 {int dummy; } ;
struct cache {int /*<<< orphan*/  prison; } ;
struct TYPE_3__ {int /*<<< orphan*/  oblock; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_WRITE_LOCK_LEVEL ; 
 int /*<<< orphan*/  WRITE_LOCK_LEVEL ; 
 struct dm_bio_prison_cell_v2* alloc_prison_cell (struct cache*) ; 
 int /*<<< orphan*/  build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_cell_key_v2*) ; 
 int dm_cell_lock_v2 (int /*<<< orphan*/ ,struct dm_cell_key_v2*,int /*<<< orphan*/ ,struct dm_bio_prison_cell_v2*,struct dm_bio_prison_cell_v2**) ; 
 int /*<<< orphan*/  free_prison_cell (struct cache*,struct dm_bio_prison_cell_v2*) ; 
 int /*<<< orphan*/  mg_complete (struct dm_cache_migration*,int) ; 
 int /*<<< orphan*/  mg_copy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oblock_succ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quiesce (struct dm_cache_migration*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 

__attribute__((used)) static int mg_lock_writes(struct dm_cache_migration *mg)
{
	int r;
	struct dm_cell_key_v2 key;
	struct cache *cache = mg->cache;
	struct dm_bio_prison_cell_v2 *prealloc;

	prealloc = alloc_prison_cell(cache);

	/*
	 * Prevent writes to the block, but allow reads to continue.
	 * Unless we're using an overwrite bio, in which case we lock
	 * everything.
	 */
	build_key(mg->op->oblock, oblock_succ(mg->op->oblock), &key);
	r = dm_cell_lock_v2(cache->prison, &key,
			    mg->overwrite_bio ?  READ_WRITE_LOCK_LEVEL : WRITE_LOCK_LEVEL,
			    prealloc, &mg->cell);
	if (r < 0) {
		free_prison_cell(cache, prealloc);
		mg_complete(mg, false);
		return r;
	}

	if (mg->cell != prealloc)
		free_prison_cell(cache, prealloc);

	if (r == 0)
		mg_copy(&mg->k.ws);
	else
		quiesce(mg, mg_copy);

	return 0;
}