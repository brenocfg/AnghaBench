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
struct thin_c {int /*<<< orphan*/  td; struct pool* pool; } ;
struct pool {int /*<<< orphan*/  shared_read_ds; } ;
struct dm_thin_lookup_result {int /*<<< orphan*/  block; } ;
struct dm_thin_endio_hook {int /*<<< orphan*/  shared_read_entry; } ;
struct dm_cell_key {int dummy; } ;
struct dm_bio_prison_cell {int dummy; } ;
struct TYPE_2__ {scalar_t__ bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 scalar_t__ WRITE ; 
 scalar_t__ bio_data_dir (struct bio*) ; 
 scalar_t__ bio_detain (struct pool*,struct dm_cell_key*,struct bio*,struct dm_bio_prison_cell**) ; 
 int /*<<< orphan*/  break_sharing (struct thin_c*,struct bio*,int /*<<< orphan*/ ,struct dm_cell_key*,struct dm_thin_lookup_result*,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  build_data_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dm_cell_key*) ; 
 int /*<<< orphan*/  cell_defer_no_holder (struct thin_c*,struct dm_bio_prison_cell*) ; 
 int /*<<< orphan*/  dm_deferred_entry_inc (int /*<<< orphan*/ ) ; 
 struct dm_thin_endio_hook* dm_per_bio_data (struct bio*,int) ; 
 int /*<<< orphan*/  inc_all_io_entry (struct pool*,struct bio*) ; 
 int /*<<< orphan*/  remap_and_issue (struct thin_c*,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_and_issue_shared_cell (struct thin_c*,struct dm_bio_prison_cell*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_shared_bio(struct thin_c *tc, struct bio *bio,
			       dm_block_t block,
			       struct dm_thin_lookup_result *lookup_result,
			       struct dm_bio_prison_cell *virt_cell)
{
	struct dm_bio_prison_cell *data_cell;
	struct pool *pool = tc->pool;
	struct dm_cell_key key;

	/*
	 * If cell is already occupied, then sharing is already in the process
	 * of being broken so we have nothing further to do here.
	 */
	build_data_key(tc->td, lookup_result->block, &key);
	if (bio_detain(pool, &key, bio, &data_cell)) {
		cell_defer_no_holder(tc, virt_cell);
		return;
	}

	if (bio_data_dir(bio) == WRITE && bio->bi_iter.bi_size) {
		break_sharing(tc, bio, block, &key, lookup_result, data_cell);
		cell_defer_no_holder(tc, virt_cell);
	} else {
		struct dm_thin_endio_hook *h = dm_per_bio_data(bio, sizeof(struct dm_thin_endio_hook));

		h->shared_read_entry = dm_deferred_entry_inc(pool->shared_read_ds);
		inc_all_io_entry(pool, bio);
		remap_and_issue(tc, bio, lookup_result->block);

		remap_and_issue_shared_cell(tc, data_cell, lookup_result->block);
		remap_and_issue_shared_cell(tc, virt_cell, lookup_result->block);
	}
}