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
struct thin_c {struct pool* pool; int /*<<< orphan*/  td; } ;
struct pool {int /*<<< orphan*/  (* process_prepared_discard ) (struct dm_thin_new_mapping*) ;int /*<<< orphan*/  all_io_ds; } ;
struct dm_thin_new_mapping {int maybe_shared; int /*<<< orphan*/  list; struct bio* bio; struct dm_bio_prison_cell* cell; scalar_t__ data_block; scalar_t__ virt_end; scalar_t__ virt_begin; struct thin_c* tc; } ;
struct dm_cell_key {int dummy; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct bio {int dummy; } ;
typedef  scalar_t__ dm_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  PHYSICAL ; 
 scalar_t__ bio_detain (struct pool*,struct dm_cell_key*,int /*<<< orphan*/ *,struct dm_bio_prison_cell**) ; 
 int /*<<< orphan*/  bio_inc_remaining (struct bio*) ; 
 int /*<<< orphan*/  build_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,struct dm_cell_key*) ; 
 int /*<<< orphan*/  dm_deferred_set_add_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dm_thin_find_mapped_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*,scalar_t__*,int*) ; 
 int ensure_next_mapping (struct pool*) ; 
 struct dm_thin_new_mapping* get_next_mapping (struct pool*) ; 
 int /*<<< orphan*/  stub1 (struct dm_thin_new_mapping*) ; 

__attribute__((used)) static void break_up_discard_bio(struct thin_c *tc, dm_block_t begin, dm_block_t end,
				 struct bio *bio)
{
	struct pool *pool = tc->pool;

	int r;
	bool maybe_shared;
	struct dm_cell_key data_key;
	struct dm_bio_prison_cell *data_cell;
	struct dm_thin_new_mapping *m;
	dm_block_t virt_begin, virt_end, data_begin;

	while (begin != end) {
		r = ensure_next_mapping(pool);
		if (r)
			/* we did our best */
			return;

		r = dm_thin_find_mapped_range(tc->td, begin, end, &virt_begin, &virt_end,
					      &data_begin, &maybe_shared);
		if (r)
			/*
			 * Silently fail, letting any mappings we've
			 * created complete.
			 */
			break;

		build_key(tc->td, PHYSICAL, data_begin, data_begin + (virt_end - virt_begin), &data_key);
		if (bio_detain(tc->pool, &data_key, NULL, &data_cell)) {
			/* contention, we'll give up with this range */
			begin = virt_end;
			continue;
		}

		/*
		 * IO may still be going to the destination block.  We must
		 * quiesce before we can do the removal.
		 */
		m = get_next_mapping(pool);
		m->tc = tc;
		m->maybe_shared = maybe_shared;
		m->virt_begin = virt_begin;
		m->virt_end = virt_end;
		m->data_block = data_begin;
		m->cell = data_cell;
		m->bio = bio;

		/*
		 * The parent bio must not complete before sub discard bios are
		 * chained to it (see end_discard's bio_chain)!
		 *
		 * This per-mapping bi_remaining increment is paired with
		 * the implicit decrement that occurs via bio_endio() in
		 * end_discard().
		 */
		bio_inc_remaining(bio);
		if (!dm_deferred_set_add_work(pool->all_io_ds, &m->list))
			pool->process_prepared_discard(m);

		begin = virt_end;
	}
}