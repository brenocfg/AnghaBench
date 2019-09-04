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
struct work_struct {int dummy; } ;
struct dm_cache_migration {int /*<<< orphan*/ * overwrite_bio; int /*<<< orphan*/  invalidate_oblock; int /*<<< orphan*/  k; int /*<<< orphan*/  invalidate_cblock; struct cache* cache; } ;
struct cache {int /*<<< orphan*/  committer; } ;

/* Variables and functions */
 int /*<<< orphan*/  continue_after_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_continuation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int invalidate_cblock (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_complete (struct dm_cache_migration*,int) ; 
 int /*<<< orphan*/  invalidate_completed ; 
 int /*<<< orphan*/  remap_to_origin_clear_discard (struct cache*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_commit (int /*<<< orphan*/ *) ; 
 struct dm_cache_migration* ws_to_mg (struct work_struct*) ; 

__attribute__((used)) static void invalidate_remove(struct work_struct *ws)
{
	int r;
	struct dm_cache_migration *mg = ws_to_mg(ws);
	struct cache *cache = mg->cache;

	r = invalidate_cblock(cache, mg->invalidate_cblock);
	if (r) {
		invalidate_complete(mg, false);
		return;
	}

	init_continuation(&mg->k, invalidate_completed);
	continue_after_commit(&cache->committer, &mg->k);
	remap_to_origin_clear_discard(cache, mg->overwrite_bio, mg->invalidate_oblock);
	mg->overwrite_bio = NULL;
	schedule_commit(&cache->committer);
}