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
struct policy_work {int dummy; } ;
struct dm_cache_migration {struct bio* overwrite_bio; struct policy_work* op; } ;
struct cache {int /*<<< orphan*/  policy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 struct dm_cache_migration* alloc_migration (struct cache*) ; 
 int /*<<< orphan*/  background_work_begin (struct cache*) ; 
 int /*<<< orphan*/  inc_io_migrations (struct cache*) ; 
 int mg_lock_writes (struct dm_cache_migration*) ; 
 int /*<<< orphan*/  policy_complete_background_work (int /*<<< orphan*/ ,struct policy_work*,int) ; 

__attribute__((used)) static int mg_start(struct cache *cache, struct policy_work *op, struct bio *bio)
{
	struct dm_cache_migration *mg;

	if (!background_work_begin(cache)) {
		policy_complete_background_work(cache->policy, op, false);
		return -EPERM;
	}

	mg = alloc_migration(cache);

	mg->op = op;
	mg->overwrite_bio = bio;

	if (!bio)
		inc_io_migrations(cache);

	return mg_lock_writes(mg);
}