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
struct dm_cache_migration {scalar_t__ overwrite_bio; int /*<<< orphan*/  cell; struct cache* cache; } ;
struct cache {int /*<<< orphan*/  prison; } ;
struct bio_list {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  background_work_end (struct cache*) ; 
 int /*<<< orphan*/  bio_io_error (scalar_t__) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  defer_bios (struct cache*,struct bio_list*) ; 
 scalar_t__ dm_cell_unlock_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio_list*) ; 
 int /*<<< orphan*/  free_migration (struct dm_cache_migration*) ; 
 int /*<<< orphan*/  free_prison_cell (struct cache*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void invalidate_complete(struct dm_cache_migration *mg, bool success)
{
	struct bio_list bios;
	struct cache *cache = mg->cache;

	bio_list_init(&bios);
	if (dm_cell_unlock_v2(cache->prison, mg->cell, &bios))
		free_prison_cell(cache, mg->cell);

	if (!success && mg->overwrite_bio)
		bio_io_error(mg->overwrite_bio);

	free_migration(mg);
	defer_bios(cache, &bios);

	background_work_end(cache);
}