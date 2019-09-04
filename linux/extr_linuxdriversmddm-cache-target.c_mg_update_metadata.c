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
struct policy_work {int op; int /*<<< orphan*/  cblock; int /*<<< orphan*/  oblock; } ;
struct dm_cache_migration {int /*<<< orphan*/  k; struct policy_work* op; struct cache* cache; } ;
struct cache {int /*<<< orphan*/  committer; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMERR_LIMIT (char*,int /*<<< orphan*/ ) ; 
#define  POLICY_DEMOTE 130 
#define  POLICY_PROMOTE 129 
#define  POLICY_WRITEBACK 128 
 int /*<<< orphan*/  cache_device_name (struct cache*) ; 
 int /*<<< orphan*/  continue_after_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dm_cache_insert_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dm_cache_remove_mapping (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_continuation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct cache*,char*,int) ; 
 int /*<<< orphan*/  mg_complete (struct dm_cache_migration*,int) ; 
 int /*<<< orphan*/  mg_success ; 
 int /*<<< orphan*/  schedule_commit (int /*<<< orphan*/ *) ; 
 struct dm_cache_migration* ws_to_mg (struct work_struct*) ; 

__attribute__((used)) static void mg_update_metadata(struct work_struct *ws)
{
	int r;
	struct dm_cache_migration *mg = ws_to_mg(ws);
	struct cache *cache = mg->cache;
	struct policy_work *op = mg->op;

	switch (op->op) {
	case POLICY_PROMOTE:
		r = dm_cache_insert_mapping(cache->cmd, op->cblock, op->oblock);
		if (r) {
			DMERR_LIMIT("%s: migration failed; couldn't insert mapping",
				    cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_insert_mapping", r);

			mg_complete(mg, false);
			return;
		}
		mg_complete(mg, true);
		break;

	case POLICY_DEMOTE:
		r = dm_cache_remove_mapping(cache->cmd, op->cblock);
		if (r) {
			DMERR_LIMIT("%s: migration failed; couldn't update on disk metadata",
				    cache_device_name(cache));
			metadata_operation_failed(cache, "dm_cache_remove_mapping", r);

			mg_complete(mg, false);
			return;
		}

		/*
		 * It would be nice if we only had to commit when a REQ_FLUSH
		 * comes through.  But there's one scenario that we have to
		 * look out for:
		 *
		 * - vblock x in a cache block
		 * - domotion occurs
		 * - cache block gets reallocated and over written
		 * - crash
		 *
		 * When we recover, because there was no commit the cache will
		 * rollback to having the data for vblock x in the cache block.
		 * But the cache block has since been overwritten, so it'll end
		 * up pointing to data that was never in 'x' during the history
		 * of the device.
		 *
		 * To avoid this issue we require a commit as part of the
		 * demotion operation.
		 */
		init_continuation(&mg->k, mg_success);
		continue_after_commit(&cache->committer, &mg->k);
		schedule_commit(&cache->committer);
		break;

	case POLICY_WRITEBACK:
		mg_complete(mg, true);
		break;
	}
}