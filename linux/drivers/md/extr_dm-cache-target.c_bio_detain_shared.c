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
struct per_bio_data {struct dm_bio_prison_cell_v2* cell; } ;
struct dm_cell_key_v2 {int dummy; } ;
struct dm_bio_prison_cell_v2 {int dummy; } ;
struct cache {int /*<<< orphan*/  prison; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  dm_oblock_t ;

/* Variables and functions */
 struct dm_bio_prison_cell_v2* alloc_prison_cell (struct cache*) ; 
 int /*<<< orphan*/  build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_cell_key_v2*) ; 
 int dm_cell_get_v2 (int /*<<< orphan*/ ,struct dm_cell_key_v2*,int /*<<< orphan*/ ,struct bio*,struct dm_bio_prison_cell_v2*,struct dm_bio_prison_cell_v2**) ; 
 int /*<<< orphan*/  free_prison_cell (struct cache*,struct dm_bio_prison_cell_v2*) ; 
 scalar_t__ from_oblock (int /*<<< orphan*/ ) ; 
 struct per_bio_data* get_per_bio_data (struct bio*) ; 
 int /*<<< orphan*/  lock_level (struct bio*) ; 
 int /*<<< orphan*/  to_oblock (scalar_t__) ; 

__attribute__((used)) static bool bio_detain_shared(struct cache *cache, dm_oblock_t oblock, struct bio *bio)
{
	bool r;
	struct per_bio_data *pb;
	struct dm_cell_key_v2 key;
	dm_oblock_t end = to_oblock(from_oblock(oblock) + 1ULL);
	struct dm_bio_prison_cell_v2 *cell_prealloc, *cell;

	cell_prealloc = alloc_prison_cell(cache); /* FIXME: allow wait if calling from worker */

	build_key(oblock, end, &key);
	r = dm_cell_get_v2(cache->prison, &key, lock_level(bio), bio, cell_prealloc, &cell);
	if (!r) {
		/*
		 * Failed to get the lock.
		 */
		free_prison_cell(cache, cell_prealloc);
		return r;
	}

	if (cell != cell_prealloc)
		free_prison_cell(cache, cell_prealloc);

	pb = get_per_bio_data(bio);
	pb->cell = cell;

	return r;
}