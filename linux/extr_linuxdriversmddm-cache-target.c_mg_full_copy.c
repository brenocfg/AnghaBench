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
struct policy_work {int /*<<< orphan*/  oblock; int /*<<< orphan*/  cblock; int /*<<< orphan*/  op; } ;
struct dm_cache_migration {int /*<<< orphan*/  k; struct policy_work* op; struct cache* cache; } ;
struct cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  POLICY_PROMOTE ; 
 int /*<<< orphan*/  copy (struct dm_cache_migration*,int) ; 
 int /*<<< orphan*/  init_continuation (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct work_struct*)) ; 
 int /*<<< orphan*/  is_dirty (struct cache*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_discarded_oblock (struct cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mg_upgrade_lock (struct work_struct*) ; 
 struct dm_cache_migration* ws_to_mg (struct work_struct*) ; 

__attribute__((used)) static void mg_full_copy(struct work_struct *ws)
{
	struct dm_cache_migration *mg = ws_to_mg(ws);
	struct cache *cache = mg->cache;
	struct policy_work *op = mg->op;
	bool is_policy_promote = (op->op == POLICY_PROMOTE);

	if ((!is_policy_promote && !is_dirty(cache, op->cblock)) ||
	    is_discarded_oblock(cache, op->oblock)) {
		mg_upgrade_lock(ws);
		return;
	}

	init_continuation(&mg->k, mg_upgrade_lock);
	copy(mg, is_policy_promote);
}