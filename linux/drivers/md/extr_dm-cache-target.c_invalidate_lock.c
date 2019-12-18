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
struct dm_cell_key_v2 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ws; } ;
struct dm_cache_migration {TYPE_1__ k; struct dm_bio_prison_cell_v2* cell; int /*<<< orphan*/  invalidate_oblock; struct cache* cache; } ;
struct dm_bio_prison_cell_v2 {int dummy; } ;
struct cache {int /*<<< orphan*/  wq; int /*<<< orphan*/  prison; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_WRITE_LOCK_LEVEL ; 
 struct dm_bio_prison_cell_v2* alloc_prison_cell (struct cache*) ; 
 int /*<<< orphan*/  build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_cell_key_v2*) ; 
 int dm_cell_lock_v2 (int /*<<< orphan*/ ,struct dm_cell_key_v2*,int /*<<< orphan*/ ,struct dm_bio_prison_cell_v2*,struct dm_bio_prison_cell_v2**) ; 
 int /*<<< orphan*/  free_prison_cell (struct cache*,struct dm_bio_prison_cell_v2*) ; 
 int /*<<< orphan*/  init_continuation (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_complete (struct dm_cache_migration*,int) ; 
 int /*<<< orphan*/  invalidate_remove ; 
 int /*<<< orphan*/  oblock_succ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quiesce (struct dm_cache_migration*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int invalidate_lock(struct dm_cache_migration *mg)
{
	int r;
	struct dm_cell_key_v2 key;
	struct cache *cache = mg->cache;
	struct dm_bio_prison_cell_v2 *prealloc;

	prealloc = alloc_prison_cell(cache);

	build_key(mg->invalidate_oblock, oblock_succ(mg->invalidate_oblock), &key);
	r = dm_cell_lock_v2(cache->prison, &key,
			    READ_WRITE_LOCK_LEVEL, prealloc, &mg->cell);
	if (r < 0) {
		free_prison_cell(cache, prealloc);
		invalidate_complete(mg, false);
		return r;
	}

	if (mg->cell != prealloc)
		free_prison_cell(cache, prealloc);

	if (r)
		quiesce(mg, invalidate_remove);

	else {
		/*
		 * We can't call invalidate_remove() directly here because we
		 * might still be in request context.
		 */
		init_continuation(&mg->k, invalidate_remove);
		queue_work(cache->wq, &mg->k.ws);
	}

	return 0;
}