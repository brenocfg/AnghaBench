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
struct dm_cache_migration {int /*<<< orphan*/  invalidate_oblock; int /*<<< orphan*/  invalidate_cblock; struct bio* overwrite_bio; } ;
struct cache {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int EPERM ; 
 struct dm_cache_migration* alloc_migration (struct cache*) ; 
 int /*<<< orphan*/  background_work_begin (struct cache*) ; 
 int invalidate_lock (struct dm_cache_migration*) ; 

__attribute__((used)) static int invalidate_start(struct cache *cache, dm_cblock_t cblock,
			    dm_oblock_t oblock, struct bio *bio)
{
	struct dm_cache_migration *mg;

	if (!background_work_begin(cache))
		return -EPERM;

	mg = alloc_migration(cache);

	mg->overwrite_bio = bio;
	mg->invalidate_cblock = cblock;
	mg->invalidate_oblock = oblock;

	return invalidate_lock(mg);
}